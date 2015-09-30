#include "header.h"

int main(int argc, char const *argv[])
{
	//Pour effacer l'ecran
	effacer_ecran();

	ligne_separation('=');

	// On ouvre le fichier de l'image
	FILE* file_image = ouverture_image(&argc,argv);
	if(file_image != NULL){
		
		MATRICE tab_pixels;
		if(lecture_fichier(file_image, &tab_pixels)){
						printf("[O]\tLecture du fichier image reussie");
			printf("\tNombre de Colonnes: %d ; Nombre de Lignes: %d ; Valeur Maximal: %d\n",tab_pixels.nb_col,tab_pixels.nb_lig,tab_pixels.max_val);
		}
		else{
			printf("[X]\tProbleme de lecture du fichier image\n");
			return 1;
		}

		afficher_tab_pixels(&tab_pixels);

		// ########################################	
		//  Appels des fonctions de transformation
		// ########################################	

		// On libère le tableau de pixels
		vider_tab_pixels(&tab_pixels);

		// On ferme le fichier quand on a finit de travailler dessus
		fclose(file_image);
	}

	ligne_separation('=');

	return 0; 
} 

void vider_tab_pixels(MATRICE * tab){
	int i;
	// Pour chaque case de la matrice
	for (i=0; i<tab->nb_lig; i++){
		// On libere la memoire allouee dynamiquement
		free(tab->mat[i]);
	printf("ok2\n");

	}
		printf("ok3\n");

	// Puis on libere la memoire allouee pour la premiere dimension de la matrice
	free(tab->mat);
}

int lecture_fichier(FILE* file_image, MATRICE * tab_pixels){
	char char_tmp[80] = "";
	int continuer = 1;
	int col=0;
	int i = 0;
	int j = 0;
	PIXEL pix_tmp;
	PIXEL ** ptr_tab;

	fscanf(file_image,"%s",char_tmp);
	fscanf(file_image,"%d %d",&tab_pixels->nb_col,&tab_pixels->nb_lig);

	ptr_tab = malloc(tab_pixels->nb_lig * sizeof(PIXEL));
	if(ptr_tab == NULL){
		printf("[X]\tErreur d'allocation sur la premiere dimension du tableau de pixels\n");
		return 0;
	}

	for (i=0; i<tab_pixels->nb_lig; i++){
		ptr_tab[i] = malloc(tab_pixels->nb_col * sizeof(PIXEL));
		if(ptr_tab[i] == NULL){
			printf("[X]\tErreur d'allocation sur la deuxieme dimension du tableau de pixels\n");
			for(i=i-1; i>=0; i--)
				free(ptr_tab[i]);
			free(ptr_tab);
			return 0;
		}
	}

	fscanf(file_image,"%d",&tab_pixels->max_val);

	i=0;
	j=0;
	do{
		fscanf(file_image, "%d %d %d", &pix_tmp.r, &pix_tmp.g, &pix_tmp.b);

		ptr_tab[i][j].r = pix_tmp.r;
		ptr_tab[i][j].g = pix_tmp.g;
		ptr_tab[i][j].b = pix_tmp.b;

		if(feof(file_image)) 
			continuer = 0;

		j++;  
		if(j==col-1){
			j = 0;
			i++;
		}

	}while(continuer);

	tab_pixels->mat = ptr_tab;
	return 1;
}

void afficher_tab_pixels(MATRICE * tab){
	ligne_separation('-');
	int lig,col;
	for (lig=0; lig<tab->nb_lig; lig++){
		for (col=0; col<tab->nb_lig; col++){
			printf("%d %d %d\t",tab->mat[lig][col].r,tab->mat[lig][col].g,tab->mat[lig][col].b);
		}	
		printf("\n");
	}
	ligne_separation('-');
}

FILE* ouverture_image(const int *argc, char const *argv[]){

	// Variable contenant le chemin du fichier, par defaut "test.ppm"
	char chemin_img[255] = "./test.ppm";

	// On teste si on a recu un chemin de fichier
	if (*argc >= 2){
		// On rajoute le "./" au debut du chemin si c'est pas fait
		if(argv[1][0] != '.')
			sprintf(chemin_img,"./%s",argv[1]);
		else
			sprintf(chemin_img,"%s",argv[1]);

		//On affiche le chemin qu'on a recu
		printf("[O]\tUn chemin de fichier a ete trouve : %s\n",chemin_img);
	}
	else //Sinon on dit qu'on a rien recu et on donne le chemin par defaut
		printf("[X]\tAucun chemin de fichier trouve, chemin par defaut : %s\n",chemin_img);

	// On ouvre le fichier de l'image
	FILE* fichier = NULL;
	fichier = fopen(chemin_img,"r");

	if(fichier != NULL)
		printf("[O]\tOuverture du fichier image reussie\n");
	else 
		printf("[X]\tOuverture du fichier image rate\n");

	return fichier;
}
/*
int test_validite_fichier(FILE *file_image){

	int valide = 1;
	char char_tmp[80] = "";
	int continuer = 1, i = 1;

	while(continuer){
		fscanf(file_image,"%s",char_tmp);
		if(char_tmp[0] != '#'){
			switch(i){
				case 1 : if(char_tmp != "P3") {
					continuer = 0;
					valide = 0;
				}
				break;


			}
			i++;
		}
	}
	if(valide)
		printf("[O]\tLe fichier est valide\n");
	else 
		printf("[X]\tLe fichier n'est pas valide\n");

	return valide;
}
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