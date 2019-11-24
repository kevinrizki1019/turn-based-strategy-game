/* File: driverPermainan.c */
/* Digunakan untuk mengetes primitif pada ADT Permainan */
#include "permainan.h"
#include <stdio.h>

int main() {
    /* Kamus */
    Permainan P;
    int turn;
    /* Algoritma */
    BacaKonfigurasi("../../config_map.txt", &P,false,&turn);
    printf("Panjang peta : %d\n", PanjangPeta(P));
    printf("Lebar peta :%d\n", LebarPeta(P));
    printf("Jumlah bangunan: %d\n", JumlahBangunan(P));
    TulisIsiTab(DaftarBangunan(P));
}