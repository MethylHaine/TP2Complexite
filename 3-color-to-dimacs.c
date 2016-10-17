#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

void afficheArete(int * aretes, int taille) {
    printf("%d arêtes créées : \n", taille/2) ;
    for(int i=0 ; i<taille ; i++) {
        printf("%d ", aretes[i]) ;
    }
    printf("\n") ;
}

int* creationAretes(int nb_sommet) {
    srand(time(NULL)) ;
    int adjacents[nb_sommet][nb_sommet] ;
    int nb_aretes = 0 ; 

    //Génération aléatoire des aretes pour chaques sommets distincts et sans doublons
    for(int i=0 ; i<nb_sommet ; i++){
        for(int j=i+1 ; j<nb_sommet ; j++) {
            adjacents[i][j] = rand()%2 ;
            if(adjacents[i][j] == 1) {
                nb_aretes ++ ;
            }
        }
    }
    
    int k=0 ;
    int * aretes = malloc(sizeof(int)*nb_aretes*2 + sizeof(int)) ;
    //Récupération des arêtes dans un tableau comme *argv[]
     for(int i=0 ; i<nb_sommet ; i++){
        for(int j=i+1 ; j<nb_sommet ; j++) {
            if(adjacents[i][j] == 1) {
                aretes[k] = i+1 ;
                aretes[k+1] = j+1 ;
                k += 2 ;
            }
        }
    }
    //Derniere case du tableau à 0 pour signaler la fin des arêtes.
    aretes[k] = 0 ;

    //Décommenter pour afficher les aretes générées
    //afficheArete(aretes, k) ;

    return aretes ;
}

void graphRandom (int nb_sommets, FILE* cnf) {
    int matrice[nb_sommets][3] ;
    int * aretes = creationAretes(nb_sommets) ;
    int taille_aretes = 0 ;

    //Recup la taille d'aretes (nombre d'aretes * 2)
    while(aretes[taille_aretes] != 0) {
        taille_aretes ++ ;
    }

    int nb_aretes = taille_aretes/2 ;
    int nb_var = 3 * nb_sommets ;
    int nb_clause = 3 * nb_aretes + nb_sommets;

    //Initiatisation
    fprintf(cnf, "p cnf %d %d\n", nb_var, nb_clause) ;

    int cmp = 1 ;
    //Chaque sommet a une couleur
    for(int i=0 ; i<nb_sommets ; i++) {
        for(int j=0 ; j<3 ; j++) {
            matrice[i][j] = cmp ;
            cmp ++ ;
            fprintf(cnf, "%d ", matrice[i][j]) ;
        }
        fprintf(cnf, "0\n") ;
    }

    //2 sommets adjacentes n'ont pas la même couleur
    for(int i=1 ; i<taille_aretes ; i+=2) {
        for(int j=0 ; j<3 ; j++) {
            fprintf(cnf, "-%d -%d ", matrice[aretes[i-1]-1][j], matrice[aretes[i]-1][j]) ;
            fprintf(cnf, "0\n") ;
        }
    }
}

int main(int argc, char *argv[]) {

    FILE* cnf = fopen("3-color-to-dimacs.cnf", "w") ;
    if(cnf == NULL) {
        perror("Fichier non trouvé/ouvert") ;
    }

    if(argc > 2) {

        int nb_sommets = atoi(argv[1]) ;
        int nb_aretes = atoi(argv[2]) ;

        int nb_var = 3 * nb_sommets ;
        int nb_clause = 3 * nb_aretes + nb_sommets ;

        int matrice[nb_sommets][3] ;
        int cmp = 1 ;

        //Initiatisation
        fprintf(cnf, "p cnf %d %d\n", nb_var, nb_clause) ;

        //Chaque sommet a une couleur
        for(int i=0 ; i<nb_sommets ; i++) {
            for(int j=0 ; j<3 ; j++) {
                matrice[i][j] = cmp ;
                cmp ++ ;
                fprintf(cnf, "%d ", matrice[i][j]) ;
            }
            fprintf(cnf, "0\n") ;
        }

        //2 sommets adjacentes n'ont pas la même couleur
        for(int i=4 ; i<argc ; i+=2) {
            for(int j=0 ; j<3 ; j++) {
                fprintf(cnf, "-%d -%d ", matrice[atoi(argv[i-1])-1][j], matrice[atoi(argv[i])-1][j]) ;
                fprintf(cnf, "0\n") ;
            }
        }
    }

    else if(argc == 2) {
        graphRandom(atoi(argv[1]), cnf) ;
    }

    else
        perror("Erreur, argument(s) attendu(s)") ;

    fclose(cnf) ;

    //Appel system de minisat et du programme qui détermine la couleur des sommets si un modele existe
    system("minisat 3-color-to-dimacs.cnf modele.txt") ;
    system("./vertex-color modele.txt") ;


    return 0 ;

}