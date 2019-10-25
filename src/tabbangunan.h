/* Nama file: tabbangunan.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef __TABBANGUNAN_H__
#define __TABBANGUNAN_H__

#include "bangunan.h"

// Banyaknya bangunan, angka disesuain sama spek
#define IdxMax 29 
#define IdxMin 1 

typedef int IdxType; /* type indeks */
typedef BANGUNAN ElType; /* type elemen tabel */
typedef struct {
	ElType *TI;
    BANGUNAN_TB[IdxMax+1];
} TabBANGUNAN;
/* Tabel of BANGUNAN yang dideklarasikan secara implisit statik

/* ********** SELEKTOR ********** */
#define TI(T)     (T).TI
#define Elmt(T,i) (T).TI[(i)]

BANGUNAN ValTabUndef();
/* Karena ini make array implisit, array mesti dinisiasi dulu dengan BANGUNAN ValTabUndef */
/* Definisi ValTabUndef: */
/* JenisBangunan(ValTabUndef) = 'X */
/* Atribut lain sembarang */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty (TabBANGUNAN * T);
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1. Isi tabel adalah ValTabUndef */

void Dealokasi(TabBANGUNAN *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0 */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt(TabBANGUNAN T);
/* Mengirimkan banyaknya elemen efektif tabel BANGUNAN */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx(TabBANGUNAN T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
IdxType GetLastIdx(TabBANGUNAN T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid(TabBANGUNAN T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel BANGUNAN */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean IsIdxEff(TabBANGUNAN T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel BANGUNAN */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty(TabBANGUNAN T);
/* Mengirimkan true jika tabel BANGUNAN T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean IsFull(TabBANGUNAN T);
/* Mengirimkan true jika tabel BANGUNAN T penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi(TabBANGUNAN *T);
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
void TulisIsiTab(TabBANGUNAN T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

#endif
