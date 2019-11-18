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
    while (((CC==BLANK) || (CC==ENTER)) && (!EndPita)){
        ADV();
    }
}

void STARTKATA(char NamaFile[], boolean file){
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK;
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
    /* Kamus Lokal */

    /* Algoritma */
    START(NamaFile,file);
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

void SalinKata(){
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi;
          CC = BLANK atau EndPita = true;
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    /* Kamus Lokal */
    int i=1;

    /* Algoritma */
    while ((CC!=BLANK) && (CC!=ENTER) && (!EndPita)){
        if (i<=NMax){
            CKata.TabKata[i] = CC;
            i++;
        }
        ADV();
    }
    CKata.Length = i-1;
}

int CKatatoInt(){
/*  Mengembalikan integer dari kata */
    /* Kamus */
    int i,res;

    /* Algoritma */
    res=0;
    for (i=1;i<=CKata.Length;i++){
        res = res*10+(int) (CKata.TabKata[i]-'0');
    }
    return res;
}

Kata StringtoKata(char s[]){
/* Mengubah string menjadi Kata */
    int i=0;
    Kata kata;
    while(s[i]!='\0'){
        kata.TabKata[i+1]=s[i];
        i++;
    }
    kata.Length=i;
    return kata;
}

boolean IsSamaKata(Kata kata1,Kata kata2){
/* Mengembalikan true jika kata1=kata2 */
    if (kata1.Length==kata2.Length){
        int i=1;
        while ((i<kata1.Length) && (kata1.TabKata[i]==kata2.TabKata[i])){
            i++;
        }
        return (kata1.TabKata[i]==kata2.TabKata[i]);
    }
    else{
        return false;
    }
}