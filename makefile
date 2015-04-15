#By Quune & Tendry

##############################
#MAKEFILE POUR LE PROJET
##############################
#OPTIONS DE COMPILATION
##############################

#############################
#Nom de l'executable final
export EXEC=2pac
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
export DRIVER_DIR=../drivers

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
all: 								$(RUN_DIR)/$(EXEC)

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