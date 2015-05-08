/* -*- c-basic-offset: 3 -*- 
 *
 * ENSICAEN
 * 6 Boulevard Marechal Juin 
 * F-14050 Caen Cedex 
 * 
 * This file is owned by ENSICAEN students
 * No portion of this document may be reproduced, copied
 * or revised without written permission of the authors.
 */ 

/**
 * @author Geliot <quentin.geliot@ecole.ensicaen.fr> 
 * @author Rakotondramasy <tendry.rakotondramasy@ecole.ensicaen.fr> 
 * @version     1.0 - 16/04/2015
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <carte.h>
#include <conduire.h>
#include <math.h>

/**
 * @file conduire.
 *
 * Codes des fonctions assurant le déplacement de la voiture de course
 */

//############################################################################

int deltaCarburantAcceleration(int accX, int accY, int velX, int velY, int dansSable)
{
	int valeur = accX*accX + accY*accY;
	valeur += (int)(sqrt(velX*velX+velY*velY)*3.0/2.0);
	if (dansSable) valeur += 1;
	return -valeur;
}

//############################################################################

Pilote construire_pilote(FILE *fichier) {

	Pilote pilote;

	pilote.carte = charge_carte(fichier);

	pilote.accX = pilote.accY = pilote.velX = pilote.velY = pilote.coordx = pilote.coordy = 0;

	return pilote;

}

//############################################################################

void detruire_pilote(Pilote *pilote) {

	detruire_carte(&(pilote->carte));
}

//############################################################################

void emplacement_pilote(Pilote *pilote, FILE *fichier) {
	
	//Variables pour la lecture du fichier et stockage des caractères dans un tableau
	char c, essai[30],tab[10];

	int entier[6],i=0,j=0,k=0;

	//Lecture et stockage du fichier
	while(fread(&c, sizeof(char), 1, fichier)==1 && c != '\n')
	{
		//Stockage du charactere
		essai[i] = c;

		//Si on a une coordonnée
		if(essai[i] == ' ' || essai[i] == '\t')
		{
			//On la détermine
			entier[j] = determination_position(essai, i-1);

			//On réinitialise pour la prochaine coordonnée
			j++;
			i=-1;
		}
		
		i++;
	} 

	//Détermination de la dernière coordonnée
	entier[j] = determination_position(essai, i-1);

	pilote->coordx = entier[0];
	pilote->coordy = entier[1];
	pilote->carte.matrice[entier[2]][entier[3]] = '*';
	pilote->carte.matrice[entier[4]][entier[5]] = '*';

}

int determination_position(char *tab, int debut) {

	//Variables pour les boucles
	int k;

	//Variable pour la multiplication et pour la tranposition char <=> int
	int h=1, permu,tmp=0;

	//On isole dans la première boucle pour trouver l'abscisse
	for(k=debut; k>=0; k--)
	{
		if(!(tab[k] == '\0' || tab[k] == '\n'))
		{
			permu = tab[k];

			tmp = tmp + (permu-48)*h;
			h=h*10;
		}
	}

	return tmp;

}

//############################################################################

int determination_direction(Pilote *pilote) {



}

//############################################################################

void depart_pilote(Pilote *pilote)
{
	char action[10];

	if(pilote->carte.matrice[pilote->coordy-2][pilote->coordx] == '#') {

		pilote->accY--;
	}

	if(pilote->carte.matrice[pilote->coordy][pilote->coordx+2] == '#') {

		pilote->accX++;
	}

	if(pilote->carte.matrice[pilote->coordy+2][pilote->coordx] == '#') {

		pilote->accY++;
	}

	if(pilote->carte.matrice[pilote->coordy][pilote->coordx-2] == '#') {

		pilote->accX--;
	}

	pilote->velX += pilote->accX;
	pilote->velY += pilote->accY;
	
}

//############################################################################

char *avancer_pilote(Pilote *pilote) {
	return NULL;

}
