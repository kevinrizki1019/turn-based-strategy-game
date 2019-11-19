/* Nama file: bangunan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "bangunan.h"
#include <stdio.h>

/* ********** SELEKTOR ********** */
void StringJenisBangunan(BANGUNAN B) {
    if (JenisBangunan(B) == 'C') {
        printf("Castle");
    } else if (JenisBangunan(B) == 'T') {
        printf("Tower");
    } else if (JenisBangunan(B) == 'F') {
        printf("Fortress");
    } else if (JenisBangunan(B) == 'V') {
        printf("Village");
    }
}

int GetNilaiPenambahanPasukan (BANGUNAN B)
// Mengembalikan nilai A bergantung pada JenisBangunan(B) dan Level(B)
{
    if (JenisBangunan(B) == 'C') {
        return ((Level(B) * 5) + 5);
    } else if (JenisBangunan(B) == 'T') {
        if (Level(B) == 1) {
            return 5;
        } else if (Level(B) == 2) {
            return 10;
        } else if (Level(B) == 3) {
            return 20;
        } else if (Level(B) == 4) {
            return 30;
        }        
    } else if (JenisBangunan(B) == 'F') {
        return (Level(B) * 10);
    } else if (JenisBangunan(B) == 'V') {
        return (Level(B) * 5);
    }
}
int GetMaksimumPenambahanPasukan (BANGUNAN B)
// Mengembalikan nilai M bergantung pada JenisBangunan(B) dan Level(B)
{
    if (JenisBangunan(B) == 'C') {
        return ((Level(B) * 20) + 20);
    } else if (JenisBangunan(B) == 'T') {
        return ((Level(B) * 10) + 10);
    } else if (JenisBangunan(B) == 'F') {
        return (Level(B) * 20);
    } else if (JenisBangunan(B) == 'V') {
        return ((Level(B) * 10) + 10);
    }
}
int GetPasukanAwal (BANGUNAN B) 
// Prekondisi: JenisBangunan(B) harus sudah terdefinisi
// Mengembalikan nilai U bergantung pada JenisBangunan(B) dan Level(B)
{
    if (JenisBangunan(B) == 'C') {
        return 40;
    } else if (JenisBangunan(B) == 'T') {
        return 30;
    } else if (JenisBangunan(B) == 'F') {
        return 80;
    } else if (JenisBangunan(B) == 'V') {
        return 20;
    }
}

/* ********** VALIDATOR ********** */
boolean IsJenisBangunanValid (char CC)
// JenisBangunan valid: CC == [C, T, F, V]
{
    return (CC == 'C' || CC == 'T' || CC == 'F' || CC == 'V');
}
boolean IsPosisiValidByMap (POINT posisi, int tinggi, int lebar)
// Posisi valid: absis(posisi) <= lebar(peta) && ordinat(posisi) <= tinggi(peta)
{
    return ((Absis(posisi) <= lebar) && (Ordinat(posisi) <= tinggi));
}
boolean IsJumlahPasukanValid (int jml_pasukan)
// JumlahPasukan valid: jml_pasukan <= MAX_PASUKAN
{
    return (jml_pasukan <= MAX_PASUKAN);
}
boolean IsLevelValid (int lvl)
// Level valid: 1 <= lvl <= 4
{
    return ((1 <= lvl) && (lvl <= 4));
}

/* ********** KONSTRUKTOR ********** */
BANGUNAN MakeBANGUNAN (char jenis_bangunan, POINT posisi,int pemilik)
{
    BANGUNAN B;
    JenisBangunan(B) = jenis_bangunan;
    Posisi(B) = MakePOINT (Absis(posisi), Ordinat(posisi));
    JumlahPasukan(B) = GetPasukanAwal(B);
    Level(B) = 1;
    Pemilik(B) = pemilik;
    SetPertahanan(&B);
    return B;
}

/* ********** SETTER ********** */
void SetPertahanan (BANGUNAN *B)
// Prekondisi: JenisBangunan(*B) harus suah terdefinisi
// Mengubah nilai status pertahanan sesuai levelnya
{
    if (JenisBangunan(*B) == 'C') {
        Pertahanan(*B) = false;
    } else if (JenisBangunan(*B) == 'T') {
        Pertahanan(*B) =  true;
    } else if (JenisBangunan(*B) == 'F') {
        Pertahanan(*B) = (Level(*B) >= 3);
    } else if (JenisBangunan(*B) == 'V') {
        Pertahanan(*B) = false;
    }
}

/* ********** OPERASI LAINNYA ********** */
boolean IsLevelBangunanBisaDitambah (BANGUNAN *B) {

}

void TambahSatuLevel (BANGUNAN *B, boolean *success, BANGUNAN *B_lama) 
{
    int M;

    /* Nilai M untuk mengecek apakah jumlah pasukan cukup untuk dilevel up*/
    M = GetMaksimumPenambahanPasukan (*B);

    if (JumlahPasukan(*B) >= (M / 2)) {
        
        /* Mengecek apakah level bangunan sudah max atau belum */
        if (IsLevelValid(Level(*B) + 1)) {

            (*B_lama) = (*B); (*success) = true;
            Level(*B)++;
            printf("Level ");
            StringJenisBangunan(*B);
            printf("-mu bertambah menjadi %d!\n", Level(*B));
            JumlahPasukan(*B) -= M / 2;

        } else {

            (*success) = false;
            printf("Level\n");
            StringJenisBangunan(*B);
            printf("sudah max tidak bisa di level up!\n");

        }
        
    } else {

        (*success) = false;
        printf("Jumlah pasukan ");
        StringJenisBangunan(*B);
        printf(" kurang untuk level up!\n");
    }
}

void TambahJumlahPasukan (BANGUNAN *B, int jumlah_penambahan)
{
    if (JumlahPasukan(*B) < GetMaksimumPenambahanPasukan(*B)) {
        JumlahPasukan(*B) += jumlah_penambahan;
    }   
}

void KurangJumlahPasukan (BANGUNAN *B, int jumlah_pengurangan)
{
    if (JumlahPasukan(*B) - jumlah_pengurangan >= 0) {
        JumlahPasukan(*B) -= jumlah_pengurangan;
    }
}

void TulisBangunan (BANGUNAN B)
{
    if (JenisBangunan(B) == 'C') {
        printf("Castle ");
    } else if (JenisBangunan(B) == 'T') {
        printf("Tower ");
    } else if (JenisBangunan(B) == 'F') {
        printf("Fort ");
    } else if (JenisBangunan(B) == 'V') {
        printf("Village ");
    }
    TulisPOINT(Posisi(B));
    printf(" %d lv. %d", JumlahPasukan(B), Level(B));
}

boolean IsBangunanSama(BANGUNAN A, BANGUNAN B){
    if ((A.JenisBangunan == B.JenisBangunan) &&
        (A.Posisi.X == B.Posisi.X) && 
        (A.Posisi.Y == B.Posisi.Y) &&
        (A.Level == B.Level) &&
        (A.JumlahPasukan == B.JumlahPasukan) &&
        (A.P == B.P)){
            return true;
        }
    return false;   
}

