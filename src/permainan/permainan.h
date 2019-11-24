/* Nama file: permainan.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef __PERMAINAN_H__
#define __PERMAINAN_H__

#include "../mesinkata/mesinkata.h"
#include "../tabbangunan/tabbangunan.h"
#include "../matriks/matriks.h"
#include "../listbangunan/listbangunan.h"
#include "../graph/graph.h"
#include "../queueofskill/queueofskill.h"
#include "../stackt/stackt.h"
#include "../color/color.h"
#include "../boolean.h"
#include <stdio.h>

typedef struct{
    List ListBangunan;
    Queue QueueSkill;
    int Shield;
} Player;

typedef struct{
    TabBANGUNAN DaftarBangunan; // Menyimpan daftar bangunan
    MATRIKS Peta;
    Player Player[3];
    Stack StackPermainan;
    GraphBANGUNAN G;
    boolean ExtraTurn, AttackUp, CriticalHit;
} Permainan;

/* ********** SELEKTOR ********** */
#define TinggiPeta(P) (P).Peta.NBrsEff
#define LebarPeta(P) (P).Peta.NKolEff
#define JumlahBangunan(P) (P).DaftarBangunan.Neff
#define DaftarBangunan(P) (P).DaftarBangunan
#define Peta(P) (P).Peta
#define PlayerPerm(P,idPlayer) (P).Player[idPlayer]
#define ListBangunanPlayer(P,idPlayer) (P).Player[idPlayer].ListBangunan
#define SkillPlayer(P,idPlayer) (P).Player[idPlayer].QueueSkill
#define StackPerm(P) (P).StackPermainan
#define Graph(P) (P).G

void BacaKonfigurasi(char NamaFile[], Permainan *Perm, boolean load, int *turn);
/*  Membaca konfigurasi file dari 'NamaFile'
    I.S. = 'NamaFile' terdefinisi dan ada
    F.S. = Variabel Perm terinisialisasi */

void SimpanKonfigurasi(char NamaFile[], Permainan Perm, int turn);
/* Menyimpan konfigurasi permainan di file */


void PrintKonfigurasiPermainan(Permainan Perm);
/* Mencetak ke layar konfigurasi permainan hasil pembacaan dari file eksternal */

void TulisLogoPermainan();

void TulisPetaPermainan (Permainan Perm);
/* Prosedur yang serupa seperti TulisMATRIKS namun mengganti memberikan output */
/* berupa character sesuai integer yang ada pada konvensi sebagai berikut */
/* Elmt(Peta(Perm),i,j) = -1 maka cetak '*' */
/* Elmt(Peta(Perm),i,j = 0 maka cetak ' ' */
/* else maka TulisBANGUNAN(Elmt(Peta(Perm), i, j)) */

void TulisSkorPermainan (Permainan Perm);

void InitListPlayer(List L,TabBANGUNAN *tabel);
/* mengeset boolean bangunan player menjadi false */

void TulisDaftarBangunan(List ListPlayer,TabBANGUNAN tabBangunan,int *n,int *n_atck,int *n_move,char tipe);
/* Menuliskan daftar bangunan dari suatu player */

void TulisDaftarBangunanMusuhTerhubung(Permainan Perm, int Id, int *n, int turn);
/* Menuliskan daftar bangunan yang terhubung dengan bangunan tersebut sesuai ADT Graph */
/* dengan aturan bangunan milik pemain tidak termasuk tertulis*/

void TulisDaftarBangunanPlayerTerhubung(Permainan Perm, int Id, int *n, int turn);



#endif