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
#include <star.h>

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

	pilote.coordonnee_map.x = pilote.coordonnee_map.y = 0;
	pilote.coordonnee_acc.x = pilote.coordonnee_acc.y = 0;
	pilote.coordonnee_vitesse.x = pilote.coordonnee_vitesse.y = 0;

	return pilote;

}

//############################################################################

void detruire_pilote(Pilote *pilote) {

	detruire_carte(&(pilote->carte));
}

//############################################################################

void emplacement_pilote(Pilote *pilote, FILE *fichier) {
	
	//Variables pour la lecture du fichier et stockage des caractères dans un tableau
	char c, essai[30];

	int entier[6],i=0,j=0;

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

	if(pilote->coordonnee_map.x == entier[0] && pilote->coordonnee_map.y == entier[1]) {
		pilote->coordonnee_vitesse.x = pilote->coordonnee_vitesse.y = 0;
	}

	pilote->coordonnee_map.x = entier[0];
	pilote->coordonnee_map.y = entier[1];
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

int vecteur_vitesse(int x, int y) {
	return (x*x + y*y);
}

//############################################################################

int distance(Coordonnee pointA, Coordonnee pointB) {
	return sqrt((pointB.x - pointA.x)*(pointB.x - pointA.x) + (pointB.y - pointA.y)*(pointB.y - pointA.y));
}

//############################################################################

int max(int a, int b) {
	if(a<0)
		a=-a;
	if(b<0)
		b=-b;
	if(a<b)
		return b;

	return a;
}
//############################################################################

void depart_pilote(Pilote *pilote) {

	if(pilote->carte.matrice[pilote->coordonnee_map.x + 5][pilote->coordonnee_map.y] == '#') {
		pilote->coordonnee_acc.x++;
	}
	else if(pilote->carte.matrice[pilote->coordonnee_map.x - 5][pilote->coordonnee_map.y] == '#') {
		pilote->coordonnee_acc.x--;
	}
	else if(pilote->carte.matrice[pilote->coordonnee_map.x][pilote->coordonnee_map.y + 5] == '#') {
		pilote->coordonnee_acc.y++;
	}
	else {
		pilote->coordonnee_acc.y--;
	}

	pilote->coordonnee_vitesse.x += pilote->coordonnee_acc.x;
	pilote->coordonnee_vitesse.y += pilote->coordonnee_acc.y;

	pilote->coordonnee_trajectoire.x = pilote->coordonnee_map.x;
	pilote->coordonnee_trajectoire.y = pilote->coordonnee_map.y;

}

//############################################################################
//############################################################################

Coordonnee get_trajectoire_coordonnee(Pilote *pilote, Trajectoire *trajectoire, FILE *inf) {

	Trajectoire *actuel = NULL, *actuel_2 = NULL;
	actuel = trajectoire->suivant;
	actuel_2 = trajectoire;
	Coordonnee output;
	int tmp_distance_1=1000,tmp_distance_2;

	//Recherche parmi la liste des coordonnées à suivre la plus proche du joueur
	while(actuel != NULL)
	{
		tmp_distance_2 = distance(actuel->coordonnees, pilote->coordonnee_map);

		//On teste si la distance trouvée et inférieure à la precedente 
		//et que le joueur ne se trouve pas sur la coordonnée observée
		if(tmp_distance_2 <= tmp_distance_1 && tmp_distance_2 != 0)
		{
			tmp_distance_1 = tmp_distance_2;
			actuel_2 = actuel;
	
		}

		actuel = actuel->suivant;
	}

	//On teste si avec la vitesse du joueur actuel, le pilote peut aller à la coordonnée renvoyée
	if(pilote->carte.matrice[actuel_2->coordonnees.x + pilote->coordonnee_vitesse.x][actuel_2->coordonnees.y + pilote->coordonnee_vitesse.y] == '#') {

		output.x = actuel_2->coordonnees.x;
		output.y = actuel_2->coordonnees.y;

		return output;
	}
	else {
		//Sinon, on renvoie la coordonnée precedente
		output.x = actuel_2->precedent->coordonnees.x;
		output.y = actuel_2->precedent->coordonnees.y;

		return output;
	}
}

//############################################################################

void rouler_pilote(Pilote *pilote, Coordonnee coordonnee, FILE *inf) {

	int tmp_vitesse_X, tmp_vitesse_Y,tmp_acc_X,tmp_acc_Y, sup;
	int i,j;

	//Coordonnées du vecteur vitesse pour aller à la coordonnée donnée en paramètre
	tmp_vitesse_X = coordonnee.x - pilote->coordonnee_map.x;	
	tmp_vitesse_Y = coordonnee.y - pilote->coordonnee_map.y;

	//Ré-initialisation des vecteurs accélérations
	tmp_acc_X = tmp_acc_Y =pilote->coordonnee_acc.x = pilote->coordonnee_acc.y= 0;

	//On normalise le vecteur accélération intermédiaire
	if(tmp_vitesse_X < 0)
		tmp_acc_X = -1;
	if(tmp_vitesse_X > 0)
		tmp_acc_X = 1;
	if(tmp_vitesse_Y < 0)
		tmp_acc_Y = -1;
	if(tmp_vitesse_Y > 0)
		tmp_acc_Y = 1;

	//Si le pilote n'est pas dans le sable
	if(pilote->carte.matrice[pilote->coordonnee_map.x][pilote->coordonnee_map.y] != '~') {
		//Si la vitesse est dans la norme
		if(vecteur_vitesse(pilote->coordonnee_vitesse.x + tmp_acc_X, pilote->coordonnee_vitesse.y + tmp_acc_Y)<25) {

			//Si le pilote peut accélérer
			if(pilote->carte.matrice[pilote->coordonnee_map.x + pilote->coordonnee_vitesse.x + tmp_acc_X]
				[pilote->coordonnee_map.y + pilote->coordonnee_vitesse.y + tmp_acc_Y] == '#') {

				pilote->coordonnee_acc.x = tmp_acc_X;
				pilote->coordonnee_acc.y = tmp_acc_Y;
			}
			//Si le pilote avec sa vitesse, peut aller à la coordonnée donnée
			else if(pilote->carte.matrice[pilote->coordonnee_map.x + pilote->coordonnee_vitesse.x]
				[pilote->coordonnee_map.y + pilote->coordonnee_vitesse.y] == '#' && pilote->coordonnee_vitesse.x !=0
				&& pilote->coordonnee_vitesse.y != 0) {


				pilote->coordonnee_acc.x = 0;
				pilote->coordonnee_acc.y = 0;
			}
			else {


				pilote->coordonnee_acc.x = tmp_acc_X;
				pilote->coordonnee_acc.y = tmp_acc_Y;
			}
			

		}
		
	}
	else {

		//On regarde dans le carré autour du joueur s'il peut trouver un emplacement hors sable
		for(i=pilote->coordonnee_map.x -3; i<=pilote->coordonnee_map.x+3; i++) {
			for(j=pilote->coordonnee_map.y -3; j<=pilote->coordonnee_map.y+3; j++) {

				if(pilote->carte.matrice[i][j] == '#' && vecteur_vitesse(i-pilote->coordonnee_map.x,j-pilote->coordonnee_map.y) == 9 ) {

					//Coordonnées du vecteur vitesse pour aller à la coordonnée donnée en paramètre
					tmp_vitesse_X = i - pilote->coordonnee_map.x;	
					tmp_vitesse_Y = j - pilote->coordonnee_map.y;

					tmp_acc_X = tmp_acc_Y = 0;

					//On normalise le vecteur accélération intermédiaire
					if(tmp_vitesse_X < 0)
						tmp_acc_X = -1;
					if(tmp_vitesse_X > 0)
						tmp_acc_X = 1;
					if(tmp_vitesse_Y < 0)
						tmp_acc_Y = -1;
					if(tmp_vitesse_Y > 0)
						tmp_acc_Y = 1;

					if(vecteur_vitesse(tmp_acc_Y,tmp_acc_X) == 1) {
						pilote->coordonnee_acc.x = tmp_acc_X;
						pilote->coordonnee_acc.y = tmp_acc_Y;

						i=10000;
						j=10000;
					}
					
				}
			}
		}
	}

	//Mise à jour du vecteur vitesse
	pilote->coordonnee_vitesse.x += pilote->coordonnee_acc.x;
	pilote->coordonnee_vitesse.y += pilote->coordonnee_acc.y;


}

//############################################################################
//
/*
//On initialise les coordonnées de l'accélaration si besoin
		//ATTENTION : deplacement de 1 en 1
		if(pilote->coordonnee_vitesse.x != tmp_acc_X)
			pilote->coordonnee_acc.x = tmp_acc_X;
		if(pilote->coordonnee_vitesse.y != tmp_acc_Y)
			pilote->coordonnee_acc.y = tmp_acc_Y;
 */
