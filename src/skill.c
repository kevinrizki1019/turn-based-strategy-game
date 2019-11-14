/* Nama file: skill.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "skill.h"
#include "stdio.h"

/* *********** OUTPUT *********** */
void PrintSkill(int idx){
/* Mencetak skill dengan urutan ke i */
    switch(idx){
        case 1: // Instant Upgrade
        printf("IU\n");
        break;

        case 2: // Shield
        printf("SH\n");
        break;

        case 3: // Extra Turn
        printf("ET\n");
        break;

        case 4: // Attack Up
        printf("AU\n");
        break;

        case 5: // Critical Hit
        printf("CH\n");
        break;

        case 6: // Instant Reinforcement
        printf("IR\n");
        break;

        case 7: // Barrage
        printf("BR\n");
        break;
    }
}

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
/* Mengurangi jumlah pasukan sebanyak 10 pada bangunan player */