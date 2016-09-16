#include <stdio.h>
#include <stdlib.h>

//O(n³)
int * Algo1(int * tab, int n) {
    int * bornes = malloc(sizeof(int)*2) ;
    int i, j, cmp, sommeCourant ;
    int sommeMax = 0 ;

    for(i=0 ; i<n ; i++) {
        sommeCourant = 0 ;
        for(j=i+1 ; j<n ; j++) {
            for(cmp=i ; cmp<=j ; cmp++) {
                if(sommeMax <= sommeCourant + tab[cmp]) {
                    sommeCourant += tab[cmp] ;
                    sommeMax = sommeCourant ;
                    bornes[0] = i ;
                    bornes[1] = cmp ;
                }
                else
                    sommeCourant += tab[cmp] ;
            }
        }
    }
    return bornes ;
}

//O(n²)
int * Algo2(int * tab, int n) {
    int * bornes = malloc(sizeof(int)*2) ;
    int i, j, sommeCourant ;
    int sommeMax = 0 ;
    for(i=0 ; i<n ; i++) {
        sommeCourant = 0 ;
        for(j=i ; j<n ; j++) {
            if(sommeMax <= sommeCourant + tab[j]) {
                bornes[0] = i ;
                bornes[1] = j ;
                sommeCourant += tab[j] ;
                sommeMax = sommeCourant ;

            }
            else
                sommeCourant += tab[j] ;
        }
    }

    return bornes ;
}


//O(n log n)
int * Algo3(int * tab, int deb, int fin) {
    int* borneDeb = malloc(sizeof(int)*2) ;
    int* borneFin = malloc(sizeof(int)*2) ;

    borneDeb = Algo3(tab, 0, fin/2) ;
    borneFin = Algo3(tab, fin/2, fin) ;

    return bornes ;
}

// ALGO 4

/* SommeMax = T[0] ;
        Somme = 0 ;
        cmp = 0	;
        BorneMin, BorneMax = -1 ;

        WHILE T[cmp] < 0 && cmp < N
                IF SommeMax < T[cmp]
                THEN
                        SommeMax = T[cmp]
                        BorneMax = BorneMin = cmp ;
                cmp ++ ;
        FIN WHILE
        IF cmp = N-1
        THEN
                RETURN BorneMin, BorneMax ;


        SommeMax = 0 ;
        BorneMin = cmp ;
        FOR i=cmp à N-1
                IF T[i] >= 0
                THEN
                        SommeMax += T[i]
                        BorneMax = i ;
                ELSE 	IF Somme += T[i] < 0
                        THEN
                                Somme = 0 ;
                                BorneMin = i+1 ;*/

void affiche_tab(int * tab, int taille) {
    int i ;
    for(i=0 ; i<taille ; i++)
        printf("%d ", tab[i]) ;
    printf("\n") ;
}


int main (void) {

    int tab[10] = {-10, -23, -600, -1000, 0, -5, -3, 12, -2005, -2500} ;

    int * sousSeq = Algo2(tab, 10) ;

    affiche_tab(sousSeq, 2);

    return 0 ;
}






