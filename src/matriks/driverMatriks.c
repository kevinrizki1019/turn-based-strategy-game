/* File: driverMatriks.c */
/* Digunakan untuk mengetes semua primitif pada ADT Matriks */

#include "matriks.h"
#include "stdio.h"

int main() {
    /* KAMUS LOKAL */
    int NB, NK;
    MATRIKS M;
    /* ALGORITMA */
    NB = 10;
    NK = 15;
    MakeMATRIKS (NB, NK, &M);
    printf("%d %d %d \n",NBrsEff(M),NKolEff(M),ElmtMat(M,NBrsEff(M)-2,NBrsEff(M)-3)); 

    return 0;
}