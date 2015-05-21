/**
 * @file	2pac.c
 * @author	Quentin & Tendry
 * @brief	LE pilote del'équipe ThugRacer récemment embauché au prix faramineux de plus de 56 Millions de US$
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conduire.h>
#include <star.h>

/**
 * [main description]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[]) {

	int i,j;
	
	FILE *info = fopen("ici.txt", "w");

	//Construction du pilote
	Pilote pilote = construire_pilote(stdin);

	//Situation du pilote et de ses concurrents
	emplacement_pilote(&pilote, stdin);

	Coordonnee dep; 
	dep.x = pilote.coordx; 
	dep.y = pilote.coordy;
	Coordonnee end;

	for(i=0;i<pilote.carte.tailleY;i++)
	{
		for(j=0;j<pilote.carte.tailleX;j++)
		{
			if(pilote.carte.matrice[j][i] == '=')
			{
				end.x = j; 
				end.y = i;

				j=pilote.carte.tailleX;
				i=pilote.carte.tailleY;
			}
		}
	}

	Trajectoire* trajectoire = trouver_chemin(dep, end, pilote.carte);

	fclose(info);
	//Destruction du pilote
	detruire_pilote(&pilote);
	
	return EXIT_SUCCESS;
}


	
/*
	fprintf(info, "%d\n", pilote.coordx);

	Trajectoire* ptr = NULL;
	Trajectoire* trajectoire = trouver_chemin(dep, end, pilote.carte);
	ptr = trajectoire;

	if(!ptr)
		fprintf(info, "NON T_T\n");

	while(ptr != NULL)
	{
		fprintf(info, "%d %d\n", ptr->coordonnees.x, ptr->coordonnees.y);
		ptr = ptr->suivant;
	}

	
	//Determination de la direction lors du départ
	depart_pilote(&pilote);

	//Instruction pour le serveur
	pilote.carte.carburant += deltaCarburantAcceleration(pilote.accX, pilote.accY, pilote.velX, pilote.velY, 0);

	fprintf(stdout, "%d %d\n", pilote.accX, pilote.accY);

	// Vidage du buffer nécessaire.
	fflush(stdout);

	//Debut de la course
	while(!feof(stdin)) {
	
		//Situation du pilote et de ses concurrents
		emplacement_pilote(&pilote, stdin);

		//Le pilote se déplace
		rouler_pilote(&pilote);
	
		//Instruction pour le serveur
		pilote.carte.carburant += deltaCarburantAcceleration(pilote.accX, pilote.accY, pilote.velX, pilote.velY, 0);

		fprintf(stdout, "%d %d\n", pilote.accX, pilote.accY);

		// Vidage du buffer nécessaire.
		fflush(stdout);
	}
	*/