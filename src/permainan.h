/* Nama file: permainan.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef __PERMAINAN_H__
#define __PERMAINAN_H__

#include "mesinkata.h"
#include "tabbangunan.h"
#include "matriks.h"
#include "listbangunan.h"
#include "graph.h"
#include "queueofskill.h"
#include "color.h"

typedef struct{
    List ListBangunan;
    Queue QueueSkill;
} Player;

typedef struct{
    TabBANGUNAN DaftarBangunan; // Menyimpan daftar bangunan
    MATRIKS Peta;
    Player Player1;
    Player Player2;
    GraphBANGUNAN G;
} Permainan;

/* ********** SELEKTOR ********** */
#define TinggiPeta(P) (P).Peta.NBrsEff
#define LebarPeta(P) (P).Peta.NKolEff
#define JumlahBangunan(P) (P).DaftarBangunan.Neff
#define DaftarBangunan(P) (P).DaftarBangunan
#define Peta(P) (P).Peta
#define ListBangunanP1(P) (P).Player1.ListBangunan
#define ListBangunanP2(P) (P).Player2.ListBangunan
#define SkillP1(P) (P).Player1.QueueSkill
#define SkillP2(P) (P).Player2.QueueSkill
#define Graph(P) (P).G

void BacaKonfigurasi(char NamaFile[],Permainan *Perm);
/*  Membaca konfigurasi file dari 'NamaFile'
    I.S. = 'NamaFile' terdefinisi dan ada
    F.S. = Variabel Perm terinisialisasi */

void PrintKonfigurasiPermainan(Permainan Perm);
/* Mencetak ke layar konfigurasi permainan hasil pembacaan dari file eksternal */

void TulisPetaPermainan (Permainan Perm);
/* Prosedur yang serupa seperti TulisMATRIKS namun mengganti memberikan output */
/* berupa character sesuai integer yang ada pada konvensi sebagai berikut */
/* Elmt(Peta(Perm),i,j) = -1 maka cetak '*' */
/* Elmt(Peta(Perm),i,j = 0 maka cetak ' ' */
/* else maka TulisBANGUNAN(Elmt(Peta(Perm), i, j)) */

void TulisBangunanPlayer(List L,TabBANGUNAN tabBangunan,int *n);
/* Menuliskan daftar bangunan dari suatu player */

void TulisDaftarBangunan(Permainan Perm,int turn,int *n);
/* Menuliskan daftar bangunan dari suatu player pada suatu state permainan tertentu */

void TulisDaftarBangunanTerhubung(Permainan Perm, int Id);
/* Menuliskan daftar bangunan yang terhubung dengan bangunan tersebut sesuai ADT Graph */
#endif