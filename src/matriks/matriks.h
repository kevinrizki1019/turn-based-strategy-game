/* Nama file: matriks.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */
/* ADT Matriks of integer digunakan untuk dua kegunaan: */
/* Merepresentasikan peta  */
/* konvensinya: -1 pagar, 0 tidak ada bangunan, id bangunan jika ada bangunan */
/* ADT Matriks didefinisikan sesuai yang ada pada Diktat Struktur Data */
/* Pada modul kali ini hanya digunakan primitif seperlunya*/

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
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori 
   Elemen pada tepi matriks bernilai -1, selainnya 0 */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define ElmtMat(M,i,j) (M).Mem[(i)][(j)]

#endif