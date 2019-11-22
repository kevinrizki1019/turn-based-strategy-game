#include "permainan.h"
#include "mesinkata.h"
#include "command.h"
#include "skill.h"
#include <stdio.h>


int main(){
    /* Silakan mencoba codingan di bawah ini */
    /* Jangan mengahapus codingan dibawah karena untuk main program */
    /* Kamus */
    Permainan Perm;
    char s[NMaxStr],pil;
    int i,turn,NbBangunanAttackOff,NbBangunanMoveOff,BanyakBangunan;
    boolean finish,end_turn;
    List ListBangunanPlayerAvailableToAttack, ListBangunanPlayerAvailableToMove;

    /* Algoritma */
    TulisLogoPermainan();
    
    /* Inisiasi Game */
    InitDaftarCommand();
    do{
        printf("ENTER INPUT: ");
        scanf(" %c",&pil);
        if ((pil != '1') && (pil != '2')) {
            printf("Please input 1 or 2!\n");
        }
    }while((pil!='1') && (pil!='2'));
    
    if (pil=='1'){
        BacaKonfigurasi("config_map.txt",&Perm,false);
    }
    else{
        printf("Lokasi load file: ");
        scanf("%s",s);
        BacaKonfigurasi(s,&Perm,true);
    }

    /* Tampilan awal game hasil load dari file */
    printf("\n~~~~~~~~~~~~~~~");
    PrintKonfigurasiPermainan(Perm);
    ShowAvailableCommand();
    printf("~~~~~~~~~~~~~~~\n\n");


    /* Looping Command */
    turn = 1;
    finish = false;
    Perm.ExtraTurn = false;
    do{
        TambahPasukanDiAwalGiliran(&Perm,turn);

        CreateEmptyStack(&StackPerm(Perm));
        end_turn = false;

        CreateEmpty(&ListBangunanPlayerAvailableToAttack);
        CreateEmpty(&ListBangunanPlayerAvailableToMove);
        CopyList(ListBangunanPlayer(Perm,turn),&ListBangunanPlayerAvailableToAttack);
        CopyList(ListBangunanPlayer(Perm,turn),&ListBangunanPlayerAvailableToMove);
        NbBangunanAttackOff = 0;
        NbBangunanMoveOff = 0;
        
        /* boolean skill */
        if (Perm.ExtraTurn) Perm.ExtraTurn = false;
        do{ // command != "EXIT"
            TulisPetaPermainan(Perm);
            printf("Player %d\n",turn);
            TulisDaftarBangunan(ListBangunanPlayer(Perm,turn),DaftarBangunan(Perm),&BanyakBangunan);
            PrintAvailableSkill(Perm,turn);
            printf("\n");
            printf("ENTER COMMAND: ");
            STARTKATA("stdin",false);
            if (IsSamaKata(CKata,DaftarCommand[1])){ // command == "ATTACK"
                if (!IsEmptyList(ListBangunanPlayerAvailableToAttack)) {
                    CommandAttack(&Perm,turn,&ListBangunanPlayerAvailableToAttack,&ListBangunanPlayerAvailableToMove,&NbBangunanAttackOff);
                } else {
                    printf("Tidak ada lagi bangunan yang dapat menyerang!\n");
                }
            }
            else if (IsSamaKata(CKata,DaftarCommand[2])){ // command == "LEVEL_UP"
                CommandLevelUp(&Perm, turn);
            }
            else if (IsSamaKata(CKata,DaftarCommand[3])){ // command == "SKILL"
                CommandSkill(&Perm, turn);
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
                if (!IsEmptyList(ListBangunanPlayerAvailableToMove)) {
                    CommandMove(&Perm, turn, &ListBangunanPlayerAvailableToMove,&NbBangunanMoveOff);
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
        
        if (!finish){
            printf("\n");
            if (!Perm.ExtraTurn) turn = turn%2+1;
        }
        
    }while(!finish);
}