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

	char action[10];

	Pilote pilote = construire_pilote(stdin);

	while(!feof(stdin)) {
		emplacement_pilote(&pilote, stdin);

	depart_pilote(&pilote);

	sprintf(action,"%d %d",pilote.accX, pilote.accY);

	pilote.carte.carburant += deltaCarburantAcceleration(pilote.accX, pilote.accY, pilote.velX, pilote.velY, 0);

	fprintf(stdout, "%s\n", action);

	fflush(stdout); // Vidage du buffer nécessaire.
	}
	

	detruire_pilote(&pilote);
	
	return EXIT_SUCCESS;
}