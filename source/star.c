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

#include <stdio.h>
#include <stdlib.h>
#include <star.h>
#include <math.h>

Trajectoire* trouver_chemin(Coordonnee depart, Coordonnee fin, Carte carte)
{
	//Creation des structures utilitaires
	int i = 0, j= 0, estimeeG = 0;
	Star star;
	Trajectoire* oldPathPoint = NULL;
	Trajectoire* pathPoint = NULL;
	Noeud* toStore = NULL;
	Noeud* path = NULL;
	Noeud* toInit = NULL;
	Noeud node, arrivee;
	Coordonnee coordonnee, coordInit;

	star.openList = construire_liste(carte.tailleX*carte.tailleY);
	star.noeuds = malloc(carte.tailleX * sizeof(Noeud**));

	for(i = 0; i < carte.tailleX; i++)
	{
		star.noeuds[i] = malloc(carte.tailleY * sizeof(Noeud*));
	}

	// Initialisation ajout du noeud de départ
	node = construire_noeud(0, (fabs(depart.x - fin.x)+fabs(depart.y - fin.y))*10, depart);
	toInit = (Noeud*) malloc(sizeof(Noeud));
	*toInit = node;
	ajouter(&(star.openList), toInit);
	star.noeuds[depart.x][depart.y] = toInit;

	// Initialisation et ajout du noeud d'arrivée
	arrivee = construire_noeud(-1, 0, fin);
	toInit = (Noeud*) malloc(sizeof(Noeud));
	*toInit = arrivee;

	star.noeuds[fin.x][fin.y] = toInit;

	// Arrêt quand chemin trouvé ou PAS de chemin
	while(arrivee.etat != CLOSE || star.openList.quantite == 0)
	{
		//Recupération du noeud le plus intéressant
		coordonnee = star.openList.coordonnees[star.openList.ids[0]];
		toStore = star.noeuds[coordonnee.x][coordonnee.y];
		supprimer_sommet(&(star.openList));

		//Changement de son état
		toStore->etat = CLOSE;

		// Scan des 8 cases autour
		for(i = coordonnee.x - 1; i <= coordonnee.x + 1; i++)
		{
			for(j = coordonnee.y - 1; j <= coordonnee.y + 1; j++)
			{
				// Si case valide
				if(i >= 0 && j >= 0 && i < carte.tailleX && j < carte.tailleY)
				{
					// Si case non initialisée
					if(star.noeuds[i][j] == NULL)
					{
						coordInit.x = i; coordInit.y = j;
						node = construire_noeud(cout_g(toStore, coordInit), (fabs(i - fin.x)+fabs(j - fin.y))*10, coordInit);
						toInit = malloc(sizeof(Noeud));
						*toInit = node;
						star.noeuds[i][j] = toInit;
					}

					// Si case praticable
					if(carte.matrice[i][j] != '.' && star.noeuds[i][j]->etat != CLOSE)
					{
						// Si pas dans open list on l'ajoute
						if(!star.noeuds[i][j]->etat == OPEN)
						{
							// Le père est la case actuellement traitée
							star.noeuds[i][j]->parent = toStore;
							ajouter(&(star.openList), star.noeuds[i][j]);
						}
						// Sinon on regarde si on a trouvé un meilleur chemin jusqu'à cette case
						else
						{
							estimeeG = cout_g(toStore, star.noeuds[i][j]->coordonnees);
							if(estimeeG < star.noeuds[i][j]->G)
							{
								star.noeuds[i][j]->parent = toStore;
								star.noeuds[i][j]->G = estimeeG;
								mise_a_jour(&(star.openList), star.noeuds[i][j]->idOpen, star.noeuds[i][j]->G + star.noeuds[i][j]->H);
							}
						}
					}
				}
			}
		}
	}

	// Cas chemin trouvé
	if(star.openList.quantite > 0)
	{
		// Construction du chemin
		path = star.noeuds[fin.x][fin.y];

		// Construction premier noeud
		if (oldPathPoint == NULL && path != NULL)
		{
			oldPathPoint = (Trajectoire*) malloc(sizeof(Trajectoire));
			oldPathPoint->coordonnees = path->coordonnees;
			oldPathPoint->suivant = NULL;
			path = path->parent;
		}
		else
		{
			while(path!= NULL)
			{
				pathPoint = (Trajectoire*) malloc(sizeof(Trajectoire));
				pathPoint->coordonnees = path->coordonnees;
				pathPoint->precedent = oldPathPoint;
				oldPathPoint->suivant = pathPoint;
				oldPathPoint = pathPoint;
				path = path->parent;
			}
		}		
	}

	return pathPoint;
}