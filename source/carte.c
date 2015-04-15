/**
 * @file	carte.c
 * @brief	Code source du module de la carte
 * @date	05 Avril 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <carte.h>

Carte construit_carte(int tailleX, int tailleY, int carburant)
{
	// Création de la carte
	Carte carte;

	int i = 0;

	carte.tailleX = tailleX;
	carte.tailleY = tailleY;
	carte.carburant = carburant;

	// Allocation de la zone mémoire pour les colonnes
	carte.matrice = calloc(sizeof(char*), tailleY);

	// Création et parcours de chaque pointeur
	for(i = 0; i < tailleY; i++)
	{
		// Allocation de la zone mémoire pour les lignes
		carte.matrice[i] = calloc(sizeof(char), tailleX);
	}

	return carte;
}

void detruire_carte(Carte* carte)
{
	int i = 0;

	for(i = 0; i < carte->tailleY; i++)
	{
		free(carte->matrice[i]);
	}

	free(carte->matrice);
	carte->matrice = NULL;
}

Carte charge_carte(FILE* fichier)
{
	Carte carte;
	int tx, ty, carbu, i, j;
	char c;

	// Ouverture d'un fichier de debug
	FILE* debug = fopen("2pacsostrongomg.log", "w+");

	fscanf(fichier, "%d %d %d", &tx, &ty, &carbu);
	fprintf(debug, "%d %d %d\n", tx, ty, carbu);

	carte = construit_carte(tx, ty, carbu);

	// Placement en fin de ligne
	while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n');

	// Parcours de chaque ligne du circuit
	for(i = 0; i < ty; i++)
	{
		for(j = 0; j < tx; j++)
		{
			fscanf(fichier, "%c", &(carte.matrice[i][j]));
		}
	}

	return carte;
}