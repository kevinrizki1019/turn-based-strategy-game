/* File: driverPoint.c */
/* Digunakan untuk mengetes semua primitif pada ADT Point */

#include "point.h"
#include "stdio.h"

int main() {
    /* KAMUS LOKAL */
    int X;
    int Y;
    POINT P;
    /* ALGORITMA */
    X = 3;
    Y = -1;
    P = MakePOINT(X,Y);
    TulisPOINT(P);
}