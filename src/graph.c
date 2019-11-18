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
    }
}

adrver SearchVer(GraphBANGUNAN G, infotype X) {
    adrver v;

    v = FirstVer(G);
    while (v != Nil && InfoVer(v) != X) {
        v = NextVer(v);
    }
    return v;
}

adradj SearchAdj(adrver v, infotype X) {
    adradj a;

    a = FirstAdj(v);
    while (a != Nil && InfoAdj(a) != X) {
        a = NextAdj(a);
    }
    return a;
}

infotype GetIdAdj (GraphBANGUNAN G, infotype infoV, int idx) {
    adrver v;
    adradj a;
    int count;

    v = SearchVer(G, infoV);
    a = FirstAdj(v);
    count = 1;
    while (a != Nil && count != idx) {
        a = NextAdj(a);
        count++;
    }

    return InfoAdj(a);
}

void InsVLastAdj (adrver v, infotype X) {
    adradj a, aLast;
    
    a = AlokasiAdj(X);
    if (a != Nil) {
        if (FirstAdj(v) == Nil) {
            FirstAdj(v) = a;
        } else {
            aLast = FirstAdj(v);
            while (NextAdj(aLast) != Nil && InfoAdj(aLast) != X) {
                aLast = NextAdj(aLast);
            }
            if (InfoAdj(aLast) != X) {
                NextAdj(aLast) = a;
            } else {
                // X sudah menjadi adjacent dari v
                DealokasiAdj(&a);
            }
        }
        NextAdj(a) = Nil;
    }

}

void MakeTerhubung(GraphBANGUNAN *G, infotype V1, infotype V2) {
    adrver P1, P2;

    // InsertVLastAdj V2 ke vertice pada G dengan infotype V1
    P1 = SearchVer(*G,V1);
    InsVLastAdj(P1,V2);
    
    // InsertVLastAdj V1 ke vertice pada G dengan infotype V2
    P2 = SearchVer(*G,V2);
    InsVLastAdj(P2,V1);
}

void PrintKeterhubungan(GraphBANGUNAN G)
{
    int i;
    adrver PVer;
    adradj PAdj;
    
    if (FirstVer(G) != Nil) {
        // Iterasi adress vertice
        PVer = FirstVer(G);
        while (PVer != Nil) {
            printf("%d",InfoVer(PVer));
            if (FirstAdj(PVer) != Nil) {
                // Iterasi adress adjacent
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

