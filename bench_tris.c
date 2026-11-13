#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tris.h"

void remplir_alea(int* t, int n){ for(int i=0;i<n;i++) t[i]=rand()%10000; }
void remplir_trie(int* t, int n){ for(int i=0;i<n;i++) t[i]=i; }
int est_trie(int* t, int n){ for(int i=1;i<n;i++) if(t[i-1]>t[i]) return 0; return 1; }

int main(){
    srand(time(NULL));
    int tailles[] = {1000, 10000, 50000};
    int nb = 3;

    printf("--- Banc de mesures tris ---\\n");
    for(int k=0;k<nb;k++){
        int n = tailles[k];
        int* t1 = malloc(n*sizeof(int));
        int* t2 = malloc(n*sizeof(int));
        
        // Cas 1 : aleatoire
        remplir_alea(t1, n);
        for(int i=0;i<n;i++) t2[i]=t1[i];
        
        clock_t d1 = clock();
        tri_fusion(t1, 0, n-1);
        clock_t f1 = clock();
        
        clock_t d2 = clock();
        tri_rapide(t2, 0, n-1);
        clock_t f2 = clock();
        
        printf("\\nTaille %d - Tableau ALEATOIRE:\\n", n);
        printf("  Tri fusion : %.4f sec | trie=%d\\n", (double)(f1-d1)/CLOCKS_PER_SEC, est_trie(t1,n));
        printf("  Tri rapide : %.4f sec | trie=%d\\n", (double)(f2-d2)/CLOCKS_PER_SEC, est_trie(t2,n));

        // Cas 2 : deja trie (pire cas pour tri rapide)
        remplir_trie(t1, n);
        for(int i=0;i<n;i++) t2[i]=t1[i];

        d1 = clock();
        tri_fusion(t1, 0, n-1);
        f1 = clock();
        
        d2 = clock();
        tri_rapide(t2, 0, n-1);
        f2 = clock();
        
        printf("Taille %d - Tableau DEJA TRIE (pire cas rapide):\\n", n);
        printf("  Tri fusion : %.4f sec\\n", (double)(f1-d1)/CLOCKS_PER_SEC);
        printf("  Tri rapide : %.4f sec\\n", (double)(f2-d2)/CLOCKS_PER_SEC);

        free(t1); free(t2);
    }
    return 0;
}
