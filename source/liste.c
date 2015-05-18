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
#include <liste.h>
#include <noeud.h>
#include <coordonnee.h>

Liste construire_liste(int tailleMax)
{
	Liste liste;

	liste.taille = tailleMax;
	liste.idCourant = 0;
	liste.quantite = 0;

	liste.ids = calloc(tailleMax, sizeof(int));
	liste.coutF = calloc(tailleMax, sizeof(int));
	liste.coordonnees = calloc(tailleMax, sizeof(Coordonnee));

	return liste;
}

void ajouter(Liste* liste, Noeud* noeud)
{
	int currentPosition, tmp;

	// Ajout à la fin
	liste->ids[liste->quantite] = liste->idCourant;
	noeud->idOpen = liste->idCourant;

	// Ajout des valeurs dans les autres listes
	liste->coutF[liste->idCourant] = noeud->G + noeud->H;
	liste->coordonnees[liste->idCourant] = noeud->coordonnees;

	// On boucle tant que le rangement est pas fini
	currentPosition = liste->quantite;
	while(liste->coutF[liste->idCourant] < liste->coutF[liste->ids[currentPosition/2]]
			&& currentPosition != 0)
	{
		// On échange les identifiants
		tmp = liste->ids[currentPosition/2];
		liste->ids[currentPosition/2] = liste->idCourant;
		liste->ids[currentPosition] = tmp;

		// On continue de regarder mais cette fois pour le noeud parent
		currentPosition /= 2;
	}

	liste->quantite++;
	liste->idCourant++;
}

void supprimer_sommet(Liste* liste)
{
	if(liste->quantite <= 0)
	{
		return;
	}

	int currentPosition, tmp;

	liste->ids[0] = liste->ids[liste->quantite - 1];
	liste->quantite--;

	currentPosition = 1;
	while((liste->coutF[liste->ids[currentPosition-1]] > liste->coutF[liste->ids[currentPosition*2-1]]
			|| liste->coutF[liste->ids[currentPosition-1]] > liste->coutF[liste->ids[currentPosition*2]])
			&& currentPosition-1 < liste->quantite)
	{
		if(liste->coutF[liste->ids[currentPosition*2]] > liste->coutF[liste->ids[currentPosition*2-1]])
		{
			tmp = liste->ids[currentPosition-1];
			liste->ids[currentPosition-1] = liste->ids[currentPosition*2-1];
			liste->ids[currentPosition*2-1] = tmp;
			currentPosition *= 2;
		}
		else
		{
			tmp = liste->ids[currentPosition-1];
			liste->ids[currentPosition-1] = liste->ids[currentPosition*2];
			liste->ids[currentPosition*2] = tmp;
			currentPosition *= 2;
			currentPosition++;
		}
	}
}

void mise_a_jour(Liste* liste, int id, int newF)
{
	int index = 0, tmp = 0;

	// Mise à jour de la nouvelle valeur
	liste->coutF[id] = newF;

	// Recherche dans le tableau d'entier
	while(liste->ids[index] != id)
	{
		index++;
	}

	// On boucle tant que le rangement est pas fini
	while(liste->coutF[id] < liste->coutF[liste->ids[index/2]]
			&& index != 0)
	{
		// On échange les identifiants
		tmp = liste->ids[index/2];
		liste->ids[index/2] = id;
		liste->ids[index] = tmp;

		// On continue de regarder mais cette fois pour le noeud parent
		index /= 2;
	}
}

void affiche_liste(Liste* liste, FILE* output)
{
	int i = 0;

	fprintf(output, "|%d| ", liste->quantite);
	for(i = 0; i < liste->quantite; i++)
	{
		fprintf(output, "%d ", liste->ids[i]);
	}
	fprintf(output, "\n");
}