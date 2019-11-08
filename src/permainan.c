/* Nama file: permainan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "permainan.h"
#include "mesinkata.h"
#include "color.h"
#include <stdio.h>

void BacaKonfigurasi(char NamaFile[],Permainan *Perm){
/*  Membaca konfigurasi file dari 'NamaFile'
    I.S. = 'NamaFile' terdefinisi dan ada
    F.S. = Variabel Perm terinisialisasi */
    /* Kamus */
    int i,j,x,y;
    char tipe;

    /* Algoritma */
    STARTKATA(NamaFile);
    TinggiPeta(*Perm) = CKatatoInt();
    ADVKATA();
    LebarPeta(*Perm) = CKatatoInt();
    ADVKATA();
    JumlahBangunan(*Perm) = CKatatoInt();

    MakeEmptyTab(&DaftarBangunan(*Perm),JumlahBangunan(*Perm));
    MakeMATRIKS(TinggiPeta(*Perm),LebarPeta(*Perm),&Peta(*Perm));
    CreateEmpty(&ListBangunanP1(*Perm));
    CreateEmpty(&ListBangunanP2(*Perm));

    for (i=IdxMin;i<=(*Perm).B;i++){
        ADVKATA();
        tipe = CKata.TabKata[1];
        ADVKATA(); x=CKatatoInt();
        ADVKATA(); y=CKatatoInt();
        
        if (i<=2){
            Elmt(DaftarBangunan((*Perm)), i) = MakeBANGUNAN(tipe,MakePOINT(x,y),i);
            if (i==1){
                InsVFirst(&ListBangunanP1(*Perm),1);
            }
            else{
                InsVFirst(&ListBangunanP2(*Perm),2);
            }
        }
        else{
            Elmt(DaftarBangunan((*Perm)), i) = MakeBANGUNAN(tipe,MakePOINT(x,y),0);
        }

        NeffTab(DaftarBangunan(*Perm))++;
        ElmtMat(Peta(*Perm),x,y) = i;
    }

    /* Input keterhubungan */
}

void TulisPetaPermainan (Permainan Perm){
    for (int i=0;i<=TinggiPeta(Perm)+1;i++){
        for (int j=0;j<=LebarPeta(Perm)+1;j++){
            if (ElmtMat(Peta(Perm),i,j)==-1){
                printf("*");
            }
            else if (ElmtMat(Peta(Perm),i,j)==0){
                printf(" ");
            }
            else{
                if (Pemilik(Elmt(DaftarBangunan(Perm),ElmtMat(Peta(Perm),i,j)))==1 ){
                    blue();
                }
                else if (Pemilik(Elmt(DaftarBangunan(Perm),ElmtMat(Peta(Perm),i,j)))==2 ){
                    red();
                }
                printf("%c",JenisBangunan(Elmt(DaftarBangunan(Perm),ElmtMat(Peta(Perm),i,j))));

                if (Pemilik(Elmt(DaftarBangunan(Perm),ElmtMat(Peta(Perm),i,j)))!=0 ){
                    reset();
                }
            }
        }
        printf("\n");
    }
}

void TulisBangunanPlayer(List L,TabBANGUNAN tabBangunan){
    address P=First(L);
    int i=0;

    while (P!=Nil){
        i++;
        printf("%d. ",i);
        TulisBangunan(Elmt(tabBangunan,Info(P)));
        printf("\n");
        P=Next(P);
    }
}

void TulisDaftarBangunan(Permainan Perm,int turn){
    if (turn==1){
        TulisBangunanPlayer(ListBangunanP1(Perm),DaftarBangunan(Perm));
    }
    else{
        TulisBangunanPlayer(ListBangunanP2(Perm),DaftarBangunan(Perm));
    }
}
