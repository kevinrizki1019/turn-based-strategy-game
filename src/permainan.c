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

    for (i=IdxMin;i<=(*Perm).B;i++){
        ADVKATA();
        tipe = CKata.TabKata[1];
        ADVKATA(); x=CKatatoInt();
        ADVKATA(); y=CKatatoInt();
        (*Perm).DaftarBangunan.TB[i] = MakeBANGUNAN(tipe,MakePOINT(x,y));
    }

    /* Input keterhubungan */
}