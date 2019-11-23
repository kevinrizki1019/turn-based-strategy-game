/* Nama file: skill.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "skill.h"

/* *********** OUTPUT *********** */
void PrintSkill(int idx){
/* Mencetak skill dengan urutan ke i */
    switch(idx){
        case 1: // Instant Upgrade
        printf("IU");
        break;

        case 2: // Shield
        printf("SH");
        break;

        case 3: // Extra Turn
        printf("ET");
        break;

        case 4: // Attack Up
        printf("AU");
        break;

        case 5: // Critical Hit
        printf("CH");
        break;

        case 6: // Instant Reinforcement
        printf("IR");
        break;

        case 7: // Barrage
        printf("BR\n");
        break;
    }
}

void PrintAvailableSkill(Permainan Perm,int player){
    printf("Skill Available: ");
    if (!IsQueueEmpty(SkillPlayer(Perm,player))){
        PrintSkill(InfoHead(SkillPlayer(Perm,player)));
    }
    else{
        printf("-");
    }
    printf("\n");
}

/* *********** Checker *********** */

int CanGetInstantReinforment(Permainan *Perm, int player){
    address P = First(ListBangunanPlayer(*Perm,player));
    while (P != Nil){
        if (Level(Elmt(DaftarBangunan(*Perm),Info(P))) < 4)
            return 0;
        P = Next(P);
    }
    return 1;
}


/* *********** Implementasi Skill *********** */
void InstantUpgrade(Permainan *Perm,int player)
/* Melakukan upgrade bangunan yang dimiliki oleh suatu player.
    Jika player = 1, upgrade bangunan player 1.
    Jika player = 2, upgrade bangunan player 2. */
{	
	BANGUNAN B;
    address P = First(ListBangunanPlayer(*Perm,player));
    while (P != Nil){
        B = Elmt(DaftarBangunan(*Perm),Info(P));
        if(IsLevelValid(Level(B)+1)){
            Level(B)++;
            Elmt(DaftarBangunan(*Perm),Info(P)) = B;
		}
        P = Next(P);
    }
}

void InstantReinforcement(Permainan *Perm, int player)
/* Melakukan penambahan 5 pasukan pada bangunan yang dimiliki oleh suatu player.
    Jika player = 1, berarti lakukan pada bangunan player 1.
    Jika player = 2, berarti lakukan pada bangunan player 2. */
{
    BANGUNAN B;
    address P = First(ListBangunanPlayer(*Perm, player));
    while (P != Nil){
        B = Elmt(DaftarBangunan(*Perm),Info(P));
        JumlahPasukan(B) += 5;
        Elmt(DaftarBangunan(*Perm),Info(P)) = B;
        P = Next(P);
    }
}

void Barrage(Permainan *Perm,int player)
/* Mengurangi jumlah pasukan sebanyak 10 pada bangunan musuh */
{
    BANGUNAN B;
    address P = First(ListBangunanPlayer(*Perm, (player%2)+1)); // milik musuh
    while (P != Nil){
        B = Elmt(DaftarBangunan(*Perm),Info(P));
        JumlahPasukan(B) -= 5;
        if (JumlahPasukan(B)<10){
            JumlahPasukan(B) = 0;
        }
        Elmt(DaftarBangunan(*Perm),Info(P)) = B;
        P = Next(P);
    }
}
