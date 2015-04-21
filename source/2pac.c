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

	Pilote pilote = construire_pilote(stdin);

	emplacement_pilote(&pilote, stdin);


	detruire_pilote(&pilote);

	
	return EXIT_SUCCESS;
}

/*
	char c;
	int i;
	FILE* debug = fopen("caca4.log","w+"); // Pour le débuggage
	fprintf(debug," === >Carte< === \n");
	//Lecture de la carte droit au but.
	int tx, ty;
	int carburant; // carburant dans le réservoir
	int nbrBoosts = 5; // Nombre de boosts au départ
	// Il y a maintenant lecture du carburant au départ
	fscanf(stdin,"%d %d %d", &tx, &ty,&carburant);
	fprintf(debug,"taille %d x %d\n", tx, ty);
	fprintf(debug,"Carburant de départ %d \n\n",carburant);
	while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n');
	for (i=0; i<ty; i++) { // Lecture de la carte ligne par ligne
		while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n') fprintf(debug,"%c",c);
		fprintf(debug,"\n");
	}	
	fflush(debug);
	fprintf(debug,"\n === Debut Course === \n");
	int tour = 0;
	int accX = 0, accY = 0;
	int velX = 0, velY = 0;
	char action[100];
	char essai[100];
	i=0;
//	while(!feof(stdin)){
		tour++;
		fprintf(debug,"\n === Tour %d === \n", tour);
		//Lecture des positions.
		while(fread(&c, sizeof(char), 1, stdin)==1 && c!='\n')
		{
			essai[i] = c;
			fprintf(debug, "%c", essai[i]);
			i++;
		} 
		//fprintf(debug,"%c",c);
		fprintf(debug,"\n === Action === \n");
		// Pas de prise en compte du sable (pas de mémorisation de la carte)
		//carburant += deltaCarburantAcceleration(accX, accY, velX, velY, 0);
		velX += accX;
		velY += accY;
		//Écriture de l'accélération.
		sprintf(action,"%d %d",accX,accY);
		fprintf(stdout, "%s\n", action);
	//	fprintf(debug, "%s (carburant restant %d)\n", action, carburant);
		fflush(stdout); // Vidage du buffer nécessaire.
		fflush(debug);
//	}
*/