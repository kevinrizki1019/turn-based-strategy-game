/* Nama file: tabbangunan.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel dinamik */
#ifndef __TABBANGUNAN_H__
#define __TABBANGUNAN_H__

#include "../bangunan/bangunan.h"
#include <stdlib.h>

// Banyaknya bangunan, angka disesuain sama spek
#define IdxMin 1 

typedef int IdxType; /* type indeks */
typedef BANGUNAN ElType; /* type elemen tabel */
typedef struct {
    ElType *TB;
    int Neff;
    int MaxEl;
} TabBANGUNAN;
/* Tabel of BANGUNAN yang dideklarasikan secara implisit statik

/* ********** SELEKTOR ********** */
#define TB(T)           (T).TB
#define Elmt(T,i)       (T).TB[(i)]
#define NeffTab(T)      (T).Neff
#define MaxEl(T)        (T).MaxEl

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmptyTab(TabBANGUNAN *T, int maxel);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel + 1 */
void DealokasiTab(TabBANGUNAN *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0; Neff(T)=0 */


#endif
