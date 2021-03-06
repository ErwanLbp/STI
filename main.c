#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"

/**  
 * \file main.c
 * \brief Main
 * \author Le Batard--Polès Erwan
 		   Vacheret Alex
 		   Romanet Vincent
 * Main du programme dans lequel on va effectuer tous les appels de fonction
 */

 int main(int argc, char const *argv[])
 { 
	//Pour effacer l'ecran
 	effacer_ecran();

 	ligne_separation('=');

 	char nomImage[255] = "";
 	char transformation[255] = "";

	// On ouvre le fichier de l'image
 	FILE* file_image = ouverture_lecture_fichier_image(&argc,argv,nomImage,transformation);
 	if(file_image == NULL)
 		return 1;

 	IMAGE tab_pixels;
 	if(lecture_fichier(file_image, &tab_pixels, nomImage)){
 		printf("\tNombre de Colonnes:\t%d\n\tNombre de Lignes:\t%d\n\tValeur Maximal:\t\t%d\n",tab_pixels.nb_col,tab_pixels.nb_lig,tab_pixels.max_val);
 		printf("[O]\tLecture complete du fichier image reussie\n");
 	}
 	else{
 		printf("[X]\tProbleme de lecture du fichier image\n");
 		return 1;
 	}

 	file_image = NULL;

	// ###########################################
	//  Travail des fonctions des transformations
	// ###########################################
	
 	// Raccourcis pour que l'utilisateur rentre la transformation lors de l'execution en ligne de commande
 	int transfoOk = 1;
 	if(strcmp(transformation, "niveauGris") == 0)
 		niveauGris(&tab_pixels);
 	else if(strcmp(transformation, "binarisation") == 0)
 		binarisation(&tab_pixels);
 	else if(strcmp(transformation, "symetrieH") == 0)
 		symetrie_horizontale(&tab_pixels);
 	else if(strcmp(transformation, "symetrieV") == 0)
 		symetrie_verticale(&tab_pixels);
 	else if(strcmp(transformation, "negatif") == 0)
 		negatif(&tab_pixels);
 	else if(strcmp(transformation, "redimensionnement") == 0)
 		redimensionnement(&tab_pixels, argc, argv);
 	else if(strcmp(transformation, "ameliorationContraste") == 0)
 		amelioration_du_contraste(&tab_pixels);
 	else if(strcmp(transformation, "lissage") == 0)
 		lissage(&tab_pixels);
 	else if(strcmp(transformation, "laplacien") == 0)
 		laplacien(&tab_pixels);
 	else if(strcmp(transformation, "gradientSimple") == 0)
 		gradient(&tab_pixels, transformation);
  	else if(strcmp(transformation, "gradientSobel") == 0)
 		gradient(&tab_pixels, transformation);
 	else if(strcmp(transformation, "detectionContoursSobel") == 0)
 		detectionContoursSobel(&tab_pixels);
 	else if(strcmp(transformation, "detectionContoursLaplacien") == 0)
 		detectionContoursLaplacien(&tab_pixels);
 	else if(strcmp(transformation, "reductionBruit") == 0)
		reductionBruit(&tab_pixels);
 	else if(strcmp(transformation, "masqueCustom") == 0)
 		masqueCustom(&tab_pixels, argc, argv);
 	else if(strcmp(transformation, "base") != 0){
 		printf("[X]\tTransformation inexistante\n");
 		transfoOk = 0;
 	}

	// ###########################################

 	if(transfoOk){
 		file_image = ouverture_ecriture_fichier_image(&(tab_pixels.type),nomImage,transformation);

 		if(file_image == NULL)
 			return 1;
 		if(ecriture_fichier(file_image,&tab_pixels,nomImage,transformation))
 			printf("[O]\tEcriture du fichier reussie, transformation sauvegardee\n");
 		else
 			printf("[X]\tEcriture du fichier rate, transformation non sauvegardee\n");
 	}

	// On libère le tableau de pixels
 	vider_tab_pixels(&tab_pixels);

 	ligne_separation('=');

 	return 0;  
 } 

/**
* \fn void vider tab pixel
* \brief Fonction pour faire la binarisation d'une image
* Cette fonction sert à vider un tableau en mémoire afin d'éviter les fuite de mémoire dans le programme
* On l'utilise pour détruire chaque copie par exemple.
*
*/
 void vider_tab_pixels(IMAGE * tab){
 	int i;
	// Pour chaque case de la IMAGE
 	for (i=0; i<tab->nb_lig; i++){
		// On libere la memoire allouee dynamiquement
 		free(tab->mat[i]);
 	}

	// Puis on libere la memoire allouee pour la premiere dimension de la IMAGE
 	free(tab->mat);
 }

/**
* \fn void afficher tab pixel
* \brief Fonction pour afficher une tableau
* Cette fonction afficher un tableau à deux dimensions avec une simple double boucle
*
*/
 void afficher_tab_pixels(const IMAGE * tab){
 	ligne_separation('-');
 	int lig,col;

 	// On parcours tout le tableau pour l'afficher
 	for (lig=0; lig<tab->nb_lig; lig++){
 		for (col=0; col<tab->nb_col; col++){
 			if(tab->type == 3 || tab->type == 6)
 				printf("%d %d %d\t",tab->mat[lig][col].r,tab->mat[lig][col].g,tab->mat[lig][col].b);
 			else
 				printf("%d ", tab->mat[lig][col].r);
 		}	
 		printf("\n");
 	}

 	ligne_separation('-');
 }

/**
* \fn void ligne séparation
* \brief Fonction de séparation
* Simple fonction pour obtenir un résultat plus lisible dans la console ou on affiche les erreurs si il y en a
*
*/
 void ligne_separation(const char separateur){
	// On ecrit 100 fois le caractere recu en argument
 	printf("\n");
 	int i;
 	for (i = 0; i < 100; ++i)
 	{
 		printf("%c",separateur);
 	}
 	printf("\n\n");
 }

/**
* \fn void effacer ecran
* \brief Fonction clear screen
* Petit clear screen au lancement du programme
*
*/
 void effacer_ecran(){
	// Decide de l'OS a la compilation
	#ifdef _WIN32
 	system("cls");
	#elif __unix__ 
 	system("clear");
	#elif __linux__
 	system("clear");
	#endif
 }