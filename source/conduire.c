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
	char c, char essai[30];

	//Variables pour les boucles
	int i=0,j,k,l;

	//Variable pour la multiplication et pour la tranposition char <=> int
	int h=1, permu;

	//Lecture et stockage du fichier
	while(fread(&c, sizeof(char), 1, fichier)==1 && c!='\t')
	{
		essai[i] = c;

		//Stockage de la séparation des deux coordonées
		if(c == ' ')
			l=i;

		i++;
	} 

	//On isole dans la première boucle pour trouver l'abscisse
	for(k=l-1; k>=0; k--)
	{
		permu = essai[k];

		pilote->coordx = pilote->coordx + (permu-48)*h;
		h=h*10;

	}

	h = 1;
	
	//Meme opération pour trouver l'ordonnée
	for(k=i-1; k>l; k--)
	{
		permu = essai[k];

		pilote->coordy = pilote->coordy + (permu-48)*h;
		h=h*10;

	}
	
}

//############################################################################

int determination_direction(Pilote *pilote) {

}

//############################################################################

char* depart_pilote(Pilote *pilote)
{
	if(pilote->carte.matrice[pilote->coordy + pilote->accY - 5][pilote->coordx + pilote->accX])

}

//############################################################################

char *avancer_pilote(Pilote *pilote) {
	return NULL;

}




int deltaCarburantAcceleration(int accX, int accY, int velX, int velY, int dansSable)
{
	int valeur = accX*accX + accY*accY;
	valeur += (int)(sqrt(velX*velX+velY*velY)*3.0/2.0);
	if (dansSable) valeur += 1;
	return -valeur;
}
