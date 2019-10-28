/* Nama file: command.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */
/* Mengolah command (input) dari user */

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "mesinkata.h"

extern Kata DaftarCommand[9]; /* Berisi 8 daftar command yang bisa dilakukan. Indeks 0 tidak digunakan */

void InitDaftarCommand();
/* Mengisi array DaftarCommand */

#endif