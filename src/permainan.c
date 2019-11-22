/* Nama file: permainan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "permainan.h"
#include <stdio.h>

void BacaKonfigurasi(char NamaFile[],Permainan *Perm, boolean load){
/*  Membaca konfigurasi file dari 'NamaFile'
    I.S. = 'NamaFile' terdefinisi dan ada
    F.S. = Variabel Perm terinisialisasi */
    /* Kamus */
    int i,j,x,y,n,m,b,pemilik;
    char tipe;

    /* Algoritma */
    STARTKATA(NamaFile,true);
    n = CKatatoInt();
    ADVKATA();
    m = CKatatoInt();
    ADVKATA();
    b = CKatatoInt(); // banyak bangunan

    MakeEmptyTab(&DaftarBangunan(*Perm),b);
    MakeMATRIKS(n,m,&Peta(*Perm));
    CreateGraph(&Graph(*Perm),b);

    for (int player=1;player<=2;++player){
        CreateEmpty(&ListBangunanPlayer(*Perm,player));
        CreateEmptyQueue(&SkillPlayer(*Perm,player),10);
        Add(&SkillPlayer(*Perm,player),1);
    }


    for (i=IdxMin;i<=b;i++){
        ADVKATA();
        tipe = CKata.TabKata[1];
        ADVKATA(); x=CKatatoInt();
        ADVKATA(); y=CKatatoInt();
        
        if (!load){
            if (i<=2){
                Elmt(DaftarBangunan((*Perm)), i) = MakeBANGUNAN(tipe,MakePOINT(x,y),i);
                InsVFirst(&ListBangunanPlayer(*Perm,i),i);
            }
            else{
                Elmt(DaftarBangunan((*Perm)), i) = MakeBANGUNAN(tipe,MakePOINT(x,y),0);
            }
        }
        else{
            ADVKATA(); pemilik = CKatatoInt();
            Elmt(DaftarBangunan((*Perm)), i) = MakeBANGUNAN(tipe,MakePOINT(x,y),pemilik);
            if ((pemilik==1) || (pemilik==2)){
                InsVLast(&ListBangunanPlayer(*Perm,pemilik),i);
            }
        }

        NeffTab(DaftarBangunan(*Perm))++;
        ElmtMat(Peta(*Perm),x,y) = i; // mengeset id bangunan pada matriks peta
    }

    /* Input keterhubungan */
    for (i=IdxMin;i<=b;i++){
        for (j=IdxMin;j<=b;j++){
            ADVKATA();
            if (j>i){
                x = CKatatoInt();
                if (x==1){
                    MakeTerhubung(&Graph(*Perm),i,j);
                }
            }
        }
    }
}

void SimpanKonfigurasi(char NamaFile[], Permainan Perm, int turn){
    FILE *file = fopen(NamaFile,"w");
    fprintf(file,"%d %d\n%d\n",TinggiPeta(Perm),LebarPeta(Perm),JumlahBangunan(Perm));
    
    for (int idB=IdxMin; idB<=JumlahBangunan(Perm); idB++){
        POINT pos=Posisi(Elmt(DaftarBangunan(Perm),idB));
        char jenis = JenisBangunan(Elmt(DaftarBangunan(Perm),idB));
        int pemilik = Pemilik(Elmt(DaftarBangunan(Perm),idB));
        fprintf(file,"%c %d %d %d\n",jenis,Absis(pos),Ordinat(pos),pemilik);
    }
    
    adrver verNow = FirstVer(Graph(Perm));
    for (int i=IdxMin; i<=JumlahBangunan(Perm); i++){
        adradj adjNow = FirstAdj(verNow);
        for (int j=IdxMin; j<=JumlahBangunan(Perm); j++){
            if (adjNow==Nil){
                fprintf(file,"0");
            }
            else{
                if (InfoAdj(adjNow)==j){
                    fprintf(file,"1");
                    adjNow = NextAdj(adjNow);
                }
                else{
                    fprintf(file,"0");
                }
            }
            if (j<JumlahBangunan(Perm)){
                fprintf(file," ");
            }
        }
        fprintf(file,"\n");
        verNow = NextVer(verNow);
    }
    fclose(file);
}


void PrintKonfigurasiPermainan(Permainan Perm) {
    int i;
    
    printf("\nDimensi Peta\n");
    printf("Tinggi: %d\n",TinggiPeta(Perm));
    printf("Lebar: %d\n",LebarPeta(Perm));
    printf("Jumlah Bangunan: %d\n\n",JumlahBangunan(Perm));
    
    printf("Daftar Bangunan:\n");
    for (i=IdxMin;i<=JumlahBangunan(Perm);i++){
        printf("%d. ",i);
        TulisBangunan(Perm.DaftarBangunan.TB[i]);
        printf("\n");
    }

    printf("\nKeterhubungan Bangunan:\n");
    PrintKeterhubungan(Graph(Perm));
    
    printf("\n");
}

void TulisLogoPermainan() {
    printf("\n");
    red();  
    printf("   /|       /\\       |\\           \n");
    printf("  / | |  / /  \\   |  | \\   |~~    \n");    
    reset();
    blue(); 
    printf(" / ~| | / / ~ ~\\ ~|~ | ~\\  |      \n");
    printf("/   | |/ /      \\ |/ |   \\ |      \n");       
    printf("~~~~~~~~~WORLD WAR~~~~~~~~~~~~~     \n");
    reset();
    brightwhite();
    printf("NEW GAME(1)      LOAD GAME(2)              \n");
    reset();
}

void TulisPetaPermainan (Permainan Perm){
    for (int i=0;i<=TinggiPeta(Perm)+1;i++){
        if (NbElmtList(ListBangunanPlayer(Perm,1)) > NbElmtList(ListBangunanPlayer(Perm,2))) {
            bgblue();
        } else if ((NbElmtList(ListBangunanPlayer(Perm,1)) < NbElmtList(ListBangunanPlayer(Perm,2)))) {
            bgred();
        } else {
            bgwhite();
        }  
        printf(" ");
        reset();
        for (int j=0;j<=LebarPeta(Perm)+1;j++){
            if (ElmtMat(Peta(Perm),i,j)==-1){
                if (NbElmtList(ListBangunanPlayer(Perm,1)) > NbElmtList(ListBangunanPlayer(Perm,2))) {
                    bgblue();
                } else if ((NbElmtList(ListBangunanPlayer(Perm,1)) < NbElmtList(ListBangunanPlayer(Perm,2)))) {
                    bgred();
                } else {
                    bgwhite();
                }
                printf(" ");
                reset();
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
            if ((i==0 || i==TinggiPeta(Perm)+1) || j==LebarPeta(Perm)+1) {
                if (NbElmtList(ListBangunanPlayer(Perm,1)) > NbElmtList(ListBangunanPlayer(Perm,2))) {
                    bgblue();
                } else if ((NbElmtList(ListBangunanPlayer(Perm,1)) < NbElmtList(ListBangunanPlayer(Perm,2)))) {
                    bgred();
                } else {
                    bgwhite();
                }  
            }
            printf(" ");
            reset();
        }
        printf("\n");
    }
    reset();
}

void TulisDaftarBangunan(List ListPlayer,TabBANGUNAN tabBangunan,int *n){
    address P=First(ListPlayer);

    *n = 0;
    while (P!=Nil){
        printf("%d. ",++(*n));
        TulisBangunan(Elmt(tabBangunan,Info(P)));
        printf("\n");
        P=Next(P);
    }
}

void TulisDaftarBangunanTerhubung(Permainan Perm, int Id, int *n)
{
    int adj_id;
    TabBANGUNAN DB;
    adrver V;
    adradj A;

    DB = DaftarBangunan(Perm);
    *n = 0;
    if (FirstVer(Graph(Perm)) != Nil) {
        V = SearchVer(Graph(Perm),Id);
        if (FirstAdj(V) != Nil) {
            A = FirstAdj(V);
            while (A != Nil) {
                printf("%d.", ++(*n));
                adj_id = InfoAdj(A);
                TulisBangunan(Elmt(DB,adj_id));
                if (NextAdj(A) != Nil) {
                    printf("\n");
                }

                A = NextAdj(A);
            }
        }
    }
}

void TulisDaftarBangunanMusuhTerhubung(Permainan Perm, int Id, int *n, int turn) {
    int adj_id;
    TabBANGUNAN DB;
    adrver V;
    adradj A;

    DB = DaftarBangunan(Perm);
    *n = 0;
    if (FirstVer(Graph(Perm)) != Nil) {
        V = SearchVer(Graph(Perm),Id);
        if (FirstAdj(V) != Nil) {
            
            A = FirstAdj(V);
            while (A != Nil) {
                adj_id = InfoAdj(A);
                if (Pemilik(Elmt(DB,adj_id)) != turn) {
                    printf("%d.", ++(*n));
                    TulisBangunan(Elmt(DB,adj_id));
                    
                    if (NextAdj(A) != Nil) {
                        printf("\n");
                    }
                }
                A = NextAdj(A);
            }
        }
    }
}

void TulisDaftarBangunanPlayerTerhubung(Permainan Perm, int Id, int *n, int turn) {
    int adj_id;
    TabBANGUNAN DB;
    adrver V;
    adradj A;

    DB = DaftarBangunan(Perm);
    *n = 0;
    if (FirstVer(Graph(Perm)) != Nil) {
        V = SearchVer(Graph(Perm),Id);
        if (FirstAdj(V) != Nil) {
            
            A = FirstAdj(V);
            while (A != Nil) {
                adj_id = InfoAdj(A);
                if (Pemilik(Elmt(DB,adj_id)) == turn) {
                    printf("%d.", ++(*n));
                    TulisBangunan(Elmt(DB,adj_id));
                    
                    if (NextAdj(A) != Nil) {
                        printf("\n");
                    }
                }
                A = NextAdj(A);
            }
        }
    }
}