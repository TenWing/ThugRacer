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

#ifndef NOEUD_H
#define NOEUD_H

// Constante d'état d'un noeud
#define OPEN 0
#define CLOSE 1
#define UNTREATED 2

#include <coordonnee.h>

/**
 * @brief une case piste du terrain de jeu
 */
typedef struct Noeud Noeud;
struct Noeud
{
	/**
	 * @brief l'id du noeud ans l'openList s'il y est
	 */
	int idOpen;
	
	/**
	 * @brief le coût en déplacement pour aller du départ
	 *        à ce noeud
	 */
	int G;

	/**
	 * @brief la distance estimée entre ce noeud et l'arrivée
	 */
	int H;

	/**
	 * @brief le poids de parcours du noeud (+ = pas bien)
	 */
	int P;

	/**
	 * @brief coordonnées du noeud dans la matrice
	 */
	Coordonnee coordonnees;

	/**
	 * @brief le noeud parent de ce noeud
	 */
	Noeud* parent;

	/**
	 * @brief etat du noeud, si dans l'open list, la close ou encore non traité
	 */
	int etat;
};

/**
 * @brief construit un noeud de l'espace de jeu
 * @param  G la valeur G
 * @param  H la valeur H
 * @param  coordonnees la coordonnée x/y sur la carte
 * @return   un noeud de l'espace de jeu
 */
Noeud construire_noeud(int G, int H, Coordonnee coordonnees);

/**
 * @brief renvoie le cout G entre un noeud et une position
 * @param  depart  le noeud parent
 * @param  arrivee la coordonnée d'arrivée
 * @return         le G cherché
 */
int cout_g(Noeud* depart, Coordonnee arrivee);

#endif