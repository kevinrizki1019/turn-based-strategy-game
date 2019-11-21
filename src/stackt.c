#include "stackt.h"


/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack(Stack *S){
    Top(*S) =  0;
}

infoStack MakeInfoStack(BANGUNAN B, int id, int jenis){
    infoStack res;
    res.bangunan = B;
    res.idBangunan = id;
    res.jenis = jenis;
    return res;
}


/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsStackEmpty (Stack S){
    return (Top(S)==0);
}

boolean IsStackFull (Stack S){
    return (Top(S)==MaxElStack);
}


/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infoStack X){
/* Menambahkan X sebagai elemen Stack S. */
    Top(*S) +=1;
    S->T[Top(*S)] = X;
}


/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infoStack* X){
/* Menghapus X dari Stack S. */
    *X = InfoTop(*S);
    Top(*S) -=1;
}