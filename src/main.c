#include "permainan.h"
#include "mesinkata.h"
#include "command.h"
#include <stdio.h>
#include <unistd.h>

#define NMaxStr 255

void TulisDaftarBangunan(Permainan Perm,int turn){
    if (turn==1){
        TulisBangunanPlayer(ListBangunanP1(Perm),DaftarBangunan(Perm));
    }
    else{
        TulisBangunanPlayer(ListBangunanP2(Perm),DaftarBangunan(Perm));
    }
}


int main(){
    /* Silakan mencoba codingan di bawah ini */



    /* Jangan mengahapus codingan dibawah karena untuk main program */
    // /* Kamus */
    // Permainan Perm;
    // char s[NMaxStr];
    // Kata command;
    // int i,turn=1,idx;
    // boolean finish = false;

    // /* Algoritma */
    // InitDaftarCommand();
    // do{
    //     printf("Masukkan nama file: ");
    //     scanf("%s",s);
    // }while( access(s,R_OK) == -1 );
    
    // BacaKonfigurasi(s,&Perm);
    // printf("%d %d %d\n",Perm.N,Perm.M,Perm.B);
    // for (i=IdxMin;i<=Perm.B;i++){
    //     printf("%d. ",i);
    //     TulisBangunan(Perm.DaftarBangunan.TB[i]);
    //     printf("\n");
    // }

    // /* Looping Command */
    // do{
    //     TulisPetaPermainan(Perm);
    //     printf("Player %d\n",turn);

        
        
    //     do{ // command != "EXIT"
    //         printf("ENTER COMMAND: ");
    //         scanf("%s",s);
    //         command = StringtoKata(s);
    //         if (IsSamaKata(command,DaftarCommand[1])){ // command == "ATTACK"
    //             TulisDaftarBangunan(Perm,turn);
    //             printf("Bangunan yang digunakan untuk menyerang: ");
    //             scanf("%d",&idx);
    //         }
    //         else if (IsSamaKata(command,DaftarCommand[2])){ // command == "LEVEL_UP"
    //             TulisDaftarBangunan(Perm,turn);
    //             printf("Bangunan yang akan di level up: ");
    //             scanf("%d",&idx);
    //         }
    //         else if (IsSamaKata(command,DaftarCommand[8])){ // command == "EXIT"
    //             finish = true;
    //         }
    //         if (!finish) printf("\n");
    //     }while ( !finish && !IsSamaKata(command,DaftarCommand[5]) );
        
    //     if (!finish){
    //         printf("\n");
    //         turn=turn%2+1;
    //     }
    // }while(!finish);
}