/* Nama file: command.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */
/* Mengolah command (input) dari user */

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "mesinkata.h"
#include "listbangunan.h"
#include "permainan.h"

extern Kata DaftarCommand[9]; /* Berisi 8 daftar command yang bisa dilakukan. Indeks 0 tidak digunakan */

void InitDaftarCommand();
/* Mengisi array DaftarCommand */

void ShowAvailableCommand();
/* Menampilkan ke layar daftar Command yang bisa dilakukan player */

boolean IsInRange(int x,int l,int r);
/* Fungsi untuk membantu pengecekan nilai. Mengirimkan true jika x di antara l dan r */

/* **** PROSEDUR YANG DIJALANKAN KETIKA PLAYER MENGETIKKAN COMMAND DI LAYAR *** */
void CommandAttack(Permainan *perm, int turn);
/* Menjalankan mekanisme attack yang dilakukan oleh pemain turn */

void CommandLevelUp(Permainan *perm, int turn);
/* Menjalankan mekanisme level_up yang dilakukan oleh pemain turn */

void CommandSkill(Permainan *perm, int turn);
/* Menjalankan mekanisme skill yang dilakukan oleh pemain turn */

void CommandUndo(Permainan *perm);
/* Menjalankan mekanisme undo yang dilakukan oleh pemain turn */

void CommandEndTurn(Permainan *perm, int turn);
/* Menjalankan mekanisme end_turn yang dilakukan oleh pemain turn */

void CommandSave(Permainan *perm, int turn);
/* Menjalankan mekanisme save yang dilakukan oleh pemain turn */

void CommandMove(Permainan *perm, int turn);
/* Menjalankan mekanisme move yang dilakukan oleh pemain turn */

void CommandExit(Permainan *perm, int turn);
/* Menjalankan mekanisme exit yang dilakukan oleh pemain turn */

/* PROSEDUR PENUNJANG GAME LAINNYA */
void TambahPasukanDiAwalGiliran(Permainan *perm, int turn);
/* Menambhakn semua jumlah pasukan pada bangunan milik player 1 atau 2 (tergantung nnilai turn)*/

#endif