/* Nama file: matriks.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef __MATRIKS_H__
#define __MATRIKS_H__

#define BrsMin 1
#define BrsMax 30 
#define KolMin 1
#define KolMax 30

typedef int indeks; 
typedef int ElType;
typedef struct {
    ElType Mem[BrsMax+1][KolMax+1];
    int NBrsEff; 
    int NKolEff; 
} MATRIKS;

void MakeMATRIKS (int NB, int NK, MATRIKS * M);

#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

void BacaMATRIKS (MATRIKS * M, int NB, int NK);

void TulisMATRIKS (MATRIKS M);

#endif