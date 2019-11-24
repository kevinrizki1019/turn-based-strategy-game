/* File: driverMesinKata.c */
/* Digunakan untuk mengetes semua primitif pada ADT Mesin Kata */

#include "mesinkata.h"
#include <stdio.h>

int main(){
    printf("Masukkan kata bebas: ");
    STARTKATA("stdin",false);
    printf("Berikut kata yang Anda masukkan: ");
    for (int i=1; i<=CKata.Length; ++i){
        printf("%c",CKata.TabKata[i]);
    }
    printf("\n\n");

    printf("Masukkan angka bebas: ");
    STARTKATA("stdin",false);
    printf("Berikut angka yang Anda masukkan: ");
    printf("%d\n\n",CKatatoInt());

    printf("Masukkan direktori file yang akan dibaca: ");
    char namafile[255];
    scanf("%s",namafile);
    STARTKATA(namafile,true);
    while(!EndPita){
        for (int i=1; i<=CKata.Length; ++i){
            printf("%c",CKata.TabKata[i]);
        }
        printf("\n");
        ADVKATA();
    }

    return 0;
}