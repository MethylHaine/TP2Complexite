#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//O(n³)
int * Algo1(int * tab, int n) {
    int * bornes = malloc(sizeof(int)*2) ;
    int i, j, cmp, sommeCourant ;
    int sommeMax = 0 ;

    for(i=0 ; i<n ; i++) {
        //sommeCourant = 0 ;
        for(j=i+1 ; j<n ; j++) {
            sommeCourant = 0 ;
            for(cmp=i ; cmp<=j ; cmp++) {
                sommeCourant += tab[cmp] ;
                if(sommeMax < sommeCourant) {
                    sommeMax = sommeCourant ;
                    bornes[0] = i ;
                    bornes[1] = cmp ;
                }
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
            sommeCourant += tab[j] ;
            if(sommeMax < sommeCourant) {
                bornes[0] = i ;
                bornes[1] = j ;
                sommeMax = sommeCourant ;

            }
        }
    }

    return bornes ;
}

//O(n log n)
int * Algo3(int * tab, int deb, int fin) {

    int mil = (deb + fin) / 2 ;

    int * SSeq = malloc(sizeof(int)*3) ;

    if(deb == fin) {
        SSeq[0] = deb  ;
        SSeq[1] = deb ;
        SSeq[2] = tab[deb] ;
        return SSeq ;
    }

    int * SeqG = Algo3(tab, deb, mil) ;
    int * SeqD = Algo3(tab, mil+1, fin) ;
    int * SeqM = malloc(sizeof(int)*3) ;

    int i ;

    int sommeG = tab[mil], borneInf = mil ;
    int sommeGmax = sommeG ;
    for(i=mil-1 ; i >= deb ; i--) {
        sommeG += tab[i] ;
        if(sommeG >= sommeGmax) {
            sommeGmax = sommeG ;
            borneInf = i ;
        }
    }
    int sommeD = tab[mil+1], borneSup = mil + 1 ;
    int sommeDmax = sommeD ;
    for(i=mil+2 ; i <= fin ; i++) {
        sommeD += tab[i] ;
        if(sommeD >= sommeDmax) {
            sommeDmax = sommeD ;
            borneSup = i ;
        }
    }

    int sommeMilieu = sommeDmax + sommeGmax ;
    if(SeqG[2]>=SeqD[2] && SeqG[2]>=sommeMilieu)
        return SeqG ;
    else if(SeqD[2]>=SeqG[2] && SeqD[2]>=sommeMilieu)
        return SeqD ;
    else {
        SeqM[0] = borneInf ;
        SeqM[1] = borneSup ;
        SeqM[2] = sommeMilieu ;
        return SeqM ;
    }
}

//O(n)
int * Algo4(int * tab, int n) {

    int * bornes = malloc(sizeof(int)*2) ;

    int cmp = 0, imax = 0;


    //--INIT-----------------------//
    while(tab[cmp] < 0 && cmp < n) {
        if(tab[cmp] > tab[imax])
            imax = cmp ;
        cmp++ ;
    }
    if(cmp == n) {
        bornes[0] = imax ;
        bornes[1] = imax ;
        return bornes ;
    }
    //--INIT-----------------------//

    int i, borneInf = cmp ;
    int sommeMax = 0 ;
    int sommeCourant = 0 ;
    for(i=cmp ; i<n ; i++) {
        sommeCourant += tab[i] ;
        if(sommeCourant < 0) {
            sommeCourant = 0 ;
            borneInf = i+1 ;
        }
        if(sommeMax <= sommeCourant) {
            sommeMax = sommeCourant ;
            bornes[0] = borneInf ;
            bornes[1] = i ;
        }
    }
    return bornes ;
}


void affiche_tab(int * tab, int taille) {
    int i ;
    for(i=0 ; i<taille ; i++)
        printf("%d ", tab[i]) ;
    printf("\n") ;
}

int * creerTabRand(int taille) {
    //srand(time(NULL));
    int * tab = malloc(sizeof(int)*taille) ;
    int i ;
    for(i=0 ; i<taille ; i++) {
        tab[i] = rand()%(-101 - 100) -100 ;
    }
    return tab ;
}

int main (int argc, char * argv[]) {

    if(argc != 3) {
        printf("ERROR\nUtilisation : \t%s\t[taille_tab]\t{1,2,3,4}\n", argv[0]) ;
        exit(1) ;
    }

    int * bornes = malloc(sizeof(int)*2) ;
    int * bornesRec = malloc(sizeof(int)*3) ;

    int taille = atoi(argv[1]) ;

    int * tab = creerTabRand(taille) ;
    affiche_tab(tab, taille);

    switch (atoi(argv[2])) {
    case 1 : bornes = Algo1(tab, taille) ;
        affiche_tab(bornes, 2);
        break ;
    case 2 : bornes = Algo2(tab, taille) ;
        affiche_tab(bornes, 2);
        break ;
    case 3 : bornesRec = Algo3(tab, 0, taille-1) ;
        affiche_tab(bornesRec, 3);
        break ;
    case 4 : bornes = Algo4(tab, taille) ;
        affiche_tab(bornes, 2);
        break ;
    default : printf("ERROR\nUtilisation : \t%s\t[taille_tab]\t{1,2,3,4}\n", argv[0]) ;
        exit(1) ;
    }

    return 0 ;
}


