#include "permainan.h"
#include "mesinkata.h"
#include "command.h"
#include <stdio.h>

#define NMaxStr 255

int main(){
    /* Silakan mencoba codingan di bawah ini */
    /* Jangan mengahapus codingan dibawah karena untuk main program */
    /* Kamus */
    Permainan Perm;
    char s[NMaxStr],pil;
    Kata command;
    int i,turn,BanyakBangunan;
    boolean finish,ExtraTurn;

    /* Algoritma */
    /* Inisiasi Game */
    InitDaftarCommand();
    do{
        printf("Opsi:\n");
        printf("1. Baca konfigurasi\n");
        printf("2. Load game\n");
        printf("Masukkan pilihan: ");
        scanf(" %c",&pil);
    }while((pil!='1') && (pil!='2'));
    
    if (pil=='1'){
        BacaKonfigurasi("config_map.txt",&Perm);
    }

    /* Tampilan awal game hasil load dari file */
    printf("\n~~~~~~~~~~~~~~~");
    PrintKonfigurasiPermainan(Perm);
    ShowAvailableCommand();
    printf("~~~~~~~~~~~~~~~\n\n");


    /* Looping Command */
    turn = 1;
    finish = false;
    do{
        TulisPetaPermainan(Perm);
        printf("Player %d\n",turn);
        TulisDaftarBangunan(Perm,turn,&BanyakBangunan);
        printf("\n");

        /* boolean skill */
        ExtraTurn = false;
        do{ // command != "EXIT"
            printf("ENTER COMMAND: ");
            scanf("%s",s);
            command = StringtoKata(s);
            if (IsSamaKata(command,DaftarCommand[1])){ // command == "ATTACK"
                // CommandAttack(perm, turn);
            }
            else if (IsSamaKata(command,DaftarCommand[2])){ // command == "LEVEL_UP"
                CommandLevelUp(&Perm, turn);
            }
            else if (IsSamaKata(command,DaftarCommand[3])){ // command == "SKILL"
                // CommandSkill(&Perm, turn);
            } 
            else if (IsSamaKata(command,DaftarCommand[4])){ // command == "UNDO"
                // CommandUndo(&Perm, turn);
            }
            else if (IsSamaKata(command,DaftarCommand[5])){ // command == "END_TURN"
                // CommandEndTurn(&Perm, turn);
            }
            else if (IsSamaKata(command,DaftarCommand[6])){ // command == "SAVE"
                // CommandSave(&Perm, turn);
            }
            else if (IsSamaKata(command,DaftarCommand[7])){ // command == "MOVE"
                // CommandMove(&Perm, turn);
            }
            else if (IsSamaKata(command,DaftarCommand[8])){ // command == "EXIT"
                // CommandExit(&Perm,turn);
                finish = true;
            }
            else{
                printf("Input salah\n");
            }
            if (!finish) printf("\n");
        } while ( !finish && !IsSamaKata(command,DaftarCommand[5]) );
        
        if (!finish){
            printf("\n");
            if (!ExtraTurn) turn=turn%2+1;
        }
        
    }while(!finish);
}