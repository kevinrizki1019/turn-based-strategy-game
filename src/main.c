/* Nama file: main.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "permainan/permainan.h"
#include "mesinkata/mesinkata.h"
#include "command/command.h"
#include "skill/skill.h"
#include "color/color.h"
#include <stdio.h>

int main(){
    /* Silakan mencoba codingan di bawah ini */
    /* Jangan mengahapus codingan dibawah karena untuk main program */
    /* Kamus */
    Permainan Perm;
    char s[NMaxStr],pil;
    int i,turn,NbBangunanAttack,NbBangunanMove,BanyakBangunan;
    boolean finish,end_turn;

    /* Algoritma */
    TulisLogoPermainan();
    
    /* Inisiasi Game */
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
        BacaKonfigurasi("config_map.txt",&Perm,false,&turn);
    }
    else{
        printf("Lokasi load file: ");
        scanf("%s",s);
        BacaKonfigurasi(s,&Perm,true,&turn);
    }

    /* Tampilan awal game hasil load dari file */
    printf("\n~~~~~~~~~~~~~~~");
    PrintKonfigurasiPermainan(Perm);
    ShowAvailableCommand();
    printf("~~~~~~~~~~~~~~~\n\n");


    /* Looping Command */
    finish = false;
    Perm.ExtraTurn = false;
    do{
        TambahPasukanDiAwalGiliran(&Perm,turn);

        CreateEmptyStack(&StackPerm(Perm));
        end_turn = false;
        InitListPlayer(ListBangunanPlayer(Perm,turn),&DaftarBangunan(Perm));

        
        /* boolean skill */
        if (Perm.ExtraTurn) Perm.ExtraTurn = false;
        do{ // command != "EXIT"
            TulisPetaPermainan(Perm);
            blue();
            printf("       Player %d ",1);
            reset();
            printf("%d |",NbElmtList(ListBangunanPlayer(Perm,1)));
            
            printf(" %d ",NbElmtList(ListBangunanPlayer(Perm,2)));
            red();
            printf("Player %d\n",2);
            reset();

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
            if (IsSamaKata(CKata,DaftarCommand[1])){ // command == "ATTACK"
                if (NbBangunanAttack>0) {
                    CommandAttack(&Perm,turn);
                    if (IsEmptyList(ListBangunanPlayer(Perm,(turn%2)+1))) finish = true;
                } else {
                    printf("Tidak ada lagi bangunan yang dapat menyerang!\n");
                }
            }
            else if (IsSamaKata(CKata,DaftarCommand[2])){ // command == "LEVEL_UP"
                CommandLevelUp(&Perm, turn);
            }
            else if (IsSamaKata(CKata,DaftarCommand[3])){ // command == "SKILL"
                CommandSkill(&Perm, turn);
                CreateEmptyStack(&StackPerm(Perm));
            } 
            else if (IsSamaKata(CKata,DaftarCommand[4])){ // command == "UNDO"
                CommandUndo(&Perm);
            }
            else if (IsSamaKata(CKata,DaftarCommand[5])){ // command == "END_TURN"
                end_turn = true;
            }
            else if (IsSamaKata(CKata,DaftarCommand[6])){ // command == "SAVE"
                CommandSave(Perm, turn);
            }
            else if (IsSamaKata(CKata,DaftarCommand[7])){ // command == "MOVE"
                if (NbBangunanMove>0) {
                    CommandMove(&Perm, turn);
                } else {
                    printf("Tidak ada lagi bangunan yang dapat memindahkan pasukan!\n");
                }
            }
            else if (IsSamaKata(CKata,DaftarCommand[8])){ // command == "EXIT"
                CommandExit(Perm,turn);
                finish = true;
            }
            else{
                printf("Input salah\n");
            }
            if (!finish) printf("\n");
        } while ( !finish && !end_turn );
        if (CanGetInstantReinforment(&Perm,turn)) {
             Add(&SkillPlayer(Perm,turn),6);
        }

        if (!finish){
            printf("\n");
            if (!Perm.ExtraTurn) turn = turn%2+1;
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