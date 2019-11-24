/* File: driverBangunan.c */
/* Digunakan untuk mengetes semua primitif pada ADT Bangunan */
#include "bangunan.h"
#include "stdio.h"

int main() {
    /* Kamus */
    BANGUNAN B1;
    POINT P;
    /* Algoritma */
    Absis(P) = 13;
    Ordinat(P) = 2;
    B1 = MakeBANGUNAN('V', P,0);
    TulisBangunan(B1);
    printf("\n");

    printf("%d\n", Pertahanan(B1));
    Pertahanan(B1) = true;
    printf("%d\n", Pertahanan(B1));
    SetPertahanan(&B1);
    printf("%d\n", Pertahanan(B1));

    TulisBangunan(B1);
    printf("\n");
    boolean sukses;
    BANGUNAN B_lama;
    TambahSatuLevel(&B1,&sukses,&B_lama);
    TulisBangunan(B1);
    printf("\n");

    TambahJumlahPasukan(&B1, 10);
    TulisBangunan(B1);
    printf("\n");
    TambahJumlahPasukan(&B1, 10);
    TulisBangunan(B1);
    printf("\n");

    KurangJumlahPasukan(&B1, 20);
    TulisBangunan(B1);
    printf("\n");
    KurangJumlahPasukan(&B1, 20);
    TulisBangunan(B1);
    printf("\n");
    return 0;
} 