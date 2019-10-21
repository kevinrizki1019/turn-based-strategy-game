/* Nama file: bangunan.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef __BANGUNAN_H__
#define __BANGUNAN_H__

#include "boolean.h"
#include "point.h"

#define MAX_PASUKAN 1000000

typedef struct {
    char JenisBangunan;  // [C, T, F, V]
    POINT Posisi;
    int JumlahPasukan;
    int Level;
} BANGUNAN;
/* CATATAN:
Setelah dipikir-pikir ada beberapa attribut yg bisa didrop disini
1. ID, digantiin dengan indeks bangunan pada tab bangunan
2. Pemilik, digantiin dengan list linier
3. A, M, P, dan U, didapet dari kombinasi JenisBangunan dan level
*/

/* ********** SELEKTOR ********** */
#define JenisBangunan(B) (B).JenisBangunan
#define Posisi(B) (B).Posisi
#define JumlahPasukan(B) (B).JumlahPasukan
#define Level(B) (B).Level

int GetNilaiPenambahanPasukan (BANGUNAN B);
// Mengembalikan nilai A bergantung pada JenisBangunan(B) dan Level(B)
int GetMaksimumPenambahanPasukan (BANGUNAN B);
// Mengembalikan nilai M bergantung pada JenisBangunan(B) dan Level(B)
boolean GetPertahanan (BANGUNAN B);
// Mengembalikan nilai P bergantung pada JenisBangunan(B) dan Level(B)
int GetPasukanAwal (BANGUNAN B);
// Mengembalikan nilai U bergantung pada JenisBangunan(B) dan Level(B)

/* ********** VALIDATOR ********** */
boolean IsJenisBangunanValid (char CC);
// JenisBangunan valid: CC == [C, T, F, V]
boolean IsPosisiValid (POINT posisi);
// Posisi valid: absis(posisi) <= lebar(peta) && ordinat(posisi) <= tinggi(peta)
boolean IsJumlahPasukanValid (int jml_pasukan);
// JumlahPasukan valid: jml_pasukan <= MAX_PASUKAN
boolean IsLevelValid (int lvl);
// Level valid: 1 <= lvl <= 4

/* ********** KONSTRUKTOR ********** */
BANGUNAN MakeBANGUNAN (char tipe_bangunan, POINT posisi, int jml_pasukan);
// Prekondisi: semua parameter adalah valid untuk tipe BANGUNAN
// Proses Membuat sebuah BANGUNAN dengan atribut sesuai parameter
// untuk atribut Level dimulai dengan nilai 1

#endif