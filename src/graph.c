#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

adrver AlokasiVer (infotype X) {
    adrver P;
    P = (VERTICE*) malloc(sizeof(infotype));
    if (P != Nil) {
        InfoVer(P) = X;
        NextVer(P) = Nil;
        FirstAdj(P) = Nil;
        return P;
    } else {
        return Nil;
    }    
}

adradj AlokasiAdj (infotype X) {
    adradj P;
    P = (ADJ*) malloc(sizeof(infotype));
    if (P != Nil) {
        InfoAdj(P) = X;
        NextAdj(P) = Nil;
        return P;
    } else {
        return Nil;
    }      
}

void DealokasiVer (adrver *P)
{
    free(*P);
}

void DealokasiAdj (adradj *P)
{
    free(*P);
}

void CreateGraph(GraphBANGUNAN *G, int V)
{
    infotype idBangunan;
    adrver P;
    
    FirstVer(*G) = Nil;
    // Mengisi semua vertice dengan metode InsVFirst
    for (idBangunan=V; idBangunan>=1; idBangunan--) {
        P = AlokasiVer(idBangunan);
        if (P != Nil) {
            NextVer(P) = FirstVer(*G);
            FirstVer(*G) = P;
        }
        P = Nil;
    }
}

void PrintKeterhubungan(GraphBANGUNAN G)
{
    int i;
    adrver PVer;
    adradj PAdj;
    
    if (FirstVer(G) != Nil) {
        PVer = FirstVer(G);
        while (PVer != Nil) {
            printf("%d",InfoVer(PVer));
            if (FirstAdj(PVer) != Nil) {
                PAdj = FirstAdj(PVer);
                while (PAdj != Nil) {
                    printf("->%d",InfoAdj(PAdj));
                    PAdj = NextAdj(PAdj);
                }
            }
            printf("\n");
            PVer = NextVer(PVer);           
        }
    }
}

int main() {
    GraphBANGUNAN G1;
    adrver P;

    P = Nil;

    CreateGraph(&G1,6);
    PrintKeterhubungan(G1);
    

    return 0;
}