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
    int i,turn=1,idx;
    boolean finish = false;

    /* Algoritma */
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
    printf("%d %d %d\n",TinggiPeta(Perm),LebarPeta(Perm),JumlahBangunan(Perm));
    for (i=IdxMin;i<=JumlahBangunan(Perm);i++){
        printf("%d. ",i);
        TulisBangunan(Perm.DaftarBangunan.TB[i]);
        printf("\n");
    }
    PrintKeterhubungan(Graph(Perm));
    /* Looping Command */
    do{
        TulisPetaPermainan(Perm);
        printf("Player %d\n",turn);
        TulisDaftarBangunan(Perm,turn);
        printf("\n");

        do{ // command != "EXIT"
            printf("ENTER COMMAND: ");
            scanf("%s",s);
            command = StringtoKata(s);
            if (IsSamaKata(command,DaftarCommand[1])){ // command == "ATTACK"
                //attack(perm, turn);
            }
            else if (IsSamaKata(command,DaftarCommand[2])){ // command == "LEVEL_UP"
                printf("Daftar bangunan:\n");
                TulisDaftarBangunan(Perm,turn);
                printf("Bangunan yang akan di level up: ");
                scanf("%d",&idx);
            }
            else if (IsSamaKata(command,DaftarCommand[8])){ // command == "EXIT"
                finish = true;
            }
            else{
                printf("Input salah\n");
            }
            if (!finish) printf("\n");
        }while ( !finish && !IsSamaKata(command,DaftarCommand[5]) );
        
        if (!finish){
            printf("\n");
            turn=turn%2+1;
        }
    }while(!finish);
}