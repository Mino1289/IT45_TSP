#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include "random.h"
#include "rechercheTabou.h"
#include "solution.h"

using namespace std;

int main(int argc, char **argv)
// argc : nombre de parametres
// argv : tableau contenant les parametres
// Soit l'executable 'algo_tabou' ne prend pas d'arguments soit il prend 4 arguments :
//   1.  nombre d'it�reation (crit�re d'arret de l'algo)
//   2.  dur�e de la liste Tabou
//   3.  nombre de villes
//   4.  nom du fichier indiquant les distances entre villes
{
    // initialise le g�n�rateur de nombre al�atoire
    Random::randomize();

    // valeurs par defaut
    int nb_iteration = 10;
    int duree_tabou = 0;
    int nb_villes = 10;
    char fileDistances[100];
    strcpy(fileDistances, "data/distances_entre_villes_10.txt");

    cout << "Synopsis: " << argv[0] << " nbr_iter tabu_length number_town distance_file " << endl;
    cout << "   1. nbr_iter      : number of iterations, default value=" << nb_iteration << endl;
    cout << "   2. tabu_length   : tabu list length, default value=" << duree_tabou << endl;
    cout << "   3. number_town   : number of towns of instance, default value=" << nb_villes << endl;
    cout << "   4. distance_file : distance matrix filename, default value=" << fileDistances << endl;
    cout << endl;

    if (argc == 5)
    {
        nb_iteration = atoi(argv[1]);
        duree_tabou = atoi(argv[2]);
        nb_villes = atoi(argv[3]);
        strcpy(fileDistances, argv[4]);
    }
    else if (argc != 1)
    {
        cout << "Incorrect arguments" << endl;
        exit(EXIT_FAILURE);
    }

    // Intialise les param�tre de la RechercheTabou et cr�e la solution initiale
    //   1ier  param�tre : nombre d'it�reation (crit�re d'arret de l'algo)
    //   2i�me param�tre : dur�e de la liste Tabou
    //   3i�me param�tre : nombre de villes
    //   4i�me param�tre : fichier contenant les disantances entre les villes
    rechercheTabou algo(nb_iteration, duree_tabou, nb_villes, fileDistances);

    // Lance la recherche avec la m�thode Tabou
    solution *best = algo.optimiser(true);
    // Affiche la meilleure solution rencontr�e
    cout << endl
         << "la meilleure solution rencontree est : ";
    best->afficher();

    delete best;

    return 0;
}
