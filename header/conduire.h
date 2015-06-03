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
#include <star.h>

//###########################################################################
//#####							Definitions								#####
//###########################################################################

typedef struct Pilote
{
	/**
	 * @brief coordonnee_map : les coordonnées du joueur sur la map
	 */
	Coordonnee coordonnee_map;

	/**
	 * @brief coordonnee_acc : les coordonnées du vecteur acceleration
	 */
	Coordonnee coordonnee_acc;

	/**
	 * @brief coordonnee_map : les coordonnées du vecteur vitesse
	 */
	Coordonnee coordonnee_vitesse;

	/**
	 * @brief coordonnee_trajectoire : les coordonnees de la trajectoire récupérée
	 */
	Coordonnee coordonnee_trajectoire;

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

/** 
 * @brief  détermine la position du pilote
 * @param  tab   le tableau ou figure les postiions à remettre en ordre
 * @param  debut indice du tableau
 * @return  la position
 */
int determination_position(char *tab, int debut);
/**
 * @brief permet au pilote de partir au départ
 * @param pilote 
 * @return la position au serveur
 */
void depart_pilote(Pilote *pilote);

/**
 * @brief  determine dans quelle direction doit aller le pilote
 * @param  pilote 
 * @return un entier : correspondant à la direction où aller
 */
int determination_direction(Pilote *pilote);
/**
 * @brief fonction principal du pilote
 * @param pilote 
 * @param trajectoire : la trajectoire idéale à suivre par le pilote
 * @return : les informations à envoyer au serveur
 */
void rouler_pilote(Pilote *pilote, Coordonnee coordonnee, FILE *inf);
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

Coordonnee get_trajectoire_coordonnee(Pilote *pilote, Trajectoire *trajectoire, FILE *inf);

/**
 * @brief 	renvoie la norme du vecteur vitesse au carré
 * @param  x la coordonnée x du vecteur de vitesse
 * @param  y la coordonnée y du vecteur vitesse
 * @return   la noooorme²
 */
int vecteur_vitesse(int x, int y);

int distance(Coordonnee pointA, Coordonnee pointB);

int max(int a, int b);

#endif