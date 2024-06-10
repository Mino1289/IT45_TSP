#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "ae.h"
#include "chromosome.h"
#include "random.h"

using namespace std;

int main(int argc, char** argv)
// argc : nombre de parametres
// argv : tableau contenant les parametres
// Soit l'executable 'algo_evo' ne prend pas d'arguments soit il prend 6 arguments :
//    1. nombre de g�n�ration (entier > 0)
//    2. taille de la population (entier > 0)
//    3. taux de croisement (0 <= reel <= 1)
//    4. taux de mutation (0 <= reel <= 1)
//    5. nombre de villes (=taille d'un chromosome)
//    6. nom du fichier indiquant les distances entre villes
{
	//initialise le g�n�rateur de nombre al�atoire
	Random::randomize();

	// valeurs par defaut
	int nb_generation = 1000000;
	int taille_population = 300;
	float taux_croisement = 1;
	float taux_mutation = 1;
	int taille_chromosome = 280;
	char fileDistances[100];
	strcpy(fileDistances, "data/distances_entre_villes_280.txt");

	// 10 villes: nbgen = 5000; taille_pop = 100;
	// 50 villes: nbgen = 25000; taille_pop = 100;

	if (argc == 7) {
		nb_generation = atoi(argv[1]);
		taille_population = atoi(argv[2]);
		taux_croisement = atof(argv[3]);
		taux_mutation = atof(argv[4]);
		taille_chromosome = atoi(argv[5]);
		strcpy(fileDistances, argv[6]);
	} else if (argc == 1) {
		cout << "Parametres par default" << endl;
	} else {
		cout << "Nombre d'arguments n'est pas correct." << endl;
		cout << "Soit l'executable 'algo_evo' ne prend pas d'arguments soit il prend 6 arguments : " << endl;
		cout << "   1. nombre de g�n�ration (entier > 0)" << endl;
		cout << "   2. taille de la population (entier > 0)" << endl;
		cout << "   3. taux de croisement (0 <= reel <= 1)" << endl;
		cout << "   4. taux de mutation (0 <= reel <= 1)" << endl;
		cout << "   5. nombre de villes (=taille d'un chromosome)" << endl;
		cout << "   6. nom du fichier indiquant les distances entre villes" << endl;
		exit(EXIT_FAILURE);
	}

	time_t debut = time(NULL);
	// initialise l'algorithme �volutionniste
	Ae algo(nb_generation, taille_population, taux_croisement, taux_mutation, taille_chromosome, fileDistances);
	// arguments du constructeur de l'objet Ae
	//    1. nombre de g�n�ration (entier > 0)
	//    2. taille de la population (entier > 0)
	//    3. taux de croisement (0 <= reel <= 1)
	//    4. taux de mutation (0 <= reel <= 1)
	//    5. nombre de villes (=taille d'un chromosome)
	//    6. nom du fichier indiquant les distances entre villes

	// lance l'algorithme �volutionniste
	chromosome* best = algo.optimiser();
	time_t fin = time(NULL);
	// affiche la fitness du meilleur individu trouv�
	cout << "La meilleure solution trouvee est : ";
	best->afficher();

	cout << "Durée de l'execution : " << fin - debut << " secondes" << endl;
}
