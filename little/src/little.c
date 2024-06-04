/**
 * Projec : gtsp (voyageur de commerce)
 *
 * Date   : 07/04/2014
 * Author : Olivier Grunder
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


#define NBR_TOWNS 10

 /* Distance matrix */
double dist[NBR_TOWNS][NBR_TOWNS];

/* next_town[i] = next town after town i */
int next_town[NBR_TOWNS];

/* no comment */
int best_solution[NBR_TOWNS];
double best_eval = -1.0;


/**
 * Berlin52 :
 *  6 towns : (2608.25) -> Best solution (2315.15): 0 1 2 3 5 4
 * 10 towns : (3278.83) -> Best solution (2826.50): 0 1 6 2 7 8 9 3 5 4
 * 15 towns : (5075.43) -> Best solution (4967.300): 0 13 12 10 11 3 5 4 14 9 8 7 2 6 1
 * 20 towns : (5637.21) -> Best solution (5270.860): 0 18 7 8 9 14 4 5 3 11 10 12 13 15 19 1 6 16 2 17
 * 25 towns : (5773.28) -> Best solution (5460.939): 0 21 17 20 1 6 16 2 18 7 8 9 14 4 23 5 3 24 11 10 12 13 15 19 22
 * 30 towns : (6875.88) -> Best solution 
 * 35 towns : (6888.63) -> Best solution
 * 40 towns : (7000.24) -> Best solution
 * 45 towns : (7549.86) -> Best solution
 * 50 towns : (8804.23) -> Best solution
 * 52 towns : (8980.91) -> Best solution
 */
double coord[NBR_TOWNS][2] =
{
    { 565.0, 575.0},
    {  25.0, 185.0},
    { 345.0, 750.0},
    { 945.0, 685.0},
    { 845.0, 655.0},
    { 880.0, 660.0},
    {  25.0, 230.0},
    { 525.0, 1000.0},
    { 580.0, 1175.0},
    { 650.0, 1130.0},
    // {1605.0, 620.0},
    // {1220.0, 580.0},
    // {1465.0, 200.0},
    // {1530.0, 5.0  },
    // { 845.0, 680.0},
    // { 725.0, 370.0},
    // { 145.0, 665.0},
    // { 415.0, 635.0},
    // { 510.0, 875.0},
    // { 560.0, 365.0},
    // { 300.0, 465.0},
    // { 520.0, 585.0},
    // { 480.0, 415.0},
    // { 835.0, 625.0},
    // { 975.0, 580.0},
    // {1215.0, 245.0},
    // {1320.0, 315.0},
    // {1250.0, 400.0},
    // { 660.0, 180.0},
    // { 410.0, 250.0},
    // { 420.0, 555.0},
    // { 575.0, 665.0},
    // {1150.0, 1160.0},
    // { 700.0, 580.0},
    // { 685.0, 595.0},
    // { 685.0, 610.0},
    // { 770.0, 610.0},
    // { 795.0, 645.0},
    // { 720.0, 635.0},
    // { 760.0, 650.0},
    // { 475.0, 960.0},
    // {  95.0, 260.0},
    // { 875.0, 920.0},
    // { 700.0, 500.0},
    // { 555.0, 815.0},
    // { 830.0, 485.0},
    // {1170.0, 65.0 },
    // { 830.0, 610.0},
    // { 605.0, 625.0},
    // { 595.0, 360.0},
    // {1340.0, 725.0},
    // {1740.0, 245.0},
};



/**
 * print a matrix
 */
void print_matrix(double d[NBR_TOWNS][NBR_TOWNS]) {
    int i, j;
    for (i = 0; i < NBR_TOWNS; i++) {
        printf("%d\t", i + 1);
        for (j = 0; j < NBR_TOWNS; j++) {
            printf("%.3f ", d[i][j]);
        }
        printf("\n");
    }
}



/**
 * compute distance matrix
 */
void compute_matrix(double d[NBR_TOWNS][NBR_TOWNS]) {
    int i, j;
    for (i = 0; i < NBR_TOWNS; i++) {
        double xi = coord[i][0];
        double yi = coord[i][1];

        for (j = 0; j < NBR_TOWNS; j++) {
            if (i == j) {
                d[i][j] = -1;
                continue;
            }
            double xj = coord[j][0];
            double yj = coord[j][1];
            d[i][j] = sqrt((xi - xj) * (xi - xj) + (yi - yj) * (yi - yj));
        }
    }
}

/**
 * print a solution
 */
void print_solution(int* sol, double eval) {
    int i;
    printf("(%.3f): ", eval);
    for (i = 0; i < NBR_TOWNS; i++)
        printf("%d ", sol[i]);
    printf("\n");
}


/**
 * evaluation of a solution
 */
double evaluation_solution(int* sol) {
    double eval = 0;
    int i;
    int start, end;
    for (i = 0; i < NBR_TOWNS; i++) {
        start = sol[i];
        end = sol[(i + 1) % NBR_TOWNS];
        eval += dist[start][end];
    }

    return eval;
}

int find_nearest_unvisited(int current_town, bool visited[NBR_TOWNS]) {
    int nearest_town = -1;
    double min_distance = -1;

    for (int j = 0; j < NBR_TOWNS; j++) {
        if (!visited[j]) {
            double distance = dist[current_town][j];
            if (min_distance < 0 || distance < min_distance) {
                min_distance = distance;
                nearest_town = j;
            }
        }
    }
    return nearest_town;
}


/**
 * initial solution
 */
double initial_solution() {
    /* solution of the nearest neighbour */
    int sol[NBR_TOWNS];
    bool visited[NBR_TOWNS] = { false }; // Initialize all towns as unvisited
    double eval = 0.0;

    sol[0] = 0;
    visited[0] = true;

    for (int i = 1; i < NBR_TOWNS; i++) {
        int current_town = sol[i - 1];
        int next_town = find_nearest_unvisited(current_town, visited);

        sol[i] = next_town;
        visited[next_town] = true;
    }

    eval = evaluation_solution(sol);
    printf("Initial solution ");
    print_solution(sol, eval);

    /* initialize best solution with initial solution */
    for (int i = 0; i < NBR_TOWNS; i++)
        best_solution[i] = sol[i];
    best_eval = eval;

    return eval;
}




/**
 *  Build final solution
 */
void build_solution() {
    int i, solution[NBR_TOWNS];

    int indiceCour = 0;
    int villeCour = 0;

    for (indiceCour = 0; indiceCour < NBR_TOWNS; indiceCour++) {

        solution[indiceCour] = villeCour;

        /* Test si le cycle est hamiltonien */
        for (i = 0; i < indiceCour; i++) {
            if (solution[i] == villeCour) {
                // printf ("cycle non hamiltonien\n");
                return;
            }
        }
        /* Recherche de la ville suivante */
        villeCour = next_town[villeCour];
    }

    double eval = evaluation_solution(solution);

    if (best_eval < 0 || eval < best_eval) {
        best_eval = eval;
        for (i = 0; i < NBR_TOWNS; i++)
            best_solution[i] = solution[i];

        printf("New best solution: ");
        print_solution(solution, best_eval);
    }
    return;
}


/**
 *  Little Algorithm
 */
void little_algorithm(double d0[NBR_TOWNS][NBR_TOWNS], int iteration, double eval_node_parent) {
    if (iteration == NBR_TOWNS) {
        build_solution();
        return;
    }

    /* Do the modification on a copy of the distance matrix */
    double d[NBR_TOWNS][NBR_TOWNS];
    memcpy(d, d0, NBR_TOWNS * NBR_TOWNS * sizeof(double));

    double eval_node_child = eval_node_parent;
    int i, j;

    // rows
    for (i = 0; i < NBR_TOWNS; i++) {
        double minl = -1;
        for (j = 0; j < NBR_TOWNS; j++) {
            double val = d[i][j];
            if (minl < 0 || (val >= 0 && val < minl)) {
                minl = val;
            }
        }
        if (minl >= 0) {
            eval_node_child += minl;
            for (j = 0; j < NBR_TOWNS; j++) {
                if (d[i][j] >= 0) {
                    d[i][j] -= minl;
                }
            }
        }
    }

    // cols
    for (j = 0; j < NBR_TOWNS; j++) {
        double minc = -1;
        for (i = 0; i < NBR_TOWNS; i++) {
            double val = d[i][j];
            if (minc < 0 || (val >= 0 && val < minc)) {
                minc = val;
            }
        }
        if (minc >= 0) {
            eval_node_child += minc;
            for (i = 0; i < NBR_TOWNS; i++) {
                if (d[i][j] >= 0) {
                    d[i][j] -= minc;
                }
            }
        }
    }


    /* Cut : stop the exploration of this node */
    if (best_eval >= 0 && eval_node_child >= best_eval)
        return;

    /* row and column of the zero with the max penalty */
    int izero = -1, jzero = -1;
    double max_penalty = -1;
    int k;

    for (i = 0; i < NBR_TOWNS; i++) {
        for (j = 0; j < NBR_TOWNS; j++) {
            if (d[i][j] == 0) {
                double min_row = -1;
                double min_col = -1;
                for (k = 0; k < NBR_TOWNS; k++) {
                    double valik = d[i][k];
                    double valkj = d[k][j];
                    if (valik >= 0 && (min_row < 0 || valik < min_row) && k != j) {
                        min_row = valik;
                    }
                    if (valkj >= 0 && (min_col < 0 || valkj < min_col) && k != i) {
                        min_col = valkj;
                    }
                }
                if (min_row < 0 || min_col < 0) {
                    min_row = 10e6;
                    min_col = 10e6;
                }
                double penalty = min_row + min_col;
                if (penalty > max_penalty) {
                    max_penalty = penalty;
                    izero = i;
                    jzero = j;
                }
            }
        }
    }
    if (izero < 0 || jzero < 0) {
        return;
    }

    next_town[jzero] = izero;
    // detect subtour

    // int start = jzero;
    // int tmp = next_town[start];
    // i = 0;
    // bool subtour = false;

    // // printf("\n%d -> %d\n", start, tmp);
    // while (tmp != start && tmp != -1 && i < NBR_TOWNS) {
    //     i++;
    // //     printf("%d -> %d\n", tmp, next_town[tmp]);
    //     tmp = next_town[tmp];
    // }

    // if (tmp == start && i < NBR_TOWNS) {
    //     subtour = true;
    // }

    // if (subtour) {
    //     printf("Sous-tour détecté, arrêt de l'exploration it:%d\n", iteration);
    // //     fprintf(stderr, "move added : %d -> %d\n", jzero, izero);
    // //     for (i = 0; i < NBR_TOWNS; i++) {
    // //         if (next_town[i] != -1)
    // //             fprintf(stderr, "\t%d -> %d\n", i, next_town[i]);
    // //     }
    // //     fprintf(stderr, "\n");
    //     next_town[izero] = -1;
    //     return;
    // }
    
    /* Do the modification on a copy of the distance matrix */
    double d2[NBR_TOWNS][NBR_TOWNS];
    memcpy(d2, d, NBR_TOWNS * NBR_TOWNS * sizeof(double));

    for (k = 0; k < NBR_TOWNS; k++) {
        d2[izero][k] = -1;
        d2[k][jzero] = -1;
    }
    d2[jzero][izero] = -1;

    /* Explore left child node according to given choice */

    little_algorithm(d2, iteration + 1, eval_node_child);

    /* Do the modification on a copy of the distance matrix */
    memcpy(d2, d, NBR_TOWNS * NBR_TOWNS * sizeof(double));

    d2[izero][jzero] = -1;

    little_algorithm(d2, iteration, eval_node_child);
}

/**
 *
 */
int main(int argc, char* argv[]) {
    for (int i = 0; i < NBR_TOWNS; i++)
        next_town[i] = -1;
    
    best_eval = -1;

    /* Print problem information */
    printf("Points coordinates:\n");
    int i;
    for (i = 0; i < NBR_TOWNS; i++) {
        printf("Node %d: x=%.3f, y=%.3f\n", i, coord[i][0], coord[i][1]);
    }
    printf("\n");

    compute_matrix(dist);

    printf("\n");
    printf("Distance Matrix:\n");
    print_matrix(dist);
    printf("\n");


    /* initial solution */
    double initial_value = initial_solution();
    (void)initial_value;

    /** Little : uncomment when needed
    */
    int iteration = 0;
    double lowerbound = 0.0;
    time_t start = time(NULL);
    little_algorithm(dist, iteration, lowerbound);
    time_t end = time(NULL);


    printf("Best solution:");
    print_solution(best_solution, best_eval);


    // printf("Hit RETURN!\n");
    // getchar();
    printf("Time: %f seconds\n", difftime(end, start));

    return 0;
}
