/**
 * @file	carte.h
 * @brief	Définit une carte de jeu, en l'occurence une piste de course
 * @date	05 Avril 2015
 */

#ifndef CARTE_H
#define CARTE_H

#include <stdio.h>

/**
 * @brief	La carte du jeu, correspond à la piste de course
 */
typedef struct Carte Carte;
struct Carte
{
	/**
	 * @brief	La taille de la matrice en X
	 */
	int tailleX;

	/**
	 * @brief	la taille de la matrice en Y
	 */
	int tailleY;

	/**
	 * @brief	la quantité de carburant disposée pour une voiture
	 */
	int carburant;

	/**
	 * @brief	 La carte du jeu correspond à un ensemble de caractères
	 */
	char** matrice;
};

/**
 * @brief  Construit une carte de course
 * @param  tailleX la taille X de la matrice
 * @param  tailleY la taille Y de la matrice
 * @param  carburant la quantité de carburant
 * @return         une carte initialisée
 */
Carte construit_carte(int tailleX, int tailleY, int carburant);

/**
 * @brief désalloue la matrice dynamique d'une carte
 * @param carte la carte à désallouée
 */
void detruire_carte(Carte* carte);

/**
 * @brief  Charge une carteà partir d'un fichier
 * @param  fichier le fichier contenant les informations de la carte 
 * @return        une carte bien chargée
 */
Carte charge_carte(FILE* fichier);

#endif