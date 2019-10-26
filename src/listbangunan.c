#include "boolean.h"
#include <stdio.h>
#include "listbangunan.h"

boolean IsEmpty (List L){
    return (First(L) ==  Nil);
}

void CreateEmpty (List *L){
    First(*L) = Nil;
}

address Alokasi (BANGUNAN X){
    address P;

    P = (address) malloc (sizeof (ElmtList));
    if (P != Nil) {
        Info(P) = X;
        Next(P) = Nil;
        return P;
    } 
    else {
        return Nil;
    }
}

void Dealokasi (address *P){
    free(*P);
}

address Search (List L, BANGUNAN X){
    address P;
    
    P = First(L);
    while (P != Nil) {
        if (IsBangunanSama(X, Info(P))) {return P;}
        P = Next(P);
    }
    return P;
}

void InsVFirst (List *L, BANGUNAN X) {
    address P;
    
    P = Alokasi(X);
    if (P != Nil) {
      InsertFirst(L,P);
    }
}

void InsVLast (List *L, BANGUNAN X) {
    address P;

    P = Alokasi(X);
    if (P != Nil) {
      InsertLast(L,P);
    }
}

void DelVFirst (List *L, BANGUNAN *X) {
    address P;

    P = First(*L);
    (*X) = Info(P);
    First(*L) = Next(First(*L));
    Next(P) = Nil;
    Dealokasi(&P);
}

void DelVLast (List *L, BANGUNAN *X) {
    address P;

    DelLast(L,&P);
    (*X) = Info(P);
    Dealokasi(&P);
}

void InsertFirst (List *L, address P) {
    Next(P) = First(*L);
    First(*L) = P;
}

void InsertAfter (List *L, address P, address Prec) {
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

void InsertLast (List *L, address P) {
    address Last;

    Last = First(*L);
    if (First(*L) == Nil) {
      InsertFirst(L,P);
    } else {
      while (Next(Last) != Nil) {
        Last = Next(Last);
      }
      InsertAfter(L,P,Last);
    }
}

void DelFirst (List *L, address *P) {
    *P = First(*L);
    First(*L) = Next(First(*L));
}

void DelP (List *L, BANGUNAN X) {
    address P, Prec;
    BANGUNAN Y;

    P = First(*L);
    if (IsBangunanSama(X, Info(P))) {
        DelVFirst(L,&Y);
    } 
    else {
        Prec = Nil;
        while (P != Nil) {
            if (IsBangunanSama(Info(P), X)) {
                DelAfter(L,&P,Prec);
                Dealokasi(&P);
                return;
            } 
            else {
                Prec = P;
                P = Next(P);
            }
        }
    }
}

void DelLast (List *L, address *P){
    address Last, PrecLast;
    
    Last = First(*L);
    PrecLast = Nil;
    while (Next(Last) != Nil) {
        PrecLast = Last;
        Last = Next(Last);
    }
    *P = Last;
    if (PrecLast == Nil) {
        First(*L) = Nil;
    } 
    else {
        Next(PrecLast) = Nil;
    }
}

void DelAfter (List *L, address *Pdel, address Prec) {
    *Pdel = Next(Prec);
    Next(Prec) = Next(Next(Prec));
    Next(*Pdel) = Nil;
}

int NbElmt (List L) {
    address P;
    int n = 0;

    P = First(L);
    while (P != Nil) {
        n++;
        P = Next(P);
    }
    return n;
}