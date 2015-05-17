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

#ifndef LISTE_H
#define LISTE_H

#include <noeud.h>
#include <coordonnee.h>


/**
 * @brief l'open list de l'algorithme A*
 */
typedef struct Liste Liste;
struct Liste
{
	/**
	 * @brief la taille MAX de la liste (quantité de points sur la carte)
	 */
	int taille;

	/**
	 * @brief la valeur d'identifiant a donner a chauqe nouveau noeud
	 */
	int idCourant;

	/**
	 * @brief la quantite de cases dans la liste
	 */
	int quantite;

	/**
	 * @brief identifiant uniques de chaque case, identifiant stocké dans un arbre binaire pour l'optimisation
	 */
	int* ids; 

	/**
	 * @brief le cout F de chaque case identifiée par la position dans le tableau
	 */
	int* coutF;

	/**
	 * @brief les coordonnée X/Y de chaque case identifiée par la position dans le tableau
	 */
	Coordonnee* coordonnees;
};

/**
 * @brief construit une liste avec la taille maximale de celle-ci
 * @param  tailleMax la taille max
 * @return           une liste
 */
Liste construire_liste(int tailleMax);

/**
 * @brief ajoute un noeud dans l'open list
 * @param liste la liste modifiée
 * @param noeud le noeud à ajouter
 */
void ajouter(Liste* liste, Noeud* noeud);

/**
 * @brief supprime le sommet ré-arrange l'open list
 * @param liste la liste modifiée
 */
void supprimer_sommet(Liste* liste);

/**
 * @brief modifie la valeur de F d'un noeud et ré-arrange l'arbre
 * @param liste la liste modifiée
 * @param id    l'id du noeud modifié
 * @param newF  la nouvelle valeur F du noeud
 */
void mise_a_jour(Liste* liste, int id, int newF);

#endif