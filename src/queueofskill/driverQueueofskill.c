/* File: driverQueueofskill.c */
/* Digunakan untuk mengetes semua primitif pada ADT Queueofskill */
#include "queueofskill.h"
#include "stdio.h"

int main() {
    /* KAMUS */
    int M;
    Queue Q;
    /* AGORITMA */
    CreateEmptyQueue(&Q, 2);
    if (IsQueueEmpty(Q)) {
        printf("Queue telah berhasil dibuat dengan maksimal %d elemen\n",MaxElQueue(Q));
    }
    printf("Jumlah elemen sekarang: %d\n",NBElmtQueue(Q));
    while (!IsQueueFull(Q)) {
        printf("Masukkan sebuah elemen ke dalam queue: ");
        scanf("%d",&M);
        Add(&Q,M);
        printf("Jumlah elemen sekarang: %d\n",NBElmtQueue(Q));
    }
    printf("Queue telah penuh\n");
    Del(&Q,&M);
    printf("Elemen head nya adalah %d\n",M);    
    printf("Jumlah elemen sekarang: %d\n",NBElmtQueue(Q));
    
    return 0;
}