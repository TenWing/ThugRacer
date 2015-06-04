#include <piloter.h>
#include <star.h>
#include <conduire.h>
#include <stdio.h>
#include <stdlib.h>

Checkpoint *construire_checkpoints(Trajectoire *trajectoire) {

	// Vecteur indiquant le sens de la trajectoire
	Coordonnee sens;

	// L'ancien sens de la trajectoire
	Coordonnee oldSens;

	// Pointeur sur la trajectoire précédente
	Trajectoire* old = NULL;

	// Pointeur sur la trajectoire courante
	Trajectoire* current = NULL;

	// Les virages !
	Checkpoint* premier = NULL;
	Checkpoint* dernier = NULL;

	// Initialisation
	if(!trajectoire)
		return NULL;

	current = trajectoire;
	old = trajectoire;
	oldSens.x = 0; oldSens.y = 0;

	// Tant qu'on n'est pas au bout de la trajectoire
	while(current)
	{		
		// Mise à jour du sens de la trajectoire
		sens.x = current->coordonnees.x - old->coordonnees.x;
		sens.y = current->coordonnees.y - old->coordonnees.y;

		// Changement de sens = virage !
		if(oldSens.x != sens.x || oldSens.y != sens.y)
		{
			// Construction d'un virage
			if(dernier == NULL) 
				dernier = malloc(sizeof(Checkpoint));
			else {
				dernier->suivant = malloc(sizeof(Checkpoint));
				dernier = dernier->suivant;				
			}

			if(premier == NULL)
				premier = dernier;
			
			
			//Initialisation du checkpoint
			dernier->entree.x = old->coordonnees.x;
			dernier->entree.y = old->coordonnees.y;

			dernier->sortie.x = current->coordonnees.x;
			dernier->sortie.y = current->coordonnees.y;
		}

		// Sauvegarde de l'ancien sens
		oldSens = sens;

		// Passage au noeud suivant
		old = current;
		current = current->suivant;
	}

	return premier;	
}

void affiche_checkpoints(Checkpoint *checkpoint) {

	FILE *fichier = fopen("caca.txt", "w+");
	Checkpoint *actuel = checkpoint;

	while(actuel != NULL) {
			fprintf(fichier, "%p coord %d %d\n", actuel, actuel->entree.x, actuel->entree.y);


		actuel = actuel ->suivant;
	}

	fclose(fichier);


}

void update_pilote(Pilote *pilote) {
	//Instruction pour le serveur
	pilote->carte.carburant += deltaCarburantAcceleration(pilote->coordonnee_acc.x, pilote->coordonnee_acc.y, 
		pilote->coordonnee_vitesse.x, pilote->coordonnee_vitesse.y, 0);

	//Mise a jour de la situation du pilote et des adversaires
	emplacement_pilote(pilote, stdin);
	
	
}

void ralentir(Pilote *pilote) {

	if(pilote->coordonnee_vitesse.x > 0)
		pilote->coordonnee_acc.x = -1;
	else if(pilote->coordonnee_vitesse.x < 0)
		pilote->coordonnee_acc.x = 1;
	else
		pilote->coordonnee_acc.x = 0;

	if(pilote->coordonnee_vitesse.y > 0)
		pilote->coordonnee_acc.y = -1;
	else if(pilote->coordonnee_vitesse.y < 0)
		pilote->coordonnee_acc.y = 1;
	else
		pilote->coordonnee_acc.y = 0;

}

int freiner_ou_accelerer(int vitesse, int distance) {

	if(vitesse == 25) {
		if(distance > 20) 
			return 1;

		return 0;

	}
	else if(16 <= vitesse && vitesse < 25 ) {
		if(distance > 14)
			return 1;

		return 0;
	}
	else if(9 <= vitesse && vitesse < 16 ) {
		if(distance > 9)
			return 1;

		return 0;
	}
	else if(4 <= vitesse && vitesse < 9 ) {
		if(distance > 5) 
			return 1;

		return 0;
	}
	else if(1 <= vitesse && vitesse < 4 ) {
		if(distance > 1)
			return 1;

		return 0;
	}
	else if(vitesse == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void aller_au_prochaint_point(Pilote *pilote, Coordonnee coordonnee) {

	Coordonnee vitesse_tmp;
	int tmp_acc_X=0, tmp_acc_Y=0;

	int x = pilote->coordonnee_map.x;
	int y = pilote->coordonnee_map.y;

	vitesse_tmp.x = coordonnee.x - x;
	vitesse_tmp.y = coordonnee.y - y;

	
	//Calcul de la distance entre la coordonnee et la position du pilote
	int d = distance(coordonnee, pilote->coordonnee_map);

	//Savoir si on freine ou pas
	int choix = freiner_ou_accelerer(vecteur_vitesse(pilote->coordonnee_vitesse.x, pilote->coordonnee_vitesse.y)
														,d);

	if(choix) {

		//On normalise le vecteur accélération intermédiaire
		if(vitesse_tmp.x < 0)
			tmp_acc_X = -1;
		if(vitesse_tmp.x > 0)
			tmp_acc_X = 1;
		if(vitesse_tmp.y < 0)
			tmp_acc_Y = -1;
		if(vitesse_tmp.y > 0)
			tmp_acc_Y = 1;

		if(vecteur_vitesse(pilote->coordonnee_vitesse.x, pilote->coordonnee_vitesse.y) < 16) {
			pilote->coordonnee_acc.x = tmp_acc_X;
			pilote->coordonnee_acc.y = tmp_acc_Y;
		}
		else {
			pilote->coordonnee_acc.x = 0;
			pilote->coordonnee_acc.y = 0;
		}
	}
	else {

		ralentir(pilote);
	}

	//Mise à jour du vecteur vitesse
	pilote->coordonnee_vitesse.x += pilote->coordonnee_acc.x;
	pilote->coordonnee_vitesse.y += pilote->coordonnee_acc.y;
}

void rouler(Pilote *pilote, Checkpoint *checkpoint) {

	int n = 0;

	int x,y;
	

	while(!feof(stdin))
	{
		if(n != 0)
			update_pilote(pilote);

		x = pilote->coordonnee_map.x;
		y = pilote->coordonnee_map.y;

		if(checkpoint != NULL) {

			//Si on est à l'entrée du checkpoint
			if(x == checkpoint->entree.x && y == checkpoint->entree.y ) {

				//On cherche à aller à la sortie du checkpoint
				aller_au_prochaint_point(pilote, checkpoint->sortie, debug);

				checkpoint = checkpoint->suivant;
			}

			else if(x == checkpoint->sortie.x && y == checkpoint->sortie.y) {

				checkpoint = checkpoint->suivant;

				aller_au_prochaint_point(pilote, checkpoint->entree, debug);
			
			}
			else {
				//On cherche à aller à la sortie du checkpoint
				aller_au_prochaint_point(pilote, checkpoint->entree, debug);
			}
		}
		else {
			aller_au_prochaint_point(pilote, pilote->ligne_arrivee, debug);
		}

		fprintf(stdout, "%d %d\n",pilote->coordonnee_acc.x, pilote->coordonnee_acc.y);
		fflush(stdout);
		n++;
	}



}