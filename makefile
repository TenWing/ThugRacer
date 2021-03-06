#By Quune & Tendry

##############################
#MAKEFILE POUR LE PROJET
##############################
#OPTIONS DE COMPILATION
##############################

#############################
#Nom de l'executable final
export EXEC=2pac
export EXEC2=3pac
export EXEC3=2pac_naif
export EXEC4 = 2pac_naif_2.0
##############################
##/////////////////////////////////////////////////

#Compilateur
export CC=gcc

#Options de compilation des .c
export CFLAGS=-Wall

#Nom du dossier des .h
export HEADER_DIR = header

#Noms du dossier des .c
export SOURCE_DIR=source

#Nom du dossier de build (stockage des .o)
export BUILD_DIR=build

#Résolutions des inclusions
export INCLUDEPATH=-I header
###########################

#Nom du dossier de stockage de l'exécutable
export RUN_DIR= output

#Les options pour l'éditions des liens (IMPORTANT LIBRAIRIE DYNAMIQUE)
export LDFLAGS=-I header -lm

#Le dossier de stockage des pilotes de la course 
#export DRIVER_DIR=output
export DRIVER_DIR=../GrandPrixCarburant/drivers

##############################
#Fichiers à compiler
##############################
#Création de la liste des dépendances (.o)
export SRC=$(wildcard $(SOURCE_DIR)/*.c)
export LST= $(foreach one, $(SRC), $(BUILD_DIR)/$(one))
export OBJ= $(LST:.c=.o)

#Dépendance sur les .h aussi !!!
export HDRS=$(wildcard $(HEADER_DIR)/*.h);

##############################
#COMMANDES DE COMPILATION
##############################

#Construction de l'exécutable
all: 								$(RUN_DIR)/$(EXEC) $(RUN_DIR)/$(EXEC2) $(RUN_DIR)/$(EXEC3) $(RUN_DIR)/$(EXEC4)

patch_all:							patch_gp patch_gp_v2 patch_gp_naif patch_gp_naif_2.0

#On va créer les .o pour faire le likage
$(RUN_DIR)/$(EXEC):					$(OBJ)
									@echo "Construction de l'exécutable"
									@$(CC) -o $@ $^ $(LDFLAGS)

#Procédure simple de compilation .c -> .o prise en charge des dossiers d'arrivée/départ
$(BUILD_DIR)/$(SOURCE_DIR)/%.o: 	$(SOURCE_DIR)/%.c $(HDRS)
									@echo "Compilation de $<"									
	 	 	 						@$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDEPATH) 

#commande de nettoyage du projet (suppr les .o)
mrproper:	
									@echo "Nettoyage du projet"
									@rm -rf $(BUILD_DIR)/$(SOURCE_DIR)/*.o
									@rm -rf $(RUN_DIR)/$(EXEC)

#pour lancer l'exécutable final
run:
									@echo "Exécution"	
									@(cd $(RUN_DIR); ./$(EXEC))

#Ajoute le conducteur à la liste des conducteurs possible du grand prix
patch_gp:
									@echo "Ajout de 2pac aux pilotes"
									@rm -rf $(DRIVER_DIR)/$(EXEC)
									@cp $(RUN_DIR)/$(EXEC) $(DRIVER_DIR)

###########################################################################
patch_gp_v2:
									@echo "Ajout de 3pac aux pilotes"
									@rm -rf $(DRIVER_DIR)/$(EXEC2)
									@cp $(RUN_DIR)/$(EXEC2) $(DRIVER_DIR)

v2:									$(RUN_DIR)/$(EXEC2)

source/v2/3pac.o: 					source/v2/3pac.c
									@$(CC) -o $@ -c $^ $(CFLAGS) $(LDFLAGS)

source/v2/conduire_alternatif.o: 	source/v2/conduire_alternatif.c
									@$(CC) -o $@ -c $^ $(CFLAGS) $(LDFLAGS)

$(RUN_DIR)/$(EXEC2):				$(BUILD_DIR)/$(SOURCE_DIR)/carte.o $(BUILD_DIR)/$(SOURCE_DIR)/conduire.o $(BUILD_DIR)/$(SOURCE_DIR)/liste.o $(BUILD_DIR)/$(SOURCE_DIR)/noeud.o $(BUILD_DIR)/$(SOURCE_DIR)/star.o source/v2/conduire_alternatif.o source/v2/3pac.o
									@$(CC) -o $@ $^ $(LDFLAGS)

###########################################################################
patch_gp_naif:
									@echo "Ajout de 2pac_naif aux pilotes"
									@rm -rf $(DRIVER_DIR)/$(EXEC3)
									@cp $(RUN_DIR)/$(EXEC3) $(DRIVER_DIR)

naif:								$(RUN_DIR)/$(EXEC3)

source/naif/2pac_naif.o:			source/naif/2pac_naif.c
									$(CC) -o $@ -c $^ $(CFLAGS) $(LDFLAGS)

source/naif/conduire_naif.o:	 	source/naif/conduire_naif.c
									$(CC) -o $@ -c $^ $(CFLAGS) $(LDFLAGS)

$(RUN_DIR)/$(EXEC3):				$(BUILD_DIR)/$(SOURCE_DIR)/carte.o $(BUILD_DIR)/$(SOURCE_DIR)/liste.o $(BUILD_DIR)/$(SOURCE_DIR)/noeud.o $(BUILD_DIR)/$(SOURCE_DIR)/star.o source/naif/conduire_naif.o source/naif/2pac_naif.o 
									$(CC) -o $@ $^ $(LDFLAGS)

###########################################################################
patch_gp_naif_2.0:
									@echo "Ajout de 2pac_naif_2.0 aux pilotes"
									@rm -rf $(DRIVER_DIR)/$(EXEC4)
									@cp $(RUN_DIR)/$(EXEC4) $(DRIVER_DIR)

naif_2.0:							$(RUN_DIR)/$(EXEC4)

source/naif_2.0/2pac_naif_2.0.o:	source/naif_2.0/2pac_naif_2.0.c
									$(CC) -o $@ -c $^ $(CFLAGS) $(LDFLAGS)

source/naif_2.0/piloter.o:		 	source/naif_2.0/piloter.c
									$(CC) -o $@ -c $^ $(CFLAGS) $(LDFLAGS)

$(RUN_DIR)/$(EXEC4):				$(BUILD_DIR)/$(SOURCE_DIR)/conduire.o $(BUILD_DIR)/$(SOURCE_DIR)/carte.o $(BUILD_DIR)/$(SOURCE_DIR)/liste.o $(BUILD_DIR)/$(SOURCE_DIR)/noeud.o $(BUILD_DIR)/$(SOURCE_DIR)/star.o source/naif_2.0/piloter.o source/naif_2.0/2pac_naif_2.0.o 
									$(CC) -o $@ $^ $(LDFLAGS)



