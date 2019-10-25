/* Nama file: permainan.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef __PERMAINAN_H__
#define __PERMAINAN_H__

#include "tabbangunan.h"

typedef struct{
    int N,M; // Menyimpan ukuran peta
    int B; // Menyimpan banyak bangunan
    TabBANGUNAN DaftarBangunan; // Menyimpan daftar bangunan
} Permainan;

/* ********** SELEKTOR ********** */
#define PanjangPeta(P) (P).N
#define LebarPeta(P) (P).M
#define JumlahBangunan(P) (P).B
#define DaftarBangunan(P) (P).DaftarBangunan

/* ********** KONSTRUKTOR ********** */



void BacaKonfigurasi(char NamaFile[],Permainan *Perm);
/*  Membaca konfigurasi file dari 'NamaFile'
    I.S. = 'NamaFile' terdefinisi dan ada
    F.S. = Variabel Perm terinisialisasi */

#endif