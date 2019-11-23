/* Nama file: listbangunan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "listbangunan.h"

boolean IsEmptyList (List L){
    return (First(L) ==  Nil);
}

void CreateEmpty (List *L){
    First(*L) = Nil;
}

address Alokasi (int X){
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

address Search (List L, int X){
    address P;
    boolean found = false;
    
    P = First(L);
    while ((P != Nil) && (!found)) {
        if (X==Info(P)){
            found = true;
        }
        else{
            P = Next(P);
        }
    }
    return P;
}


int GetIdFromList (List L, int n) {
    int i;
    address P;

    if (!IsEmptyList(L)) {
        P = First(L);
        for (i=1; i<n; i++) {
            P = Next(P);
        }
    }
    return Info(P);
}

int GetIdxFromList (List L, int n){
    int i;
    address P;

    i = 1;
    P = First(L);
    while (Info(P)!=n){
        ++i;
        P = Next(P);
    }
    return i;
}

void InsVFirst (List *L, int X) {
    address P;
    
    P = Alokasi(X);
    if (P != Nil) {
      InsertFirst(L,P);
    }
}

void InsVLast (List *L, int X) {
    address P;

    P = Alokasi(X);
    if (P != Nil) {
      InsertLast(L,P);
    }
}

void InsVatIdx (List *L, int X, int idx){
    address now,P;

    if (idx==1){
        InsVFirst(L,X);
    }
    else{
        P = Alokasi(X);
        if (P==Nil) return;
        printf("jancuk\n");
        now = First(*L);
        --idx;
        while (--idx){
            now = Next(now);
        }
        // berhenti sblm idx
        Next(P) = Next(now);
        Next(now) = P;
    }
}

void DelVFirst (List *L, int *X) {
    address P;

    P = First(*L);
    (*X) = Info(P);
    First(*L) = Next(First(*L));
    Next(P) = Nil;
    Dealokasi(&P);
}

void DelVLast (List *L, int *X) {
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

void DelP (List *L, int X) {
    address P, Prec;
    int Y;

    P = First(*L);
    if (X==Info(P)) {
        DelVFirst(L,&Y);
    } 
    else {
        Prec = Nil;
        while (P != Nil) {
            if (Info(P)==X) {
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

int NbElmtList (List L) {
    address P;
    int n = 0;

    P = First(L);
    while (P != Nil) {
        n++;
        P = Next(P);
    }
    return n;
}

void CopyList (List Lin, List *Lout) {
    address P;
    
    CreateEmpty(Lout);
    if (!IsEmptyList(Lin)) {
        P = First(Lin);
        while (P != Nil) {
            InsVLast(Lout, Info(P));
            P = Next(P);
        }
    }
}
