#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {

    FILE* cnf = fopen("3-color-to-dimacs.cnf", "w") ;
    if(cnf == NULL) {
        perror("Fichier non trouvé/ouvert") ;
    }

    int nb_sommets = atoi(argv[1]) ;
    int nb_aretes = atoi(argv[2]) ;

    int nb_var = 3 * nb_sommets ;
    int nb_clause = 3 * nb_aretes + nb_sommets ;
    int i, j ;

    int matrice[nb_sommets][3] ;
    int cmp = 1 ;

    //Initiatisation
    fprintf(cnf, "p cnf %d %d\n", nb_var, nb_clause) ;

    //Chaque sommet a une couleur
    for(i=0 ; i<nb_sommets ; i++) {
        for(j=0 ; j<3 ; j++) {
            matrice[i][j] = cmp ;
            cmp ++ ;
            fprintf(cnf, "%d ", matrice[i][j]) ;
        }
        fprintf(cnf, "0\n") ;
    }

    //2 aretes adjacentes n'ont pas la même couleur
    for(i=4 ; i<argc ; i+=2) {
        for(j=0 ; j<3 ; j++) {
            fprintf(cnf, "-%d -%d ", matrice[atoi(argv[i-1])-1][j], matrice[atoi(argv[i])-1][j]) ;
            fprintf(cnf, "0\n") ;
        }
    }

    fclose(cnf) ;

    return 0 ;

}
