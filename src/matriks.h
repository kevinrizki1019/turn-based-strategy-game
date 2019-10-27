/* Nama file: matriks.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */
/* ADT Matriks of integer digunakan untuk dua kegunaan: */
/* 1. Merepresentasikan keterhubungan tiap bangunan, ukuran matriks B x B, elemennya integer 1 atau 0 */
/* 2. Merepresentasikan peta (sementara sebelum menggunakan ADT Graph */
/*    konvensinya: -1 pagar, 0 tidak ada bangunan, id bangunan jika ada bangunan */

#ifndef __MATRIKS_H__
#define __MATRIKS_H__

// Deinisi menyesuaikan dengan spesifikasi
#define BrsMin 1
#define BrsMax 30 
#define KolMin 1
#define KolMax 30

typedef int indeks; 
typedef int ElTypeMat;
typedef struct {
    ElTypeMat Mem[BrsMax+1][KolMax+1];
    int NBrsEff; 
    int NKolEff; 
} MATRIKS;

/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M);
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define ElmtMat(M,i,j) (M).Mem[(i)][(j)]

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


#endif