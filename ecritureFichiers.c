#include "header.h"
#include "inOutFichiers.h"

/**  
 * \file ecritureFichier.c
 * \brief Ecriture des fichiers P1 à P6
 * \author Le Batard--Polès Erwan
 		   Vacheret Alex
 		   Romanet Vincent
 * Ensemble des fonctions d'écriture des fichiers en fonction de leur type
 */

FILE* ouverture_ecriture_fichier_image(const int * typeFichier, const char nomImage[255], const char transformation[255]){

	char chemin[255] = "";

	char nomSansExt[255] = "";
	strncpy(nomSansExt,nomImage,strlen(nomImage)-4);

	// On regarde le type du fichier pour l'ecrire
	if(*typeFichier == 1 || *typeFichier == 4)
		sprintf(chemin,"Images/%s_%s.pbm",transformation, nomSansExt);
	if(*typeFichier == 2 || *typeFichier == 5)
		sprintf(chemin,"Images/%s_%s.pgm",transformation, nomSansExt);
	if(*typeFichier == 3 || *typeFichier == 6)
		sprintf(chemin,"Images/%s_%s.ppm",transformation, nomSansExt);

	// On écrit le chemin auquel se trouve le fichier 
	printf("\tChemin du fichier d'ecriture : %s\n",chemin );

	// On ouvre le fichier une fois qu'il est trouvé 
	FILE *fichier = NULL;
	if(*typeFichier <= 3)
		fichier = fopen(chemin,"w");
	else 
		fichier = fopen(chemin,"wb");

	// On test si l'ouverture a bien fonctionné
	if(fichier == NULL)
		printf("[X]\tOuverture du fichier d'ecriture rate\n");
	else 
		printf("[O]\tOuverture du fichier d'ecriture reussie\n");

	return fichier;
}

int ecriture_fichier(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[255]){

	// On appel la fonction d'écriture qui correspond au type de l'image
	switch(tab_pixels->type){
		case 1:	ecriture_P1(fichier, tab_pixels, nomImage, transformation); break;
		case 2:	ecriture_P2(fichier, tab_pixels, nomImage, transformation); break;
		case 3:	ecriture_P3(fichier, tab_pixels, nomImage, transformation); break;
		case 4:	ecriture_P4(fichier, tab_pixels, nomImage, transformation); break;
		case 5:	ecriture_P5(fichier, tab_pixels, nomImage, transformation); break;
		case 6:	ecriture_P6(fichier, tab_pixels, nomImage, transformation); break;
		default: printf("[X]\tNombre magique du fichier image inconnu\n");  break;
	}
	
	return 1;
} 

int ecriture_P1(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){

	//On affiche le nombre de ligne et de colonne de l'image
	fprintf(fichier, "P1\n%d %d\n", tab_pixels->nb_col, tab_pixels->nb_lig); 

	int lig,col;
	for(lig=0; lig<tab_pixels->nb_lig; lig++){
		for(col=0; col<tab_pixels->nb_col; col++){ 	
			fprintf(fichier, "%d", tab_pixels->mat[lig][col].r);
			if(col % 70 > 60)
				fprintf(fichier,"\n");
			else
				fprintf(fichier," ");
		}
		fprintf(fichier,"\n");
	}

	fclose(fichier);
	return 1;
}

int ecriture_P2(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){
	
	//On affiche le nombre de ligne et de colonne de l'image
	fprintf(fichier, "P2\n%d %d\n%d\n", tab_pixels->nb_col, tab_pixels->nb_lig, tab_pixels->max_val); 

	int lig,col;
	for(lig=0; lig<tab_pixels->nb_lig; lig++){
		for(col=0; col<tab_pixels->nb_col; col++){ 			
			fprintf(fichier, "%d", tab_pixels->mat[lig][col].r);
			if(col % 70 > 60)
				fprintf(fichier,"\n");
			else
				fprintf(fichier," ");
		}
		fprintf(fichier,"\n");
	}

	fclose(fichier);

	return 1;
}

int ecriture_P3(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){
	
	//On affiche le nombre de ligne et de colonne de l'image
	fprintf(fichier, "P3\n%d %d\n%d\n", tab_pixels->nb_col, tab_pixels->nb_lig, tab_pixels->max_val); 

	int lig,col;
	for(lig=0; lig<tab_pixels->nb_lig; lig++){
		for(col=0; col<tab_pixels->nb_col; col++){ 			
			fprintf(fichier, "%d %d %d", tab_pixels->mat[lig][col].r, tab_pixels->mat[lig][col].g, tab_pixels->mat[lig][col].b);
			if(col % 70 > 60)
				fprintf(fichier,"\n");
			else
				fprintf(fichier," ");
		}
		fprintf(fichier,"\n");
	}

	fclose(fichier);

	return 1; 
}

int ecriture_P4(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){
	
	//On affiche le nombre de ligne et de colonne de l'image
	fprintf(fichier, "P4\n%d %d\n", tab_pixels->nb_col, tab_pixels->nb_lig); 
	
	int lig,col;
	for(lig=0; lig<tab_pixels->nb_lig; lig++){
		for(col=0; col<tab_pixels->nb_col; col++){ 		
			fputc(tab_pixels->mat[lig][col].r, fichier);
		}
	}

	fclose(fichier);

	return 1;
}

int ecriture_P5(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){
	
	//On affiche le nombre de ligne et de colonne de l'image
	fprintf(fichier, "P5\n%d %d\n%d\n", tab_pixels->nb_col, tab_pixels->nb_lig, tab_pixels->max_val); 
	
	int lig,col;
	for(lig=0; lig<tab_pixels->nb_lig; lig++){
		for(col=0; col<tab_pixels->nb_col; col++){ 		
			fputc(tab_pixels->mat[lig][col].r, fichier);
		}
	}

	fclose(fichier);

	return 1;
}

int ecriture_P6(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){
	
	//On affiche le nombre de ligne et de colonne de l'image
	fprintf(fichier, "P6\n%d %d\n%d\n", tab_pixels->nb_col, tab_pixels->nb_lig, tab_pixels->max_val); 
	int lig,col;
	for(lig=0; lig<tab_pixels->nb_lig; lig++){
		for(col=0; col<tab_pixels->nb_col; col++){ 		
			fputc(tab_pixels->mat[lig][col].r, fichier);
			fputc(tab_pixels->mat[lig][col].g, fichier);
			fputc(tab_pixels->mat[lig][col].b, fichier);
		}
	}

	fclose(fichier);

	return 1;
}

