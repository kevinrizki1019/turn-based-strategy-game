/* File: mesinkata.h */
/* Realisasi Mesin Kata */

#include "mesinkata.h"
#include <stdio.h>


/* State Mesin Kata */
Kata CKata;

void IgnoreBlank(){
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC ≠ BLANK */
    while ((CC==BLANK) && (!EndPita)){
        ADV();
    }
}

void STARTKATA(char NamaFile[]){
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
    /* Kamus Lokal */

    /* Algoritma */
    START(NamaFile);
    IgnoreBlank();
    if (!EndPita){
        SalinKata();
    }
}

void ADVKATA(){
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi,
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi,
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.
   Proses : Akuisisi kata menggunakan procedure SalinKata */
    IgnoreBlank();
    if (!EndPita){
        SalinKata();
    }
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau CC = MARK;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    /* Kamus Lokal */
    int i=1;

    /* Algoritma */
    while ((CC!=BLANK) && (!EndPita)){
        if (i<=NMax){
            CKata.TabKata[i] = CC;
            printf("%c %d\n",CC,i);
            i++;
        }
        ADV();
    }
    CKata.Length = i-1;
}
