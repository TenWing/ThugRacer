/**
 * @file	2pac.c
 * @author	Quentin & Tendry
 * @brief	LE pilote del'équipe ThugRacer récemment embauché au prix faramineux de plus de 56 Millions de US$
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conduire.h>

/**
 * [main description]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[]) {

	//Déclaration de l'instruction à envoyer au serveur
	char *action = (char*) malloc(10*sizeof(char));

	//Construction du pilote
	Pilote pilote = construire_pilote(stdin);

	//Situation du pilote et de ses concurrents
	emplacement_pilote(&pilote, stdin);

	//Determination de la direction lors du départ
	depart_pilote(&pilote);

	//Instruction pour le serveur
	sprintf(action,"%d %d",pilote.accX, pilote.accY);

	pilote.carte.carburant += deltaCarburantAcceleration(pilote.accX, pilote.accY, pilote.velX, pilote.velY, 0);

	fprintf(stdout, "%s\n", action);

	// Vidage du buffer nécessaire.
	fflush(stdout);

	//Debut de la course
	while(!feof(stdin)) {
	
		//Situation du pilote et de ses concurrents
		emplacement_pilote(&pilote, stdin);

		//Le pilote se déplace
		action = rouler_pilote(&pilote);
	
		//Instruction pour le serveur
		pilote.carte.carburant += deltaCarburantAcceleration(pilote.accX, pilote.accY, pilote.velX, pilote.velY, 0);

		fprintf(stdout, "%d %d\n",action[0], action[1]);

		// Vidage du buffer nécessaire.
		fflush(stdout);
	}
	
	//Destruction du pilote
	detruire_pilote(&pilote);
	
	return EXIT_SUCCESS;
}