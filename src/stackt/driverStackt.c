/* File: driverStackt.c */
/* Digunakan untuk mengetes semua primitif pada ADT Stackt */
#include "stackt.h"
#include <stdio.h>

int main(){
    /* Kamus */
    BANGUNAN b;
    Stack s;
    /* Algoritma */
    CreateEmptyStack(&s);
    printf("Stack kosong: %d\n",IsStackEmpty(s));
    for (int i=0; i<6; ++i){
        b = MakeBANGUNAN('C',MakePOINT(i,5-i),0);
        Push(&s,MakeInfoStack(b,i,i%2,false));
    }
    while (!IsStackEmpty(s))
    {
        infoStack x;
        Pop(&s,&x);
        TulisBangunan(x.bangunan);
        printf(" %d %d\n",x.idBangunan,x.jenis);
    }
    
    return 0;
}