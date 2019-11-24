/* File: driverGraph.c */
/* Digunakan untuk mengetes semua primitif pada ADT Graph */
#include "graph.h"
#include "stdio.h"

int main() {
    /* KAMUS */
    GraphBANGUNAN G;
    int X;
    /* ALGORITMA */
    CreateGraph(&G,4);
    PrintKeterhubungan(G);
    MakeTerhubung(&G,1,3);
    PrintKeterhubungan(G);
    MakeTerhubung(&G,1,2);
    PrintKeterhubungan(G);
    MakeTerhubung(&G,2,4);
    PrintKeterhubungan(G);
    MakeTerhubung(&G,1,2);
    PrintKeterhubungan(G);

    X = GetIdAdj(G,1,2);
    printf("%d\n",X);

    return 0;
}