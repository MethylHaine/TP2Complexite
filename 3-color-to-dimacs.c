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

    //Initiatisation
    fprintf(cnf, "p cnf %d %d\n", nb_var, nb_clause) ;

    //Chaque sommet a une couleur
    int i, j ;
    for(i=1 ; i<=nb_var ; i+=3) {
        for(j=i ; j<i+3 ; j++) {
            fprintf(cnf, "%d ", j) ;
        }
        fprintf(cnf, "0\n") ;
    }

    fprintf(cnf, "\n") ;

    fclose(cnf) ;

    return 0 ;

}
