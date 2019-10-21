/* Nama file: bangunan.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "bangunan.h"

#ifndef __TABBANGUNAN_H__
#define __TABBANGUNAN_H__

// Banyaknya bangunan, angka disesuain sama spek
#define IdxMax 29 
#define IdxMin 1

typedef struct {
    BANGUNAN TB[IdxMax+1];
    int Neff;
} TabBANGUNAN;

/* ********** SELEKTOR ********** */
#define Neff(T)   (T).Neff
#define TI(T)     (T).TI
#define Elmt(T,i) (T).TI[(i)]

#endif