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


/* IMPLEMENTASI PROSEDUR-PROSEDUR COMMAND */
void CommandAttack(Permainan *perm, int turn) {
    IdxType idPenyerang,idDiSerang;
    int idxPenyerang,idxDiSerang,BanyakBangunanPenyerang,BanyakBangunanDiSerang, jumlahPasukanPenyerang, jumlahPasukanDiSerang;
    BANGUNAN *bangunanPenyerang, *bangunanDiSerang;

    /* Mencetak daftar bangunan player */
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(*perm,turn,&BanyakBangunanPenyerang); 

    /* Input player bangunan mana yang digunakan untuk menyerang */
    /* Input pengguna bangunan mana yang ingin digunakan untuk menyerang */
    do {
        printf("Bangunan yang akan digunakan untuk menyerang: ");
        scanf("%d",&idxPenyerang);
        /* Masukan harus valid */ 
        if (!IsInRange(idxPenyerang,1,BanyakBangunanPenyerang)) {
            printf("Masukkan tidak valid\n");
        }
    } while (!IsInRange(idxPenyerang,1,BanyakBangunanPenyerang));

    if (turn == 1) {
        idPenyerang = GetId(ListBangunanP1(*perm),idxPenyerang);
    } else {
        idPenyerang = GetId(ListBangunanP2(*perm),idxPenyerang);
    }

    /* Mencetak daftar bangunan yang terhubung dengan bangunan player yang dipilih jika ada */
    printf("Daftar bangunan yang dapat diserang: \n");
    TulisDaftarBangunanMusuhTerhubung(*perm,idPenyerang,&BanyakBangunanDiSerang,turn);
    printf("\n");
    
    /* Meminta input bangunan diserang dan jumlah pasukan untuk menyerang */
    do {
        printf("Bangunan yang diserang: ");
        scanf("%d",&idxDiSerang);
        if (!IsInRange(idxDiSerang,1,BanyakBangunanDiSerang)) {
            printf("Masukkan tidak valid\n");
        }
    } while (!IsInRange(idxDiSerang,1,BanyakBangunanDiSerang));
    idDiSerang = GetIdAdj(Graph(*perm),idPenyerang,idxDiSerang);
    
    printf("Jumlah pasukan: ");
    scanf("%d",&jumlahPasukanPenyerang);

    if (idDiSerang == 0) {
        printf("Tidak ada bangunan yang dapat diserang\n");
    } else {
        /* MELAKUKAN SERANGAN */
        /* Satu bangunan cuman bisa nyerang sekali -> buat mark */

        /* Melakukan pembandingan jumlah pasukan bangunan penyerang dan diserang */
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
}
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

/* PROSEDUR PENUNJANG GAME LAINNYA */
void TambahPasukanDiAwalGiliran(Permainan *perm, int turn) {
    int i, A, Id;
    address P;
    
    if (turn == 1) {
        P = First(ListBangunanP1(*perm));
        i = 1;
        while (P != Nil) {
            Id = GetId(ListBangunanP1(*perm),i);
            A = GetNilaiPenambahanPasukan(Elmt(DaftarBangunan(*perm),Id));
            TambahJumlahPasukan(&Elmt(DaftarBangunan(*perm),Id),A);
            
            i++;
            P = Next(P);
        }
    } else {
        P = First(ListBangunanP2(*perm));
        i = 1;
        while (P != Nil) {
            Id = GetId(ListBangunanP2(*perm),i);
            A = GetNilaiPenambahanPasukan(Elmt(DaftarBangunan(*perm),Id));
            TambahJumlahPasukan(&Elmt(DaftarBangunan(*perm),Id),A);
            
            i++;
            P = Next(P);
        }            
    }
}