/**
 * @file	2pac_naif.c
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

	int i,j,n=0;
	Coordonnee dep; 
	Coordonnee end;
	Coordonnee coordonnee;
	Trajectoire* trajectoire = NULL;
	
	//Construction du pilote
	Pilote pilote = construire_pilote(stdin);

	//Situation du pilote et de ses concurrents
	emplacement_pilote(&pilote, stdin);

	dep.x = pilote.coordonnee_map.x; 
	dep.y = pilote.coordonnee_map.y;

	end = recherche_fin_piste(&pilote);

	trajectoire = trouver_chemin(dep, end, pilote.carte);

	depart_pilote(&pilote);

	pilote.carte.carburant += deltaCarburantAcceleration(pilote.coordonnee_acc.x, pilote.coordonnee_acc.y, 
	pilote.coordonnee_vitesse.x, pilote.coordonnee_vitesse.y, 0);


	fprintf(stdout, "%d %d\n",pilote.coordonnee_acc.x, pilote.coordonnee_acc.y);

	// Vidage du buffer nécessaire.
	fflush(stdout);

	//Debut de la course
	while(!(feof(stdin))) 
	{
		
		//Situation du pilote et de ses concurrents
		emplacement_pilote(&pilote, stdin);

		coordonnee = get_trajectoire_coordonnee(&pilote, trajectoire);

		//Le pilote se déplace
		rouler_pilote(&pilote,coordonnee);
	
		//Instruction pour le serveur
		pilote.carte.carburant += deltaCarburantAcceleration(pilote.coordonnee_acc.x, pilote.coordonnee_acc.y, 
			pilote.coordonnee_vitesse.x, pilote.coordonnee_vitesse.y, 0);


		fprintf(stdout, "%d %d\n",pilote.coordonnee_acc.x, pilote.coordonnee_acc.y);

		// Vidage du buffer nécessaire.
		fflush(stdout);

	}

	//Destruction du pilote
	detruire_pilote(&pilote);
	
	return EXIT_SUCCESS;
}