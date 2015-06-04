#ifndef PILOTER_H
#define PILOTER_H

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
 * @version     1.0 - 4/06/2015
 * 
 */

#include <coordonnee.h>
#include <star.h>
#include <conduire.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Checkpoint Checkpoint;

/**
 * @brief structure d'un virage
 */
struct Checkpoint
{	
	Coordonnee entree;

	Coordonnee sortie;

	Checkpoint *suivant;
};

/**
 * @brief  construire une liste de checkpoint
 * @param  trajectoire 
 * @return  la liste des checkpoints
 */
Checkpoint *construire_checkpoints(Trajectoire *trajectoire);

/**
 * @brief affiche la liste des checkpoints dans un fichier texte
 * @param checkpoint la liste des checkpoints
 */
void affiche_checkpoints(Checkpoint *checkpoint);

/**
 * @brief met à jour les données du pilote venant du serveur
 * @param pilote 
 */
void update_pilote(Pilote *pilote);

/**
 * @brief  fonction principal du pilote
 * @param pilote     
 * @param checkpoint la liste des checkpoints
 */
void rouler(Pilote *pilote, Checkpoint *checkpoint);

/**
 * @brief  fonction déplaçant le pilote de façon linéaire
 * @param pilote     
 * @param coordonnee la coordonnée à atteindre
 */
void aller_au_prochaint_point(Pilote *pilote, Coordonnee coordonnee);

/**
 * @brief  fait ralentir le pilote pour la négociation du virage
 * @param pilote [description]
 */
void ralentir(Pilote *pilote);

#endif