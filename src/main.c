/* Nama file: main.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "permainan/permainan.h"
#include "mesinkata/mesinkata.h"
#include "command/command.h"
#include "skill/skill.h"
#include "color/color.h"
#include <stdio.h>

int main(){
    /* Kamus */
    Permainan Perm;
    char s[NMaxStr],pil;
    int i,turn,NbBangunanAttack,NbBangunanMove,BanyakBangunan;
    boolean finish,end_turn;

    /* Algoritma */
    /* Inisiasi Game */
    TulisLogoPermainan();
    InitDaftarCommand();
    do{
        red();
        printf("ENTER INPUT: ");
        reset();
        scanf(" %c",&pil);
        if ((pil != '1') && (pil != '2')) {
            printf("Please input 1 or 2!\n");
        }
    }while((pil!='1') && (pil!='2'));
    
    if (pil=='1'){
        /* Baca konfigurasi permainan dari file config_map.txt */
        BacaKonfigurasi("config_map.txt",&Perm,false,&turn);
    }
    else{
        /* Baca konfigurasi permainan dari file game yang sudah pernah dimainkan */
        printf("Lokasi load file: ");
        scanf("%s",s);
        BacaKonfigurasi(s,&Perm,true,&turn);
    }

    /* Tampilan awal game hasil load dari file */
    PrintKonfigurasiPermainan(Perm);
    ShowAvailableCommand();

    /* Looping Command */
    finish = false;
    Perm.ExtraTurn = false;
    /* Looping satu player */
    do{

        /* Inisiasi stack diawal turn pemain*/
        CreateEmptyStack(&StackPerm(Perm));
        end_turn = false;

        /* boolean skill extra turn */
        if (Perm.ExtraTurn) Perm.ExtraTurn = false;

        /* Looping satu command */
        do{ // command != "EXIT"
            /* Mencetak informasi dan kondisi permainan */
            TulisSkorPermainan(Perm);
            if (turn == 1) {
                blue();
            } else {
                red();
            }
            printf("Player %d Turn\n",turn);
            reset();

            TulisDaftarBangunan(ListBangunanPlayer(Perm,turn),DaftarBangunan(Perm),&BanyakBangunan,&NbBangunanAttack,&NbBangunanMove,'0');
            PrintAvailableSkill(Perm,turn);
            printf("\n");

            if (turn == 1) {
                blue();
            } else {
                red();
            }
            printf("ENTER COMMAND: ");
            reset();
            
            STARTKATA("stdin",false);
            /* command == "ATTACK" */
            if (IsSamaKata(CKata,DaftarCommand[1])){ 
                if (NbBangunanAttack>0) {
                    CommandAttack(&Perm,turn);
                    if (IsEmptyList(ListBangunanPlayer(Perm,(turn%2)+1))) finish = true;
                } else {
                    printf("Tidak ada lagi bangunan yang dapat menyerang!\n");
                }
            }
            /* command == "LEVEL_UP" */
            else if (IsSamaKata(CKata,DaftarCommand[2])){ 
                CommandLevelUp(&Perm, turn);
            }
            /* command == "SKILL" */
            else if (IsSamaKata(CKata,DaftarCommand[3])){ 
                CommandSkill(&Perm, turn);
            } 
            /* command == "UNDO" */
            else if (IsSamaKata(CKata,DaftarCommand[4])){ 
                CommandUndo(&Perm);
            }
            /* command == "END_TURN" */
            else if (IsSamaKata(CKata,DaftarCommand[5])){ 
                end_turn = true;
            }
            /* command == "SAVE" */
            else if (IsSamaKata(CKata,DaftarCommand[6])){ 
                CommandSave(Perm, turn);
            }
            /* command == "MOVE" */
            else if (IsSamaKata(CKata,DaftarCommand[7])){ 
                if (NbBangunanMove>0) {
                    CommandMove(&Perm, turn);
                } else {
                    printf("Tidak ada lagi bangunan yang dapat memindahkan pasukan!\n");
                }
            }
            /* command == "EXIT" */
            else if (IsSamaKata(CKata,DaftarCommand[8])){ 
                CommandExit(Perm,turn);
                finish = true;
            }
            else{
                printf("Input salah\n");
            }
            if (!finish) printf("\n");
        } while ( !finish && !end_turn );

        if (!finish){
            printf("\n");
            /* Cek untuk mendapatkan skill IR */
            if (CanGetInstantReinforment(&Perm,turn)) {
                 Add(&SkillPlayer(Perm,turn),6);
            }
            /* Mengurangi jumlah pemakaian shield untuk lawan */ 
            if (PlayerPerm(Perm,turn%2+1).Shield>0){
                --PlayerPerm(Perm,turn%2+1).Shield;
            }
            /* /mengeset semua bangunan menjadi belum menyerang dan belum move*/ 
            InitListPlayer(ListBangunanPlayer(Perm,turn),&DaftarBangunan(Perm)); 
            /* Mengganti turn */
            if (!Perm.ExtraTurn) turn = turn%2+1;
            /* menambah pasukan, ditaruh disini biar tidak menambah pasukan ketika load game */
            TambahPasukanDiAwalGiliran(&Perm,turn);
        }
        
    }while(!finish);

    if (IsEmptyList(ListBangunanPlayer(Perm,(turn%2)+1))){
        printf("Selamat!!!\n");
        if (turn == 1) {
            blue();
        } else {
            red();
        }
        printf("Player %d",turn);
        reset();
        printf(" telah memenangkan permainan!\n");
    }
}