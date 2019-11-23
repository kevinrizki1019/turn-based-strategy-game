/* Nama file: queueofskill.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef queueofskill_H
#define queueofskill_H

#include "../boolean.h"
#include <stdio.h>
#include <stdlib.h>

/* Konstanta untuk mendefinisikan address tak terdefinisi */

/* Definisi elemen dan address */
typedef int infoQueue;
typedef int addrQueue;   /* indeks tabel */
/* Contoh deklarasi variabel bertype Queue : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct { infoQueue * T;   /* tabel penyimpan elemen */
                 addrQueue HEAD;  /* alamat penghapusan */
                 addrQueue TAIL;  /* alamat penambahan */
                 int MaxElQueue;     /* Max elemen queue */
               } Queue;
/* Definisi Queue kosong: HEAD=0; TAIL=0. */

/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxElQueue(Q) (Q).MaxElQueue

/* ********* Prototype ********* */
boolean IsQueueEmpty (Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsQueueFull (Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxElQueue */
int NBElmtQueue (Queue Q);
/* Mengirim banyak elemen dalam queue */

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxElQueue=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(Queue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQueue(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infoQueue X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void Del (Queue * Q, infoQueue * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = 0ai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

#endif