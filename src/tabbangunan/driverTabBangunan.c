/* File: driverTabBangunan.c */
/* Digunakan untuk mengetes semua primitif pada ADT TabBangunan */
#include "tabbangunan.h"
#include "stdio.h"

int main() {
    /* KAMUS */
    TabBANGUNAN TB;
    BANGUNAN B;
    /* ALGORITMA*/
    JenisBangunan(B) = 'F';
    JumlahPasukan(B) = 100;
    Level(B)         = 1;
    Pemilik(B)       = 1;
    Pertahanan(B)    = true;
    SudahAttack(B)   = true;
    SudahMove(B)     = true;
    NeffTab(TB) = 2;

    MakeEmptyTab(&TB,27);
    printf("%d",MaxEl(TB));
    DealokasiTab(&TB);
    printf("%d",MaxEl(TB));

    TulisIsiTab(TB);

    return 0;
}