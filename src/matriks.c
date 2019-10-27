/* Nama file: matriks.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "matriks.h"

/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M){
    /* Kamus Lokal */
    indeks i,j;

    /* Algoritma */
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
    for (i=0;i<=NB+1;i++){
        for (j=0;j<=NK+1;j++){
            if ((i==0) || (i==NB+1) || (j==0) || (j==NK+1)){
                ElmtMat(*M,i,j) = -1;
            }
            else{
                ElmtMat(*M,i,j) = 0;
            }
        }
    }
}
