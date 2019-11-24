/* Nama file: tabbangunan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "tabbangunan.h"

void MakeEmptyTab(TabBANGUNAN *T,int maxel){
    /* KAMUS LOKAL */
    /* ALGORITMA */
    TB(*T) = (ElType*) malloc((maxel+1)*sizeof(ElType));
    MaxEl(*T) = maxel;
    NeffTab(*T) = 0;
}

void DealokasiTab(TabBANGUNAN *T){
    /* KAMUS LOKAL */
    /* ALGORITMA */    
    free(TB(*T));
    MaxEl(*T)=0;
    NeffTab(*T)=0;
}

void TulisIsiTab(TabBANGUNAN T) {
    /* KAMUS LOKAL */
    IdxType i;

    for (i=IdxMin;i<=NeffTab(T);i++){
        printf("%d. ",i);
        TulisBangunan(Elmt(T,i));
        printf("\n");
    }
}