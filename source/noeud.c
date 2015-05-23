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
#include <noeud.h>

Noeud construire_noeud(int G, int H, Coordonnee coordonnees)
{
	Noeud noeud;

	noeud.G = G;
	noeud.H = H;
	noeud.coordonnees = coordonnees;

	noeud.P = 0;
	noeud.parent = NULL;
	noeud.etat = UNTREATED;

	return noeud;
}

int cout_g(Noeud* depart, Coordonnee arrivee)
{
	if(!depart)
		return 0;

	if(depart->coordonnees.x == arrivee.x 
		|| depart->coordonnees.y == arrivee.y)
		return depart->G + 10;
	else
		return depart->G + 14;
}