#include <stdio.h>
#include <stdlib.h>
#include "tris.h"

// --- TRI FUSION ---
void fusion(int* tab, int debut, int milieu, int fin){
    int n1 = milieu - debut + 1;
    int n2 = fin - milieu;
    int* G = malloc(n1 * sizeof(int));
    int* D = malloc(n2 * sizeof(int));
    for(int i=0;i<n1;i++) G[i]=tab[debut+i];
    for(int j=0;j<n2;j++) D[j]=tab[milieu+1+j];
    int i=0,j=0,k=debut;
    while(i<n1 && j<n2){
        if(G[i] <= D[j]) tab[k++]=G[i++];
        else tab[k++]=D[j++];
    }
    while(i<n1) tab[k++]=G[i++];
    while(j<n2) tab[k++]=D[j++];
    free(G); free(D);
}

void tri_fusion(int* tab, int debut, int fin){
    if(debut < fin){
        int milieu = (debut+fin)/2;
        tri_fusion(tab, debut, milieu);
        tri_fusion(tab, milieu+1, fin);
        fusion(tab, debut, milieu, fin);
    }
}

// --- TRI RAPIDE ---
int partition(int* tab, int debut, int fin){
    int pivot = tab[fin]; // pivot simple = dernier element (pire cas si deja trie)
    int i = debut-1;
    for(int j=debut;j<fin;j++){
        if(tab[j] <= pivot){
            i++;
            int tmp=tab[i]; tab[i]=tab[j]; tab[j]=tmp;
        }
    }
    int tmp=tab[i+1]; tab[i+1]=tab[fin]; tab[fin]=tmp;
    return i+1;
}

void tri_rapide(int* tab, int debut, int fin){
    if(debut < fin){
        int pi = partition(tab, debut, fin);
        tri_rapide(tab, debut, pi-1);
        tri_rapide(tab, pi+1, fin);
    }
}

void afficher_tab(int* tab, int n){
    for(int i=0;i<n;i++) printf("%d ", tab[i]);
    printf("\\n");
}
