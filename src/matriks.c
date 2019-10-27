/* Nama file: matriks.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "matriks.h"

/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M){
    /* Kamus Lokal */
    indeks i,j;

    /* Algoritma */
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
    for (i=0;i<=NB+1;i++){
        for (j=0;j<=NK+1;j++){
            if ((i==0) || (i==NB+1) || (j==0) || (j==NK+1)){
                ElmtMat(*M,i,j) = -1;
            }
            else{
                ElmtMat(*M,i,j) = 0;
            }
        }
    }
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl);
/* Melakukan assignment MHsl  MIn */

/* ********** KELOMPOK BACA/TULIS ********** */
/* Gak pake BacaMATRIKS dari ADT karena kita bacanya dari file */
void TulisMATRIKS (MATRIKS M);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
