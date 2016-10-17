#include <stdio.h>
#include <stdlib.h>
#define SIZEMAX 10000

int main(void)
{
	int color, vertex = 0 ;

	FILE * modele = fopen("modele.txt", "r") ;
    if(modele == NULL) 
    {
        perror("Fichier inexistant") ;
    }
    printf("\n") ;
    printf("Si un modele existe les couleurs sont données d'après le modèle\n") ;
    printf(" ----------------------------------------------\n") ;
    printf("|                   \033[38;01mR\033[00m \033[32;01mG\033[00m \033[36;01mB\033[00m                     |\n") ;
    printf(" ----------------------------------------------\n") ;

    //On place le curseur au niveau du modèle
    fseek(modele, 4, SEEK_SET) ;

    for(int i = 0; i < SIZEMAX; i++)
    {
    	fscanf(modele, "%d", &color);
    	if(i % 3 == 0)
    		vertex++;
    	
    	//La couleur 1 est la couleur Rouge, la seconde Verte, la 3e Bleue
    	if(color > 0)
    	{
    		if(color % 3 == 0)
    		{
    			printf("le sommet %d a la couleur \033[36;01mbleue\033[00m, valeur numérique de la couleur = %d\n", vertex, color) ;
    			//printf("--------------------------------------------------------------------\n") ;
    		}

    		if(color - (3 * (vertex - 1)) == 2)
    		{
    			printf("le sommet %d a la couleur \033[32;01mverte\033[00m, valeur numérique de la couleur = %d\n", vertex, color) ;
    			//printf("--------------------------------------------------------------------\n") ;
    		}

    		if(color % 3 != 0 && color - (3 * (vertex - 1)) != 2)
    		{
    			printf("le sommet %d a la couleur \033[38;01mrouge\033[00m, valeur numérique de la couleur = %d\n", vertex, color) ;
    			//printf("--------------------------------------------------------------------\n") ;
    		}

    	}


    	if(color == 0)
    		break;
    }

    return 0;
}