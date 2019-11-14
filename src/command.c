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

/* IMPLEMENTASI PROSEDUR-PROSEDUR COMMAND */
void CommandLevelUp(Permainan *perm,int turn) {  
    IdxType idx;
    int IdBangunan;

    /* Mencetak daftar bangunan player*/ 
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(*perm,turn);
    
    /* Input pengguna bangunan mana yang ingin di level up */
    do {
        printf("Bangunan yang akan di level up: ");
        scanf("%d",&idx);
        /* Masukan harus valid */ 
        if ((idx<= 0) || idx > JumlahBangunanPlayer(*perm,turn)) {
            printf("Masukkan tidak valid\n");
        }
    } while (idx <= 0 || idx > JumlahBangunanPlayer(*perm,turn));

    /* Mendapatkan IdBangunan mana yang akan di level up */
    if (turn == 1) {
        IdBangunan = GetId(ListBangunanP1(*perm),idx);
    } else {
        IdBangunan = GetId(ListBangunanP2(*perm),idx);
    }

    /* Menambah level, evaluasi kevalidan penambahan pasukan ada di dalam prosedur  */
    TambahSatuLevel(&Elmt(DaftarBangunan(*perm),IdBangunan));
}

