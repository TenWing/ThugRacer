/**
 * @file 	conduire_alternatif.h
 * @author	Quentin & Tendry
 * @brief	Header module de conduite alternatif
 */

#ifndef CONDUIRE_ALTERNATIF_H
#define CONDUIRE_ALTERNATIF_H

// Inclusions des structures du pilote
#include <conduire.h>
#include <coordonnee.h>

/**
 * @brief l'ensemble des directions possibles dans le jeu
 */
typedef enum Direction Direction;
enum Direction
{
	GAUCHE, DROITE, BAS, HAUT,
	HAUT_DROITE, HAUT_GAUCHE, BAS_DROITE, BAS_GAUCHE
};

/**
 * @brief un virage dans la course
 */
typedef struct Virage Virage;
struct Virage
{
	/**
	 * @brief le rayon d'action du virage
	 */
	int rayon;

	/**
	 * @brief le point pour le rayon du virage
	 */
	Coordonnee point;

	/**
	 * @brief la direction que doit avoir le véhicule après le virage
	 */
	Direction direction;

	/**
	 * @brief indique si le virage est fini
	 */
	int fini;

	/**
	 * @brief un pointeur vers le virage suivant
	 */
	Virage* suivant;
};

// ##########################UTILS#################################

/**
 * @brief  renvoie un vecteur associé à une direction
 * @param  direction la direction voulue
 * @return           le vecteur x et y
 */
Coordonnee vecteur_direction(Direction direction);

/**
 * @brief  renvoie la direction associée à un vecteur
 * @param  coordonnee le vecteur testé
 * @return            la direction (enum)
 */
Direction direction_vecteur(Coordonnee coordonnee);

/**
 * @brief  calcule le vecteur inverse de celui-donné
 * @param  coordonnee le vecteur à inverser
 * @return            le vecteur inverse
 */
Coordonnee vecteur_inverse(Coordonnee coordonnee);

// ################################################################

/**
 * @brief Construit une liste de virages à partir d'une trajectoire
 * @param  trajectoire la trajectoire
 * @param	carte la carte du jeu
 * @return             une liste de virages
 */
Virage* construire_virages(Trajectoire* trajectoire, Carte carte);

/**
 * @brief  Construit la portée d'action du virage
 * @param  virage      le virage modifié
 * @param  trajectoire le noeud d'action de la trajectoire
 * @param  carte       la piste de jeu
 */
void construire_rayon(Virage* virage, Trajectoire* trajectoire, Carte carte);

/**
 * @brief		Regarde si le pilote a passé la ligne de virage
 *         		et doit donc amorcer celui-ci ou non
 * @param  estimee la coordonnée estimée du prochain tour
 * @param  virage le virage
 * @return        oui ou non
 */
int dans_virage(Coordonnee estimee, Virage* virage);

/**
 * @brief		fait aller le pilote tout droit par rapport à son état
 * @param pilote le pilote modifié
 */
void tout_droit(Pilote* pilote);

/**
 * @brief 			Fait freiner le pilote (avec un vecteur)
 * @param pilote    le pilote
 */
void freiner(Pilote* pilote);

/**
 * @brief fait tourner le pilote
 * @param pilote le pilote qui doit tourner
 * @param virage le virage à négocier
 */
void tourner(Pilote* pilote, Virage* virage);

/**
 * @brief démaaaaaaaaaaaaaaaaaaaaaaarre
 * @param pilote le pilote
 */
void demarre(Pilote* pilote);

/**
 * @brief fait piloter le pilote
 * @param pilote le pilote
 * @param virage la liste des virages
 */
void piloter(Pilote* pilote, Virage* virage);

#endif