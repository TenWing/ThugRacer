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

	int i;

	carte.tailleX = tailleX;
	carte.tailleY = tailleY;
	carte.carburant = carburant;

	// Allocation de la zone mémoire pour les colonnes
	carte.matrice = (char**) malloc(sizeof(char*)*tailleX);

	// Création et parcours de chaque pointeur
	for(i = 0; i < tailleX; i++)
	{
		// Allocation de la zone mémoire pour les lignes
		carte.matrice[i] = (char*) malloc(sizeof(char)*tailleY);
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
	int tx, ty, carbu, i, j=0;
	char c;

	fscanf(fichier, "%d %d %d", &tx, &ty, &carbu);

	carte = construit_carte(tx, ty, carbu);

	while(fread(&c, sizeof(char), 1, fichier)==1 && c!='\n');

	// Parcours de chaque ligne du circuit
	for (i = 0; i < ty; i++)
	{
		while(fread(&c, sizeof(char), 1, fichier)==1 && c!='\n')
		{
			carte.matrice[j][i] = c;
			j++;
		}
		j=0;
	}

	return carte;
}