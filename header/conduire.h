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
#ifndef CONDUIRE_H
#define CONDUIRE_H

/**
 * @file conduire.h
 *
 * Definitions des fonctions assurant le déplacement de la voiture de course
 */

#include <carte.h>

//###########################################################################
//#####							Definitions								#####
//###########################################################################

typedef struct Pilote
{
	/**
	 * @brief coordx : position abscisse du pilote
	 */
	int coordx;

	/**
	 * @brief coordy : position ordonnée du pilote
	 */
	int coordy;

	/**
	 * @brief accX   : acceleration selon l'abscisse
	 */
	int accX;

	/**
	 * @brief accY   : acceleration selon l'ordonnée
	 */
	int accY;

	/**
	 * @brief velX   : vitesse selon l'abscisse
	 */
	int velX;

	/**
	 * @brief velY   : vitesse selon l'ordonée
	 */
	int velY;

	/**
	 * @brief  carte : la carte du circuit
	 */
	Carte carte;


}Pilote;

//###########################################################################
//#####							Prototypes fonctions					#####
//###########################################################################

/**
 * @brief  construit le pilote de la tean Thugracer !
 * @param  fichier le fichier contenant les informations de la carte 
 * @return le pilote construit
 */
Pilote construire_pilote(FILE *fichier);

/**
 * @brief  detruit un pilote
 * @param pilote : le pilote à détruire
 */
void detruire_pilote(Pilote *pilote);

/**
 * @brief initialise l'emplacement du pilote sur le circuit
 * @param pilote : le pilote de la course
 * @param fichier : le flux d'entrée
 */
void emplacement_pilote(Pilote *pilote, FILE *fichier);
int determination_position(char *tab, int debut);
/**
 * @brief permet au pilote de partir au départ
 * @param pilote 
 * @return la position au serveur
 */
char* depart_pilote(Pilote *pilote);

/**
 * @brief  determine dans quelle direction doit aller le pilote
 * @param  pilote 
 * @return un entier : correspondant à la direction où aller
 */
int determination_direction(Pilote *pilote);
/**
 * fait avancer le pilote en ligne droite
 * @param pilote 
 * @return : les informations à envoyer au serveur
 */
char *avancer_pilote(Pilote *pilote);

/**
 * @brief  depense du carburant à un instant t
 * @param  accX      acceleration selon l'abscisse
 * @param  accY      acceleration selon l'ordonnée
 * @param  velX      vitesse selon l'abscisse
 * @param  velY      vitesse selon l'ordonnée
 * @param  dansSable permet une dépense plus importante du carburant si la voiture est dans le sable
 * @return           le carburant consommé à l'instant t
 */
int deltaCarburantAcceleration(int accX, int accY, int velX, int velY, int dansSable);
#endif