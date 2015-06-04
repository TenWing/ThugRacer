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
#include <piloter.h>
#include <time.h>

long int temps;


void demarrer_chrono() {
	temps = clock();
}

void stop_chrono(FILE *fichier) {
	long int arret = clock();

	fprintf(fichier, "%f\n", (float) (arret - temps)/CLOCKS_PER_SEC);
}

/**
 * [main description]
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[]) {

	int i,j,n=0;
	Coordonnee end;
	Trajectoire* trajectoire = NULL;

	//Construction du pilote
	Pilote pilote = construire_pilote(stdin);

	//Situation du pilote et de ses concurrents
	emplacement_pilote(&pilote, stdin);

	//Détermination de la ligne d'arrivée
	end = recherche_fin_piste(&pilote);

	//Trajectoire de A*
	trajectoire = trouver_chemin(pilote.coordonnee_map, end, pilote.carte);

	//Détermination des virages
	Checkpoint *checkpoint = construire_checkpoints(trajectoire);

	//Fonction principale du pilote
	rouler(&pilote, checkpoint); 

	//Destruction du pilote
	detruire_pilote(&pilote);
	
	return EXIT_SUCCESS;
}