/* Nama file: command.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */
/* Mengolah command (input) dari user */

#include "command.h"

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