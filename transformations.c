#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"


int binarisation (IMAGE *imageATransfo){

	//Si l'image est en couleur il y a besoin de la passer en niveau de gris
	if(imageATransfo->type == 3 || imageATransfo->type == 6){
		niveauGris(imageATransfo);
	}

	if(imageATransfo->type != 1 && imageATransfo->type != 4){
		int lig, col, seuil = 127;

		//Double boucle pour parcourir tout le tableau
		for(lig = 0; lig<imageATransfo->nb_lig; lig++)
		{
			for(col=0; col<imageATransfo->nb_col; col++){
				//Si la valeur est en dessous du seuil il prend la valeur 0
				if (imageATransfo->mat[lig][col].r < seuil)
				{
					imageATransfo->mat[lig][col].r = 0;
					imageATransfo->mat[lig][col].g = 0;
					imageATransfo->mat[lig][col].b = 0;
				}
				//Si la valeur est en dessous du seuil il prend la valeur 255
				else {
					imageATransfo->mat[lig][col].r = 255;
					imageATransfo->mat[lig][col].g = 255;
					imageATransfo->mat[lig][col].b = 255;
				}
			}
			
		}
	}
	return 1;
}

int negatif(IMAGE *image){
	int lig,col;

	//Double boucle pour parcourir le tableau
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col<image->nb_col;col++){
			//On applique la formule pour changer la valeur de chaque composante
			image->mat[lig][col].r = 255 - (image->mat[lig][col].r);
			image->mat[lig][col].g = 255 - (image->mat[lig][col].g);
			image->mat[lig][col].b = 255 - (image->mat[lig][col].b);
		}
	}
	return 1;
}

int niveauGris(IMAGE *image){
	//On effectue la transformation seulement si l'image est en couleur
	if(image->type == 3 || image->type == 6){
		int gris, lig, col;
		for(lig=0;lig<image->nb_lig;lig++){
			for(col=0;col<image->nb_col;col++){
				gris = (0.3*(image->mat[lig][col].r)) + (0.59*(image->mat[lig][col].g))+(0.11*(image->mat[lig][col].b));
				image->mat[lig][col].r = gris;
				image->mat[lig][col].g = gris;
				image->mat[lig][col].b = gris;
			}
		}
	}
	return 1;
}

int symetrie_verticale (IMAGE *imageATransfo){
	int lig, col;
	PIXEL tmp;

	//Double boucle pour parcourir tout le tableau
	for (lig = 0; lig < imageATransfo->nb_lig / 2; lig++)
	{
		for (col = 0; col < imageATransfo->nb_col; col++)
		{
			//On créer une variable temporaire pour échanger les valeurs des pixels
			tmp = imageATransfo->mat[lig][col];
			imageATransfo->mat[lig][col] = imageATransfo->mat[imageATransfo->nb_lig - lig - 1][col];
			imageATransfo->mat[imageATransfo->nb_lig - lig - 1][col] = tmp;
		}
	}
	return 1;
}

int symetrie_horizontale(IMAGE *image){
	int lig, col;
	PIXEL tmp;
	//Double boucle for pour parcourir le tableau
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col< image->nb_col /2;col++){
			// On met dans une variable temporaire
			tmp=image->mat[lig][col];
			// On met dans le pixel actuel le pixel symétrique par raport à l'axe central vertical
			image->mat[lig][col] = image->mat[lig][image->nb_col -col-1];
			// On met dans le pixel symétrique les valeurs dans le pixel temporaire
			image->mat[lig][ image->nb_col -col-1]	=tmp;
		}
	}
	return 1;
}

int amelioration_du_contraste (IMAGE *imageATransfo){
	//Si l'image est en couleur il y a besoin de la passer en niveau de gris
	if(imageATransfo->type == 3 || imageATransfo->type == 6){
		niveauGris(imageATransfo);
	}

	if(imageATransfo->type != 1 && imageATransfo->type != 4){
		int lig,col, min = imageATransfo->mat[0][0].r, max = imageATransfo->mat[0][0].r;
		printf("min:%d ; max:%d\n", min, max );

		//Recherche du Min et du Max
		for (lig = 0; lig < imageATransfo->nb_lig; lig++)
		{
			for (col = 0; col < imageATransfo->nb_col; col++)
			{
				if (imageATransfo->mat[lig][col].r < min)
					min = imageATransfo->mat[lig][col].r;
				if (imageATransfo->mat[lig][col].r > max)
					max = imageATransfo->mat[lig][col].r;			
			}
		}
				printf("min:%d ; max:%d\n", min, max );


		// On acoluste les valeurs sur l'echelle [0;max]
		for (lig = 0; lig < imageATransfo->nb_lig; lig++)
		{
			for (col = 0; col < imageATransfo->nb_col; col++)
			{
				//On change toutes les composantes avec la formules trouvés dans l'etude theorique
				imageATransfo->mat[lig][col].r = (imageATransfo->max_val * (imageATransfo->mat[lig][col].r - min))/(max-min);
				imageATransfo->mat[lig][col].g = (imageATransfo->max_val * (imageATransfo->mat[lig][col].g - min))/(max-min);
				imageATransfo->mat[lig][col].b = (imageATransfo->max_val * (imageATransfo->mat[lig][col].b - min))/(max-min);
			}
		}
//##########################
//TEMPORAIRE
min = imageATransfo->mat[0][0].r;
 max = imageATransfo->mat[0][0].r;
//Recherche du Min et du Max
		for (lig = 0; lig < imageATransfo->nb_lig; lig++)
		{
			for (col = 0; col < imageATransfo->nb_col; col++)
			{
				if (imageATransfo->mat[lig][col].r < min)
					min = imageATransfo->mat[lig][col].r;
				if (imageATransfo->mat[lig][col].r > max)
					max = imageATransfo->mat[lig][col].r;			
			}
		}
				printf("min:%d ; max:%d\n", min, max );

	}
//##########################

	return 1;
}

int lissage (IMAGE *imageATransfo){
	int lig, col;
	IMAGE copie;
	copie.nb_lig = imageATransfo->nb_lig;
	copie.nb_col = imageATransfo->nb_col;

	//Allocation dynamique de la copie de l'image 
	copie.mat = malloc(copie.nb_lig * sizeof(PIXEL));
	if(copie.mat == NULL){
		printf("[X]\tErreur d'allocation sur la premiere dimension de la copie du tableau de pixels\n");
		return 0;
	}
	for (lig=0; lig<copie.nb_lig; lig++){
		copie.mat[lig] = malloc(copie.nb_col * sizeof(PIXEL));
		
		if(copie.mat[lig] == NULL){
			printf("[X]\tErreur d'allocation sur la deuxieme dimension de la copie du tableau de pixels\n");
			for(lig=lig-1; lig>=0; lig--)
				free(copie.mat[lig]);
			free(copie.mat);
			return 0;
		}
	}

	//On copie l'image de base dans la copie allouée dynamiquement
	for (lig = 0; lig < imageATransfo->nb_lig; lig++)
	{
		for (col = 0; col < imageATransfo->nb_col; col++)
		{
			copie.mat[lig][col] = imageATransfo->mat[lig][col];
		}
	}

	//On commence les choses sérieuses on fait le lissage
	for (lig = 1; lig < imageATransfo->nb_lig - 2; lig++)
	{
		for (col = 1; col < imageATransfo->nb_col - 2; col++)
		{

			imageATransfo->mat[lig][col].r = (  //1ere ligne
												(imageATransfo->mat[lig-1][col-1].r)+(imageATransfo->mat[lig-1][col].r)+(imageATransfo->mat[lig-1][col+1].r)+
												//2eme ligne
												(imageATransfo->mat[lig][col-1].r)+(imageATransfo->mat[lig][col].r)+(imageATransfo->mat[lig][col+1].r)+
												//3eme ligne
												(imageATransfo->mat[lig+1][col-1].r)+(imageATransfo->mat[lig+1][col].r)+(imageATransfo->mat[lig+1][col+1].r))/ 9;

			imageATransfo->mat[lig][col].g = (  //1ere ligne
												(imageATransfo->mat[lig-1][col-1].g)+(imageATransfo->mat[lig-1][col].g)+(imageATransfo->mat[lig-1][col+1].g)+
												//2eme ligne
												(imageATransfo->mat[lig][col-1].g)+(imageATransfo->mat[lig][col].g)+(imageATransfo->mat[lig][col+1].g)+
												//3eme ligne
												(imageATransfo->mat[lig+1][col-1].g)+(imageATransfo->mat[lig+1][col].g)+(imageATransfo->mat[lig+1][col+1].g))/ 9;

			imageATransfo->mat[lig][col].b = (  //1ere ligne
												(imageATransfo->mat[lig-1][col-1].b)+(imageATransfo->mat[lig-1][col].b)+(imageATransfo->mat[lig-1][col+1].b)+
												//2eme ligne
												(imageATransfo->mat[lig][col-1].b)+(imageATransfo->mat[lig][col].b)+(imageATransfo->mat[lig][col+1].b)+
												//3eme ligne
												(imageATransfo->mat[lig+1][col-1].b)+(imageATransfo->mat[lig+1][col].b)+(imageATransfo->mat[lig+1][col+1].b))/ 9;
		}
	}

	//Il faut éventuellement normaliser on sais pas trop 

	vider_tab_pixels(&copie);

	return 1;
}