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

#ifndef STAR_H
#define STAR_H

#include <coordonnee.h>
#include <noeud.h>
#include <liste.h>
#include <carte.h>

/**
 * @brief structure pour l'algorithme a étoile
 */
typedef struct Star Star;
struct Star
{
	/**
	 * @brief l'open list de l'algorithme
	 */
	Liste openList;

	/**
	 * @brief la matrice de noeuds
	 */
	Noeud*** noeuds;
};

/**
 * @brief la 
 */
typedef struct Trajectoire Trajectoire;
struct Trajectoire
{
	/**
	 * @brief pointeur vers le point precedent
	 */
	Trajectoire* precedent;

	/**
	 * @brief pointeur vers le point suivant
	 */
	Trajectoire* suivant;

	/**
	 * @brief coords x et y du point
	 */
	Coordonnee coordonnees;
};

/**
 * @brief trouve le chemin le plus court entre deux points d'une carte
 * @param  depart le point de départ
 * @param  fin    le point d'arrivée
 * @param  carte  la carte analysée
 * @return        une liste de coordonnées doublement chaînée
 */
Trajectoire* trouver_chemin(Coordonnee depart, Coordonnee fin, Carte carte);

#endif