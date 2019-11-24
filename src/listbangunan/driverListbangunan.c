/* File: driverListbangunan.c */
/* Digunakan untuk mengetes semua primitif pada ADT List Bangunan */
#include "listbangunan.h"
#include "stdio.h"

int main() {
    /* KAMUS */
    int e;
    List L1;
    /* ALGORITMA */
    CreateEmpty(&L1);
    printf("%d\n",(NbElmtList(L1)));
    InsVFirst(&L1,10);
    printf("%d\n",(NbElmtList(L1)));
    InsVLast(&L1,11);
    printf("%d\n",(NbElmtList(L1)));
    InsVatIdx(&L1,12,3);
    printf("%d\n",(NbElmtList(L1)));
    DelVFirst(&L1,&e);
    printf("%d\n",(NbElmtList(L1)));
    printf("%d\n",e);
    DelVLast(&L1,&e);
    printf("%d\n",(NbElmtList(L1)));
    printf("%d\n",e);
    DelP(&L1,11);
    printf("%d\n",(NbElmtList(L1)));

    return 0;
}