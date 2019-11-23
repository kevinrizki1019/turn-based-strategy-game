/* Nama file: permainan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "permainan.h"

void BacaKonfigurasi(char NamaFile[],Permainan *Perm, boolean load, int *turn){
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
                // Menambahkan skill Instant Upgrade ke kedua lawan
                Add(&SkillPlayer(*Perm,i),1);
            }
            else{
                Elmt(DaftarBangunan((*Perm)), i) = MakeBANGUNAN(tipe,MakePOINT(x,y),0);
            }
        }
        else{
            ADVKATA(); pemilik = CKatatoInt();
            Elmt(DaftarBangunan(*Perm), i) = MakeBANGUNAN(tipe,MakePOINT(x,y),pemilik);

            ADVKATA();
            JumlahPasukan(Elmt(DaftarBangunan(*Perm),i)) = CKatatoInt(); // pasukan

            ADVKATA();
            Level(Elmt(DaftarBangunan(*Perm),i)) = CKatatoInt(); // level

            ADVKATA();
            SudahAttack(Elmt(DaftarBangunan(*Perm),i)) = CKatatoInt(); // SudahAttack

            ADVKATA();
            SudahMove(Elmt(DaftarBangunan(*Perm),i)) = CKatatoInt(); // SudahMove
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

    *turn = 1;
    if (load){  // melanjutkan baca file jika melalui proses load
        ADVKATA();
        *turn = CKatatoInt(); // turn
        for (int player=1; player<=2; ++player){
            int Nb;
            ADVKATA();
            Nb = CKatatoInt(); // Nb bangunan player
            for (int i=0; i<Nb; ++i){
                ADVKATA();
                InsVLast(&ListBangunanPlayer(*Perm,player),CKatatoInt());
            }
            ADVKATA();
            Nb = CKatatoInt(); // Nb skill player
            for (int i=0; i<Nb; ++i){
                ADVKATA();
                Add(&SkillPlayer(*Perm,player),CKatatoInt());
            }
        }
    }

}

void SimpanKonfigurasi(char NamaFile[], Permainan Perm, int turn){
    FILE *file = fopen(NamaFile,"w");
    fprintf(file,"%d %d\n%d\n",TinggiPeta(Perm),LebarPeta(Perm),JumlahBangunan(Perm));
    
    for (int idB=IdxMin; idB<=JumlahBangunan(Perm); idB++){
        BANGUNAN B = Elmt(DaftarBangunan(Perm),idB);
        POINT pos=Posisi(B);
        char jenis = JenisBangunan(B);
        int pemilik = Pemilik(B), pasukan = JumlahPasukan(B), level = Level(B);
        fprintf(file,"%c %d %d %d %d %d %d %d\n",
            jenis,Absis(pos),Ordinat(pos),pemilik,pasukan,level,SudahAttack(B),SudahMove(B));
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

    // tulis turn dan atribut player
    fprintf(file,"%d\n",turn);
    for (int i=1;i<=2;++i){
        fprintf(file,"%d\n",NbElmtList(ListBangunanPlayer(Perm,i)));
        address P = First(ListBangunanPlayer(Perm,i));
        while (P!=Nil){
            fprintf(file,"%d",Info(P));
            if (Next(P)!=Nil){
                fprintf(file," ");
            }
            else{
                fprintf(file,"\n");
            }
            P = Next(P);
        }
        int n = NBElmtQueue(SkillPlayer(Perm,i));
        fprintf(file,"%d\n",n);
        for (int k=0; k<n; ++k){
            infoQueue x;
            Del(&SkillPlayer(Perm,i),&x);
            fprintf(file,"%d",x);
            if (k==n-1){
                fprintf(file,"\n");
            }
            else{
                fprintf(file," ");
            }
            Add(&SkillPlayer(Perm,i),x);
        }
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
    printf("~~~~~~~~~~WORLD WAR~~~~~~~~~~~     \n");
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

void InitListPlayer(List L,TabBANGUNAN *tabel){
    address P = First(L);
    while(P != Nil){
        SudahAttack(Elmt(*tabel,Info(P))) = false;
        SudahMove(Elmt(*tabel,Info(P))) = false;
        P = Next(P);
    }
}

void TulisDaftarBangunan(List ListPlayer,TabBANGUNAN tabBangunan,int *n,int *n_atck,int *n_move,char tipe){
    address P=First(ListPlayer);

    *n = 0; *n_atck = 0; *n_move = 0;
    while (P!=Nil){
        if ((tipe=='0') || ((tipe=='1') && (!SudahAttack(Elmt(tabBangunan,Info(P))))) || ((tipe=='2') && (!SudahMove(Elmt(tabBangunan,Info(P)))))){
            printf("%d. ",++(*n));
            TulisBangunan(Elmt(tabBangunan,Info(P)));
            printf("\n");
        }
        if (!SudahAttack(Elmt(tabBangunan,Info(P)))) ++(*n_atck);
        if (!SudahMove(Elmt(tabBangunan,Info(P)))) ++(*n_move);
        P=Next(P);
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
                    printf("\n%d.", ++(*n));
                    TulisBangunan(Elmt(DB,adj_id));
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
                    printf("\n%d.", ++(*n));
                    TulisBangunan(Elmt(DB,adj_id));
                    
                }
                A = NextAdj(A);
            }
        }
    }
}