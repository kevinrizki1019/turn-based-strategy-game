/* Nama file: permainan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "permainan.h"
#include "mesinkata.h"
#include <stdio.h>

void BacaKonfigurasi(char NamaFile[],Permainan *Perm){
/*  Membaca konfigurasi file dari 'NamaFile'
    I.S. = 'NamaFile' terdefinisi dan ada
    F.S. = Variabel Perm terinisialisasi */
    /* Kamus */
    int i,j,x,y;
    char tipe;
    

    /* Algoritma */
    STARTKATA(NamaFile);
    (*Perm).N = CKatatoInt();
    ADVKATA();
    (*Perm).M = CKatatoInt();
    ADVKATA();
    (*Perm).B = CKatatoInt();

    MakeEmpty(&DaftarBangunan(*Perm));

    for (i=IdxMin;i<=(*Perm).B;i++){
        ADVKATA();
        tipe = CKata.TabKata[1];
        ADVKATA(); x=CKatatoInt();
        ADVKATA(); y=CKatatoInt();
        Elmt(DaftarBangunan((*Perm)), i) = MakeBANGUNAN(tipe,MakePOINT(x,y));
    }

    /* Input keterhubungan */
}

int main() {
    Permainan P;
    BacaKonfigurasi("../config_map.txt", &P);
    printf("Panjang peta : %d\n", PanjangPeta(P));
    printf("Lebar peta :%d\n", LebarPeta(P));
    printf("Jumlah bangunan: %d\n", JumlahBangunan(P));
    TulisIsiTab(DaftarBangunan(P));
}