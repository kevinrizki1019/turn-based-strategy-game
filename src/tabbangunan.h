/* Nama file: tabbangunan.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef __TABBANGUNAN_H__
#define __TABBANGUNAN_H__

#include "bangunan.h"

// Banyaknya bangunan, angka disesuain sama spek
#define IdxMax 29 
#define IdxMin 1

typedef struct {
    BANGUNAN TB[IdxMax+1];
} TabBANGUNAN;
/* Tabel of BANGUNAN yang dideklarasikan secara implisit statik

/* ********** SELEKTOR ********** */
#define TI(T)     (T).TI
#define Elmt(T,i) (T).TI[(i)]

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty (TabBANGUNAN * T);
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1. Isi tabel adalah ValTabUndef */

#endif