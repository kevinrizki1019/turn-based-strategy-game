#include "stackt.h"


/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack(Stack *S){
    Top(*S) =  0;
}


/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsStackEmpty (Stack S){
    return (Top(S)==0);
}

boolean IsStackFull (Stack S){
    return (Top(S)==MaxElStack);
}


/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infotype X){
/* Menambahkan X sebagai elemen Stack S. */
    Top(*S) +=1;
    S->T[Top(*S)] = X;
}


/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infotype* X){
/* Menghapus X dari Stack S. */
    *X = InfoTop(*S);
    Top(*S) -=1;
}