/* Nama file: listbangunan.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef __LIST_LINIER_BANGUNAN__
#define __LIST_LINIER_BANGUNAN__

#include "boolean.h"
#include "bangunan.h"
#include "tabbangunan.h"

/* List direpresentasi secara berkait dengan tabel */
typedef BANGUNAN InfoType;
typedef int address; // [IndexMin..IndexMax, Nil]
typedef struct {
	InfoType info;
	address Next;
} ElmtList;

/* TABEL MEMORI UNTUK DAFTAR BANGUNAN, GLOBAL */
#define IndexMin 1
#define IndexMax 29 
#define Nil NULL
/* Nil adalah address tidak terdefinisi, di luar [IndexMin..IndexMax] */
TabBANGUNAN TabMem; 
address FirstAvail;

typedef struct {
	address First;
} List;

#define First(L) (L).First
#define Next(P) TabMem[P].Next
#define Info(P) TabMem[P].Info

/* PROTOTYPE */
boolean MemFull();
/* Mengirimkan true jika memori list sudah "habis": FirstAvail==Nil */  

void InitTab();
/* Prosedur yang sama dengan MakeEmpty dengan beberapa tambahan */
/* I.S. Sembarang. */
/* F.S. TabMem[IndexMin..IndexMax] siap dipakai sebagai elemen list */
/* berkait, Elemen pertama yang available adalah FirstAvail=1. */
/* Next(i)=i+1 untuk i[IndexMin..IndexMax+1], Next(IndexMax)=Nil */

void AllocTab(address *P);
/* Mengambil sebuah elemen siap pakai P pada awal list FirstAvail */
/* I.S. FirstAvail mungkin kosong. */
/* F.S. Jika FirstAvail tidak Nil, P adalah FirstAvail dan */
/* FirstAvail yang baru adalah Next(FirstAvail) */
/* Jika FirstAvail=Nil, P=Nil, */
/* tulis pesan “Tidak tersedia lagi elemen siap pakai” } */

void DeAllocTab (address P)
// { Mengembalikan sebuah elemen P pada awal list FirstAvail}
// { I.S. FirstAvail mungkin kosong. P tidak Nil. }
// { F.S. FirstAvail = P }

/* UBAH BAWAH INI */
/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, BANGUNAN X);
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, BANGUNAN X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLast (List *L, BANGUNAN X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, BANGUNAN *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLast (List *L, BANGUNAN *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
void InsertAfter (List *L, address P, address Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLast (List *L, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelP (List *L, BANGUNAN X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void DelLast (List *L, address *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
void DelAfter (List *L, address *Pdel, address Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

/****************** PROSES SEMUA ELEMEN LIST ******************/
int NbElmtList (List L);
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */

#endif