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
    int Pemilik;  // tanda pemilik bangunan. 0(tidak ada yang punya), 1/2 (milik player)
    boolean P,attacked,moved; // Nilai atribut P yaitu Pertahanan
} BANGUNAN;
/* CATATAN:
Setelah dipikir-pikir ada beberapa attribut yg bisa didrop disini
1. ID, digantiin dengan indeks bangunan pada tab bangunan
2. A, M, dan U, didapet dari kombinasi JenisBangunan dan level
3. Khusus untuk P karena ada skill shield up mesti dibuat atribut status pertahanan yes/no
*/

/* ********** SELEKTOR ********** */
#define JenisBangunan(B)    (B).JenisBangunan
#define Posisi(B)           (B).Posisi
#define JumlahPasukan(B)    (B).JumlahPasukan
#define Level(B)            (B).Level
#define Pemilik(B)          (B).Pemilik
#define Pertahanan(B)       (B).P
#define SudahAttack(B)      (B).attacked
#define SudahMove(B)        (B).moved

/* ********** SELEKTOR Tambahan ********** */
void StringJenisBangunan(BANGUNAN B);
/* Mengembalikan string jenis bangunan dari B, JenisBangunan(B) == 'C' -> Castle dst */

int GetNilaiPenambahanPasukan (BANGUNAN B);
// Mengembalikan nilai A bergantung pada JenisBangunan(B) dan Level(B)
int GetMaksimumPenambahanPasukan (BANGUNAN B);
// Mengembalikan nilai M bergantung pada JenisBangunan(B) dan Level(B)
int GetPasukanAwal (BANGUNAN B);
// Mengembalikan nilai U bergantung pada JenisBangunan(B) dan Level(B)

/* ********** VALIDATOR ********** */
boolean IsJenisBangunanValid (char CC);
// JenisBangunan valid: CC == [C, T, F, V]
boolean IsPosisiValidByMap (POINT posisi, int tinggi, int lebar);
// Posisi valid: absis(posisi) <= lebar(peta) && ordinat(posisi) <= tinggi(peta)
boolean IsJumlahPasukanValid (int jml_pasukan);
// JumlahPasukan valid: jml_pasukan <= MAX_PASUKAN
boolean IsLevelValid (int lvl);
// Level valid: 1 <= lvl <= 4

/* ********** KONSTRUKTOR ********** */
BANGUNAN MakeBANGUNAN (char jenis_bangunan, POINT posisi,int pemilik);
// Prekondisi: semua parameter adalah valid untuk tipe BANGUNAN
// Proses Membuat sebuah BANGUNAN dengan atribut sesuai parameter
// untuk atribut Level dimulai dengan nilai 1

/* ********** SETTER ********** */
void SetPertahanan (BANGUNAN *B);
// Mengubah nilai status pertahanan sesuai levelnya

/* ********** OPERASI BACA/TULIS ********** */
void TulisBangunan (BANGUNAN B);
// Menulis keterangan sebuah bangunan dengan format:
// <JenisBangunan(B)> <Posisi(B)> <JumlahPasukan(B)> <Level(B)>
// Tanpa spasi atau enter di awal dan di akhir

void BacaBangunan (BANGUNAN *B);
// Membaca data bangunan dari file eksternal dengan bantuan mesin keterangan
// Lalu menyimpannya dalam *B

/* ********** OPERASI LAINNYA ********** */
void TambahSatuLevel (BANGUNAN *B, boolean *success, BANGUNAN *B_lama);
// Menambah level bangunan sebesar 1 
// selama nilai setelah penambahan masih valid

void TambahJumlahPasukan (BANGUNAN *B, int jumlah_penambahan);
// Menambahkan nilai JumlahPasukan(*B) sebesar jumlah_penambahan
// tidak dilakukan penambahan jika JumlahPasukan(*B) >= M

void KurangJumlahPasukan (BANGUNAN *B, int jumlah_pengurangan);
// Menambahkan nilai JumlahPasukan(*B) sebesar jumlah_pengurangan
// tidak dilakukan pengurangan jika JumlahPasukan(*B) - jumlah_pengurangan < 0

boolean IsBangunanSama(BANGUNAN A, BANGUNAN B);
// Mengembalikan nilai true jika bangunan A dan B sama, false jika tidak


#endif