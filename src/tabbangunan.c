/* Nama file: tabbangunan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "tabbangunan.h"
#include <stdio.h>

BANGUNAN ValTabUndef() {
    BANGUNAN B;
    JenisBangunan(B) = 'X';
    return B;
}

void MakeEmpty (TabBANGUNAN * T){
    int i;
    for (i=1; i<=IdxMax; i++) {
        Elmt(*T,i) = ValTabUndef();
    }
}

void TulisIsiTab(TabBANGUNAN T) {
    int i;
    i = IdxMin;
    while (JenisBangunan(Elmt(T, i)) != 'X' && i <= IdxMax) {
        TulisBangunan(Elmt(T, i));
        printf("\n");
        i++;
    }
}

void CopyTab (TabBANGUNAN Tin, TabBANGUNAN * Tout) {
    IdxType i;

    for (i=GetFirstIdx(Tin); i<=GetLastIdx(Tin); i++) {
        Elmt(*Tout,i) = Elmt(Tin,i);
    }
}