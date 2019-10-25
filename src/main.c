#include "permainan.h"
#include <stdio.h>
#include <unistd.h>

#define NMaxStr 255


int main(){
    /* Kamus */
    Permainan Perm;
    char s[NMaxStr];
    int i;

    /* Algoritma */
    do{
        printf("Masukkan nama file: ");
        scanf("%s",s);
    }while( access(s,R_OK) == -1 );
    BacaKonfigurasi(s,&Perm);
    printf("%d %d %d\n",Perm.N,Perm.M,Perm.B);
    for (i=IdxMin;i<=Perm.B;i++){
        printf("%d. ",i);
        TulisBangunan(Perm.DaftarBangunan.TB[i]);
        printf("\n");
    }
}