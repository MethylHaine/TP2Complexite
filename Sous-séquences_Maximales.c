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

    int mil = (deb + fin) / 2 ;

    int * SSeq = malloc(sizeof(int)*3) ;

    if(deb == fin) {
        SSeq[0] = deb ;
        SSeq[1] = fin ;
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
    for(i=mil+2 ; i<=fin ; i++) {
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
    while(tab[cmp] < 0 || cmp<n) {
        if(tab[cmp] < tab[imax])
            imax = cmp ;
        cmp++ ;
    }
    if(tab[cmp] < 0) {
        bornes[0] = imax ;
        bornes[1] = imax ;
        return bornes ;
    }

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
    for(i=0 ; i<taille-1 ; i++)
        printf("%d ", tab[i]) ;
    printf("\t%d\n", tab[taille-1]) ;
}


int main (int argc, char *argv[]) {

    int tab[10] = {-10, 23, 600, -1000, -1, 300, 199, -2, 199, -10} ;

    int * sousSeq = Algo3(tab, 0, 9) ;

    affiche_tab(sousSeq, 3);

    return 0 ;
}






