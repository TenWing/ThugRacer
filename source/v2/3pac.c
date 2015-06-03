/**
 * @file	3pac.c
 * @author	Quentin & Tendry
 * @brief	LE pilote del'équipe ThugRacer récemment embauché au prix faramineux de plus de 56 Millions de US$
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conduire_alternatif.h>
#include <star.h>

/**
 * [main description]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[]) {

	int i,j;
	Coordonnee dep; 
	Coordonnee end;
	Trajectoire* trajectoire = NULL;
	Virage* virages = NULL;
	
	//Construction du pilote
	Pilote pilote = construire_pilote(stdin);

	//Situation du pilote et de ses concurrents
	emplacement_pilote(&pilote, stdin);

	dep.x = pilote.coordonnee_map.x; 
	dep.y = pilote.coordonnee_map.y;

	for(i=0;i<pilote.carte.tailleX;i++)
	{
		for(j=0;j<pilote.carte.tailleY;j++)
		{
			if(pilote.carte.matrice[i][j] == '=')
			{
				end.x = i; 
				end.y = j;
			}
		}
	}

	trajectoire = trouver_chemin(dep, end, pilote.carte);

	virages = construire_virages(trajectoire, pilote.carte);

	FILE *inf = fopen("3pac.txt", "w+");

	fprintf(inf, "coord virage : %d %d\n", virages->point.x, virages->point.y);
	fprintf(inf, "rayon : %d\n", virages->rayon);
	fprintf(inf, "direction : %d\n", virages->direction);
	fprintf(inf, "directionFrein : %d\n", virages->directionFrein);

	// afficher_chemin(trajectoire, pilote.carte, inf);

	//Debut de la course
	demarre(&pilote);

	// On conduit jusqu'à la fin
	piloter(&pilote, virages);

	// Fermeture fichier
	fclose(inf);

	//Destruction du pilote
	detruire_pilote(&pilote);
	
	return EXIT_SUCCESS;
}