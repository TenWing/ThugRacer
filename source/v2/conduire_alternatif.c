/**
 * @file 	conduire_alternatif.h
 * @author	Quentin & Tendry
 * @brief	Header module de conduite alternatif
 */

#include <stdio.h>
#include <stdlib.h>
#include <conduire.h>
#include <conduire_alternatif.h>

Coordonnee vecteur_direction(Direction direction)
{
	Coordonnee coordonnee;

	switch(direction)
	{
		case HAUT:
			coordonnee.x = 0;
			coordonnee.y = -1;
			break;

		case BAS:
			coordonnee.x = 0;
			coordonnee.y = 1;
			break;

		case GAUCHE:
			coordonnee.x = -1;
			coordonnee.y = 0;
			break;

		case DROITE:
			coordonnee.x = 1;
			coordonnee.y = 0;
			break;

		case HAUT_DROITE:
			coordonnee.x = 1;
			coordonnee.y = -1;
			break;

		case HAUT_GAUCHE:
			coordonnee.x = -1;
			coordonnee.y = -1;
			break;

		case BAS_DROITE:
			coordonnee.x = 1;
			coordonnee.y = 1;
			break;

		default: //BAS_GAUCHE
			coordonnee.x = -1;
			coordonnee.y = 1;
			break;
	}	

	return coordonnee;
}

Direction direction_vecteur(Coordonnee sens)
{
	// haut
	if(sens.y < 0 && sens.x == 0)
	{
		return HAUT;
	}
	// bas
	else if(sens.y > 0 && sens.x == 0)
	{
		return BAS;
	}
	// gauche
	else if(sens.x < 0 && sens.y == 0)
	{
		return GAUCHE;
	}
	// droite
	else if(sens.x > 0 && sens.y == 0)
	{
		return DROITE;
	}
	// haut_droite
	else if(sens.x > 0 && sens.y < 0)
	{
		return HAUT_DROITE;
	}
	// haut_gauche
	else if(sens.x < 0 && sens.y < 0)
	{
		return HAUT_GAUCHE;
	}
	// bas_droite
	else if(sens.x > 0 && sens.y > 0)
	{
		return BAS_DROITE;
	}
	// bas_gauche
	else 
	{
		return BAS_GAUCHE;
	}	
}

Coordonnee vecteur_inverse(Coordonnee coordonnee)
{
	Coordonnee vecteur;

	vecteur.x = coordonnee.x * -1;
	vecteur.y = coordonnee.y * -1;

	return vecteur;
}

Virage* construire_virages(Trajectoire* trajectoire, Carte carte)
{
	// Vecteur indiquant le sens de la trajectoire
	Coordonnee sens;

	// L'ancien sens de la trajectoire
	Coordonnee oldSens;

	// Pointeur sur la trajectoire précédente
	Trajectoire* old = NULL;

	// Pointeur sur la trajectoire courante
	Trajectoire* current = NULL;

	// Les virages !
	Virage* virages = malloc(sizeof(Virage));
	Virage* virage_tmp = virages;

	// Initialisation
	if(!trajectoire)
		return NULL;

	current = trajectoire;
	old = trajectoire;
	oldSens.x = 0; oldSens.y = 0;

	FILE* debug = fopen("construire_virages.txt", "w+");

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
			if(!virage_tmp->suivant)
				virage_tmp->suivant = malloc(sizeof(Virage));
			
			// Construction de la zone du virage
			construire_rayon(virage_tmp, current, carte);

			// Détermination du sens du virage
			virage_tmp->direction = direction_vecteur(sens);
			fprintf(debug, "direction virage %d\n", virage_tmp->direction);
			fprintf(debug, "pos virage %d %d\n", virage_tmp->point.x, virage_tmp->point.y);

			// Virage non terminé par défaut
			virage_tmp->fini = 0;

			// Virage initialisée préparation du suivant
			virage_tmp = virage_tmp->suivant;
		}

		// Sauvegarde de l'ancien sens
		oldSens = sens;

		// Passage au noeud suivant
		old = current;
		current = current->suivant;
	}

	fclose(debug);
	return virages;	
}

void construire_rayon(Virage* virage, Trajectoire* trajectoire, Carte carte)
{
	int xRange = 0, yRange = 0;
	int i = 0, j = 0;

	// Copie du point du virage
	virage->point.x = trajectoire->coordonnees.x;
	virage->point.y = trajectoire->coordonnees.y;

	// Pour construire le rayon on va chercher la portée horizontale
	// puis verticale, on va ensuite prendre la valeur minimale entre ces deux ci
	
	// Scan horizontal vers droite
	i = virage->point.x;
	while(carte.matrice[i][virage->point.y] != '.')
	{
		i++;
		j++;
	}
	xRange = j;

	// Scan horizontal vers gauche
	j = 0;
	i = virage->point.x;
	while(carte.matrice[i][virage->point.y] != '.')
	{
		i--;
		j++;
	}

	// Sauvegarde de la plus grande valeur
	if(j > xRange)
		xRange = j;

	// même raisonnement en vertical
	
	// Scan vertical vers haut
	j = 0;
	i = virage->point.y;
	while(carte.matrice[virage->point.x][i] != '.')
	{
		i--;
		j++;
	}
	yRange = j;

	// Scan Vertical vers bas
	j = 0;
	i = virage->point.y;
	while(carte.matrice[virage->point.x][i] != '.')
	{
		i--;
		j++;
	}

	// Sauvegarde de la plus grande valeur
	if(j > yRange)
		yRange = j;

	// Sauvegarde de la plus petite range
	if(xRange < yRange)
		virage->rayon = xRange;
	else
		virage->rayon = yRange;
}

int dans_virage(Coordonnee estimee, Virage* virage)
{
	return (abs(estimee.x - virage->point.x) + abs(estimee.y - virage->point.y) 
				<= virage->rayon);
}

void freiner(Pilote* pilote)
{
	// On check la direction dans lequel va le pilote
	int x = pilote->coordonnee_vitesse.x;
	int y = pilote->coordonnee_vitesse.y;

	Direction directionPilote = direction_vecteur(pilote->coordonnee_vitesse);
	Coordonnee frein = vecteur_direction(directionPilote);
	frein = vecteur_inverse(frein);	

	// On reste immobilisé si la voiture bouge pas
	if(x == 0 && y == 0)
	{
		pilote->coordonnee_acc.x = 0;
		pilote->coordonnee_acc.y = 0;
		return;
	}

	// On freine !
	pilote->coordonnee_acc.x = frein.x;
	pilote->coordonnee_acc.y = frein.y;
}

void tourner(Pilote* pilote, Virage* virage)
{
	int x = pilote->coordonnee_vitesse.x;
	int y = pilote->coordonnee_vitesse.y;
	Coordonnee sensVirage = vecteur_direction(virage->direction);
	Direction directionPilote = direction_vecteur(pilote->coordonnee_vitesse);

	if(directionPilote == virage->direction)
	{			
		// On regarde bien les cas diagonaux qui sont spécifiques
		if(sensVirage.x != 0 && sensVirage.y != 0)
		{
			// La diagonalité est correctement respectée
			if(abs(x) == abs(y))
				virage->fini = 1;
		}
		else
			virage->fini = 1;			
	}

	if(x > sensVirage.x)
		pilote->coordonnee_acc.x = -1;
	else if(x < sensVirage.x)
		pilote->coordonnee_acc.x = 1;
	else
		pilote->coordonnee_acc.x = 0;

	if(y > sensVirage.y)
		pilote->coordonnee_acc.y = -1;
	else if(y < sensVirage.y)
		pilote->coordonnee_acc.y = 1;
	else
		pilote->coordonnee_acc.y = 0;
}

void tout_droit(Pilote* pilote)
{
	// On check la direction dans lequel va le pilote
	int x = pilote->coordonnee_vitesse.x;
	int y = pilote->coordonnee_vitesse.y;

	// Si voiture immobile on bouge plus
	if(x == 0 && y == 0)
	{
		pilote->coordonnee_acc.x = 0;
		pilote->coordonnee_acc.y = 0;
		return;
	}

	Coordonnee estimee;
	Coordonnee acceleration;
	Direction sensPilote;

	// On check si on va sortir de la route ben on freine
	estimee.x = pilote->coordonnee_map.x + pilote->coordonnee_vitesse.x;
	estimee.y = pilote->coordonnee_map.y + pilote->coordonnee_vitesse.y;
	if(pilote->carte.matrice[estimee.x][estimee.y] == '.' ||
		pilote->carte.matrice[estimee.x][estimee.y] == '~')
	{
		freiner(pilote);
		return;
	}

	// On check si la norme est cappée pour pas trop accélerer
	if(vecteur_vitesse(x,y) > 9)
	{
		pilote->coordonnee_acc.x = 0;
		pilote->coordonnee_acc.y = 0;
		return;
	}

	sensPilote = direction_vecteur(pilote->coordonnee_vitesse);
	acceleration = vecteur_direction(sensPilote);

	pilote->coordonnee_acc.x = acceleration.x;
	pilote->coordonnee_acc.y = acceleration.y;
}

void demarre(Pilote* pilote)
{
	int x = pilote->coordonnee_map.x;
	int y = pilote->coordonnee_map.y;
	
	// On regarde dans les 4 directions droites de départ
	
	// Regarde en haut
	if(y >= 5 && pilote->carte.matrice[x][y-5] == '#')
	{
		pilote->coordonnee_acc.x = 0;
		pilote->coordonnee_acc.y = -1;
	}
	// Regarde en bas
	else if(y<= (pilote->carte.tailleY - 5) && pilote->carte.matrice[x][y+5] == '#')
	{
		pilote->coordonnee_acc.x = 0;
		pilote->coordonnee_acc.y = 1;
	}
	// Regarde a gauche
	else if(x >= 5 && pilote->carte.matrice[x-5][y] == '#')
	{
		pilote->coordonnee_acc.x = -1;
		pilote->coordonnee_acc.y = 0;
	}
	// Regarde a droite
	else
	{
		pilote->coordonnee_acc.x = 1;
		pilote->coordonnee_acc.y = 0;
	}

	//On démarre !!
	fprintf(stdout, "%d %d\n", pilote->coordonnee_acc.x, pilote->coordonnee_acc.y);
	fflush(stdout);
}

void piloter(Pilote* pilote, Virage* virage)
{
	int n = 0;

	while(n < 20)
	{
		//Instruction pour le serveur
		pilote->carte.carburant += deltaCarburantAcceleration(pilote->coordonnee_acc.x, pilote->coordonnee_acc.y, 
			pilote->coordonnee_vitesse.x, pilote->coordonnee_vitesse.y, 0);

		//Mise a jour de la situation du pilote et des adversaires
		emplacement_pilote(pilote, stdin);

		//On fait aller le pilote tout droit par défaut
		tout_droit(pilote);

		// Estimation de la position future du pilote si rien ne bouge
		Coordonnee estimee;
		estimee.x = pilote->coordonnee_vitesse.x + pilote->coordonnee_map.x;
		estimee.y = pilote->coordonnee_vitesse.y + pilote->coordonnee_map.y;

		// Tant qu'il reste des virages à négocier
		if(virage != NULL)
		{

			if(dans_virage(pilote->coordonnee_map, virage)
				|| dans_virage(estimee, virage))
				tourner(pilote, virage);

			if(virage->fini)
				virage = virage->suivant;
		}

		//Mise à jour du vecteur vitesse
		pilote->coordonnee_vitesse.x += pilote->coordonnee_acc.x;
		pilote->coordonnee_vitesse.y += pilote->coordonnee_acc.y;

		fprintf(stdout, "%d %d\n",pilote->coordonnee_acc.x, pilote->coordonnee_acc.y);
		fflush(stdout);
		n++;
	}

}