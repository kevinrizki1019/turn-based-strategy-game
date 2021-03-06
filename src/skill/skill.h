/* Nama file: skill.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef __SKILL_H__
#define __SKILL_H__

#include "../permainan/permainan.h"
#include "../bangunan/bangunan.h"
#include <stdio.h>

/* *********** OUTPUT *********** */
void PrintSkill(int idx);
/* Mencetak skill dengan urutan ke i */

void PrintAvailableSkill(Permainan Perm,int player);
/* Mencetak skill terdepan player */

/* *********** Checker *********** */

boolean CanGetInstantReinforment(Permainan *Perm, int player);
/* Mengecek apakah player berhak mendapatkan skill instant reinforment untuk ditambah ke queue di akhir turn
    Jika player = 1, berarti lakukan pada bangunan player 1.
    Jika player = 2, berarti lakukan pada bangunan player 2. */
boolean CanGetAttackUp(Permainan *Perm, int player, int idDiSerang);
/* Mengecek apakah player berhak mendapatkan skill attack up untuk ditambah ke queue player */

/* *********** Implementasi Skill *********** */
void InstantUpgrade(Permainan *Perm,int player);
/* Melakukan upgrade bangunan yang dimiliki oleh suatu player.
    Jika player = 1, upgrade bangunan player 1.
    Jika player = 2, upgrade bangunan player 2. */

void InstantReinforcement(Permainan *Perm,int player);
/* Melakukan penambahan 5 pasukan pada bangunan yang dimiliki oleh suatu player.
    Jika player = 1, berarti lakukan pada bangunan player 1.
    Jika player = 2, berarti lakukan pada bangunan player 2. */

void Barrage(Permainan *Perm,int player);
/* Mengurangi jumlah pasukan sebanyak 10 pada bangunan musuh */

/* Skill yang lain diaplikasikan di program saja seperti dengan menggunakan boolean
    untuk mengetahui apakah player menggunakan skill tersebut */


#endif
