/* Nama file: command.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */
/* Mengolah command (input) dari user */

#include "command.h"
#include <stdio.h>

Kata DaftarCommand[9]; /* Berisi 8 daftar command yang bisa dilakukan. Indeks 0 tidak digunakan */

void InitDaftarCommand(){
/* Mengisi array DaftarCommand */
    DaftarCommand[1] = StringtoKata("ATTACK");
    DaftarCommand[2] = StringtoKata("LEVEL_UP");
    DaftarCommand[3] = StringtoKata("SKILL");
    DaftarCommand[4] = StringtoKata("UNDO");
    DaftarCommand[5] = StringtoKata("END_TURN");
    DaftarCommand[6] = StringtoKata("SAVE");
    DaftarCommand[7] = StringtoKata("MOVE");
    DaftarCommand[8] = StringtoKata("EXIT");
}

void ShowAvailableCommand() {
    printf("Daftar Command:\n");
    printf("- ATTACK\n");
    printf("- LEVEL_UP\n");
    printf("- SKILL\n");
    printf("- UNDO\n");
    printf("- END_TURN\n");
    printf("- SAVE\n");
    printf("- MOVE\n");
    printf("- EXIT\n");
}

boolean IsInRange(int x,int l,int r){
    return ((l<=x) && (x<=r));
}


void CommandAttack(Permainan *perm, int turn) {
    IdxType idPenyerang,idDiSerang;
    int idxPenyerang,idxDiSerang,BanyakBangunan, jumlahPasukanPenyerang, jumlahPasukanDiSerang;
    BANGUNAN *bangunanPenyerang, *bangunanDiSerang;

    /* Mencetak daftar bangunan player */
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(*perm,turn,&BanyakBangunan); 

    /* Input player bangunan mana yang digunakan untuk menyerang */
    /* Input pengguna bangunan mana yang ingin digunakan untuk menyerang */
    do {
        printf("Bangunan yang akan digunakan untuk menyerang: ");
        scanf("%d",&idxPenyerang);
        /* Masukan harus valid */ 
        if (!IsInRange(idxPenyerang,1,BanyakBangunan)) {
            printf("Masukkan tidak valid\n");
        }
    } while (!IsInRange(idxPenyerang,1,BanyakBangunan));

    if (turn == 1) {
        idPenyerang = GetId(ListBangunanP1(*perm),idxPenyerang);
    } else {
        idPenyerang = GetId(ListBangunanP2(*perm),idxPenyerang);
    }

    /* Mencetak daftar bangunan yang terhubung dengan bangunan player yang dipilih jika ada */
    printf("Daftar bangunan yang dapat diserang: \n");
    TulisDaftarBangunanTerhubung(*perm,idPenyerang);

    /* Meminta input bangunan diserang dan jumlah pasukan untuk menyerang */
    printf("\n");
    printf("Bangunan yang diserang: ");
    scanf("%d",&idxDiSerang);
    printf("Jumlah pasukan: ");
    scanf("%d",&jumlahPasukanPenyerang);

    idDiSerang = GetIdAdj(Graph(*perm),idPenyerang,idxDiSerang);
    if (idDiSerang == 0) {
        printf("Tidak ada bangunan yang dapat diserang\n");
    } else {
        /* MELAKUKAN SERANGAN */
        /* Satu bangunan cuman bisa nyerang sekali -> buat mark */

        /* Melakukan pembandingan jumlah pasukan bangunan penyerang dan diserang */
        // *bangunanPenyerang = Elmt(DaftarBangunan(*perm),idPenyerang); 
        // *bangunanDiSerang = Elmt(DaftarBangunan(*perm),idDiSerang);
        
        jumlahPasukanDiSerang = JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang));
        
        if (jumlahPasukanPenyerang < jumlahPasukanDiSerang) {
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenyerang)) -= jumlahPasukanPenyerang;
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang)) -= jumlahPasukanPenyerang;
        
            printf("Bangunan gagal direbut. \n");
        } else {
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenyerang)) -= jumlahPasukanPenyerang;
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang)) = jumlahPasukanPenyerang - JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang));
            
            /* Melakukan akuisisi */
            if (turn == 1) {
                Pemilik(Elmt(DaftarBangunan(*perm),idDiSerang)) = 1;
                InsVLast(&ListBangunanP1(*perm),idDiSerang);
            } else {
                Pemilik(Elmt(DaftarBangunan(*perm),idDiSerang)) = 2;
                InsVLast(&ListBangunanP2(*perm),idDiSerang);
            }

            printf("Bangunan menjadi milikmu! \n");
        }

        /* Cek pertahanan, Pertahanan(B) */
        /* Cek skill AttackUp dan CriticalHit */
}

/* IMPLEMENTASI PROSEDUR-PROSEDUR COMMAND */
void CommandLevelUp(Permainan *perm,int turn) {  
    IdxType idx;
    int IdBangunan,BanyakBangunan;

    /* Mencetak daftar bangunan player*/ 
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(*perm,turn,&BanyakBangunan);
    
    /* Input pengguna bangunan mana yang ingin di level up */
    do {
        printf("Bangunan yang akan di level up: ");
        scanf("%d",&idx);
        /* Masukan harus valid */ 
        if (!IsInRange(idx,1,BanyakBangunan)) {
            printf("Masukkan tidak valid\n");
        }
    } while (!IsInRange(idx,1,BanyakBangunan));

    /* Mendapatkan IdBangunan mana yang akan di level up */
    if (turn == 1) {
        IdBangunan = GetId(ListBangunanP1(*perm),idx);
    } else {
        IdBangunan = GetId(ListBangunanP2(*perm),idx);
    }

    /* Menambah level, evaluasi kevalidan penambahan pasukan ada di dalam prosedur  */
    TambahSatuLevel(&Elmt(DaftarBangunan(*perm),IdBangunan));
}
