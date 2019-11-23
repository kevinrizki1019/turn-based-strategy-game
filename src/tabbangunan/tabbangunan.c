/* Nama file: tabbangunan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "tabbangunan.h"

void MakeEmptyTab(TabBANGUNAN *T,int maxel){
    TB(*T) = (ElType*) malloc((maxel+1)*sizeof(ElType));
    MaxEl(*T) = maxel;
    NeffTab(*T) = 0;
}

void DealokasiTab(TabBANGUNAN *T){
    free(TB(*T));
    MaxEl(*T)=0;
    NeffTab(*T)=0;
}