#ifndef DEF_HEADER
#define DEF_HEADER

/**
 * \file header.h
 * \brief Header du main
 * \author Le Batard--Polès Erwan
 * \version 12
 */

#include <stdio.h>
#include <stdlib.h>

// Format lancement programme : 
// ./STI [chemin image = img_test.ppm] [transformation = Aucune]
// Donc si on met pas d'argument au programme il chargera l'image de test et fera rien

/**
 * \struct PIXEL 
 * \brief Représentation d'un pixel
 *
 * PIXEL est une structure composée de 3 entiers.
 * Les 3 entiers représentent les 3 couleurs primaires.
 * r : Rouge
 * v : Vert
 * b : Bleu
 */
typedef struct PIXEL PIXEL;
struct PIXEL
{
	int r; /*!< Rouge */
	int g; /*!< Vert */
	int b; /*!< Bleu */
};


typedef struct MATRICE MATRICE;
struct MATRICE
{
	PIXEL ** mat;
	int nb_lig;
	int nb_col;
	int max_val;
};

// Pour ecrire une ligne de séparation dans le terminal
void ligne_separation(const char separateur);

// Pour ouvrir le fichier image
FILE* ouverture_image(const int *argc, char const *argv[]);

//Pour effacer l'ecran selon l'OS
void effacer_ecran();

// Regarde si le fichier est bien constitue
int test_validite_fichier(FILE *file_image);


int lecture_fichier(FILE* file_image, MATRICE * tab_pixels);
void afficher_tab_pixels(MATRICE * tab);
void vider_tab_pixels(MATRICE * tab);

#endif