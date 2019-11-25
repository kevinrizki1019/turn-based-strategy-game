/* Nama file: command.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */
/* Mengolah command (input) dari user */

#include "command.h"

Kata DaftarCommand[9]; /* Berisi 8 daftar command yang bisa dilakukan. Indeks 0 tidak digunakan */

void InitDaftarCommand(){
/* Mengisi array DaftarCommand */
    DaftarCommand[1] = StringtoKata("ATTACK");
    DaftarCommand[2] = StringtoKata("LEVEL_UP");
    DaftarCommand[3] = StringtoKata("SKILL");
    DaftarCommand[4] = StringtoKata("UNDO");
    DaftarCommand[5] = StringtoKata("END_TURN");
    DaftarCommand[6] = StringtoKata("SAVE");
    DaftarCommand[7] = StringtoKata("MOVE");
    DaftarCommand[8] = StringtoKata("EXIT");
}

void ShowAvailableCommand() {
    printf("Daftar Command:\n");
    
    printf("- ");
    green();
    printf("ATTACK\n");
    reset();
    printf("- ");
    green();
    printf("LEVEL_UP\n");
    reset();
    printf("- ");
    green();
    printf("SKILL\n");
    reset();
    printf("- ");
    green();
    printf("UNDO\n");
    reset();
    printf("- ");
    green();
    printf("END_TURN\n");
    reset();
    printf("- ");
    green();
    printf("SAVE\n");
    reset();
    printf("- ");
    green();
    printf("MOVE\n");
    reset();
    printf("- ");
    green();
    printf("EXIT\n");
    reset();
}
    
/* IMPLEMENTASI PROSEDUR-PROSEDUR COMMAND */
void CommandAttack(Permainan *perm, int turn) {
    IdxType idPenyerang,idDiSerang;
    int idxPenyerang,idxDiSerang,BanyakBangunanPenyerang,BanyakBangunanDapatDiSerang, jumlahPasukanPenyerang, 
        jumlahPasukanDiSerang,jumlahPasukanPenyerangEfektif,n_bangunan,n_move;
    BANGUNAN *bangunanPenyerang, *bangunanDiSerang;

    /* Mencetak daftar bangunan player */
    /* Satu bangunan cuman bisa nyerang sekali -> buat mark, jadi kalo udah nyerang gak ditampilin lagi di sini */
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(ListBangunanPlayer(*perm,turn),DaftarBangunan(*perm),&n_bangunan,&BanyakBangunanPenyerang,&n_move,'1'); 

    /* Input player bangunan mana yang digunakan untuk menyerang */
    /* Input pengguna bangunan mana yang ingin digunakan untuk menyerang */
    idxPenyerang = InputPenggunaValidDalamRange (1, BanyakBangunanPenyerang, "Bangunan yang akan digunakan untuk menyerang: ");
    idPenyerang = GetIdBaseOnTurn(ListBangunanPlayer(*perm,turn),DaftarBangunan(*perm),idxPenyerang,true);;

    /* Mencetak daftar bangunan yang terhubung dengan bangunan player yang dipilih jika ada */
    printf("Daftar bangunan yang dapat diserang:");
    TulisDaftarBangunanMusuhTerhubung(*perm,idPenyerang,&BanyakBangunanDapatDiSerang,turn);
    printf("\n");
    
    if (BanyakBangunanDapatDiSerang == 0) {
        printf("Tidak ada bangunan yang dapat diserang\n");
    } else {
        int i=1,count=0;
        if (PlayerPerm(*perm,turn%2+1).Shield>0){
            printf("Shield musuh aktif\n");
        }
        /* Meminta input bangunan diserang */
        idxDiSerang = InputPenggunaValidDalamRange (1, BanyakBangunanDapatDiSerang, "Bangunan yang diserang: ");
        // Mengincrement idxDiSerang agar bangunan yang sudah dimiliki si penyerang tidak ditampilkan ke opsi
        do {
            idDiSerang = GetIdAdj(Graph(*perm),idPenyerang,i);
            if (Pemilik(Elmt(DaftarBangunan(*perm),idDiSerang)) != turn){      
                count++;
            }
            i++;
        } while (count!=idxDiSerang);
        
        /* Meminta input jumlah pasukan untuk menyerang */
        jumlahPasukanPenyerang = InputPenggunaValidDalamRange (0, JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenyerang)),"Jumlah pasukan: ");
        jumlahPasukanDiSerang = JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang));
        /* Cek pertahanan, Pertahanan(B) */
        boolean pertahanan = (Pertahanan(Elmt(DaftarBangunan(*perm),idDiSerang)) || (PlayerPerm(*perm,turn%2+1).Shield>0)) &&
                                (!((*perm).AttackUp)) && (!((*perm).CriticalHit));
        if (pertahanan) {
            jumlahPasukanPenyerangEfektif = jumlahPasukanPenyerang * 3 / 4;
        } else if ((*perm).CriticalHit) {
            jumlahPasukanPenyerangEfektif = 2*jumlahPasukanPenyerang;
        } else {
            jumlahPasukanPenyerangEfektif = jumlahPasukanPenyerang;
        }
        /* MELAKUKAN SERANGAN */
        /* Melakukan pembandingan jumlah pasukan bangunan penyerang dan diserang */
        if (jumlahPasukanPenyerangEfektif < jumlahPasukanDiSerang) {
            printf("Bangunan gagal direbut. \n");
            Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idPenyerang),idPenyerang,-1,(*perm).CriticalHit));
            Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idDiSerang),idDiSerang,-1,(*perm).CriticalHit));
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenyerang)) -= jumlahPasukanPenyerang;
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang)) -= jumlahPasukanPenyerangEfektif;
        } else {
            printf("Bangunan menjadi milikmu! \n");
            // mengatur stack
            Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idPenyerang),idPenyerang,-2,(*perm).CriticalHit));
            if (Pemilik(Elmt(DaftarBangunan(*perm),idDiSerang))==turn%2+1){     // apabila milik player lain maka dipush idx list nya
                int idx = GetIdxFromList(ListBangunanPlayer(*perm,(turn%2+1)),idDiSerang);
                Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idDiSerang),idDiSerang,idx,(*perm).CriticalHit));
                if (JenisBangunan(Elmt(DaftarBangunan(*perm),idDiSerang))=='F'){
                    // Menambahkan skill Extra Turn ke lawan
                    Add(&SkillPlayer(*perm,(turn%2+1)),3);
                }
                if (NbElmtList(ListBangunanPlayer(*perm,turn%2+1))==3){
                    // Menambahkan skill Shield ke lawan
                    Add(&SkillPlayer(*perm,(turn%2+1)),2);
                }
                if (CanGetAttackUp(perm,turn,idDiSerang)){
                    // Menambahkan skill Attack Up ke player
                    Add(&SkillPlayer(*perm,turn),4);
                }
            }
            else{
                Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idDiSerang),idDiSerang,-2,(*perm).CriticalHit));
            }
            // mengatur pengurangan pasukan
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenyerang)) -= jumlahPasukanPenyerang;
            if (pertahanan) {
                jumlahPasukanPenyerangEfektif = jumlahPasukanPenyerang - (JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang))+2)/3;
            }
            else if ((*perm).CriticalHit){
                jumlahPasukanPenyerangEfektif = jumlahPasukanPenyerang + (JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang))+1)/2;
                (*perm).CriticalHit = false;
            }
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang)) = jumlahPasukanPenyerangEfektif - JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang));
            AkuisisiBangunan(perm, idDiSerang, turn);
            if (n_bangunan==9){
                // Menambahkan skill Barage ke lawan
                Add(&SkillPlayer(*perm,(turn%2+1)),7);
            }
        }
        // set boolean sudah menyerang
        SudahAttack(Elmt(DaftarBangunan(*perm),idPenyerang)) = true;
        /* Cek skill AttackUp dan CriticalHit */
    }
}
void CommandLevelUp(Permainan *perm,int turn) {  
    int IdBangunan,BanyakBangunan,n_atck,n_move,idx;
    boolean success;
    BANGUNAN B_lama;

    /* Mencetak daftar bangunan player*/ 
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(ListBangunanPlayer(*perm,turn),DaftarBangunan(*perm),&BanyakBangunan,&n_atck,&n_move,'0');
    
    /* Input pengguna bangunan mana yang ingin di level up */
    idx = InputPenggunaValidDalamRange(1,BanyakBangunan,"Bangunan yang akan di level up : ");

    /* Mendapatkan IdBangunan mana yang akan di level up */
    IdBangunan = GetIdFromList(ListBangunanPlayer(*perm,turn),idx);

    /* Menambah level, evaluasi kevalidan penambahan pasukan ada di dalam prosedur  */
    TambahSatuLevel(&Elmt(DaftarBangunan(*perm),IdBangunan),&success,&B_lama);
    
    if (success){
        Push(&StackPerm(*perm),MakeInfoStack(B_lama,IdBangunan,0,(*perm).CriticalHit));
    }
}

void CommandUndo(Permainan *perm){
    if (IsStackEmpty(StackPerm(*perm))){
        printf("Tidak ada yang bisa di undo\n");
    }
    else{
        infoStack s;
        Pop(&StackPerm(*perm),&s);
        // mencetak elemen stack yang di delete untuk di debug
        // TulisBangunan(s.bangunan);
        // printf("\n%d %d\n",s.idBangunan,s.jenis);

        // mengganti elemen di daftar bangunan
        Elmt(DaftarBangunan(*perm),s.idBangunan) = s.bangunan;
        (*perm).CriticalHit = s.CH;
        if (s.jenis==-1){  // merupakan command ATTACK gagal atau MOVE
            Pop(&StackPerm(*perm),&s);
            // TulisBangunan(s.bangunan);
            // printf("\n%d %d\n",s.idBangunan,s.jenis);
            Elmt(DaftarBangunan(*perm),s.idBangunan) = s.bangunan;
        }
        else if(s.jenis!=0){   // merupakan command ATTACK berhasil
            int pemilikSekarang = Pemilik(InfoTop(StackPerm(*perm)).bangunan);
            DelP(&ListBangunanPlayer(*perm,pemilikSekarang),s.idBangunan); // dihapus dari list (bisa juga pakai dellast)

            if (Pemilik(s.bangunan)==(pemilikSekarang%2+1)){
                InsVatIdx(&ListBangunanPlayer(*perm,(pemilikSekarang%2+1)),s.idBangunan,s.jenis);
            }
            Pop(&StackPerm(*perm),&s);
            // TulisBangunan(s.bangunan);
            // printf("\n%d %d\n",s.idBangunan,s.jenis);
            Elmt(DaftarBangunan(*perm),s.idBangunan) = s.bangunan;
        }
        printf("Command terakhir telah di-undo\n");
    }
}

void CommandMove(Permainan *perm, int turn) {
    int idxPengirim, idxPenerima, BanyakBangunanPlayer, BanyakBangunanPlayerTerhubung, jumlahPasukanKiriman, n, n_atck;
    IdxType idPengirim, idPenerima;
    
    /* Mencetak daftar bangunan player */
    /* Satu bangunan cuman bisa move sekali -> buat mark, jadi kalo udah nyerang gak ditampilin lagi di sini */
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(ListBangunanPlayer(*perm,turn),DaftarBangunan(*perm),&n,&n_atck,&BanyakBangunanPlayer,'2'); 
    
    /* Input player bangunan mana yang digunakan untuk move */
    idxPengirim = InputPenggunaValidDalamRange (1, BanyakBangunanPlayer, "Pilih bangunan: ");
    idPengirim = GetIdBaseOnTurn(ListBangunanPlayer(*perm,turn),DaftarBangunan(*perm),idxPengirim,false);

    /* Mencetak daftar bangunan yang terhubung dengan bangunan player yang dipilih jika ada */
    printf("Daftar bangunan yang terdekat:");
    TulisDaftarBangunanPlayerTerhubung(*perm,idPengirim,&BanyakBangunanPlayerTerhubung,turn);
    printf("\n");

    if (BanyakBangunanPlayerTerhubung == 0) {
        printf("Tidak ada bangunan yang dapat menerima\n");
    } else {
        int i=1,count=0;
        /* Meminta input bangunan diserang */
        idxPenerima = InputPenggunaValidDalamRange (1, BanyakBangunanPlayerTerhubung, "Bangunan yang akan menerima: ");
        // Mengincrement idxPenerima agar bangunan yang tidak dimiliki player tidak ditampilkan ke opsi
        do {
            idPenerima = GetIdAdj(Graph(*perm),idPengirim,i);
            if (Pemilik(Elmt(DaftarBangunan(*perm),idPenerima)) == turn){
                count++;
            }
            i++;
        } while (count!=idxPenerima);
        
        /* Meminta input jumlah pasukan untuk menyerang */
        jumlahPasukanKiriman = InputPenggunaValidDalamRange (0, JumlahPasukan(Elmt(DaftarBangunan(*perm),idPengirim)),"Jumlah pasukan: ");
        /* Melakukan pembandingan jumlah pasukan bangunan penyerang dan diserang */
        Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idPengirim),idPengirim,-1,(*perm).CriticalHit));
        Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idPenerima),idPenerima,-1,(*perm).CriticalHit));
        JumlahPasukan(Elmt(DaftarBangunan(*perm),idPengirim)) -= jumlahPasukanKiriman;
        if (JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenerima)) + jumlahPasukanKiriman < MAX_PASUKAN) {
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenerima)) += jumlahPasukanKiriman;
        }
        // set boolean sudah move
        SudahMove(Elmt(DaftarBangunan(*perm),idPengirim)) = true;
        printf("%d pasukan dari ",jumlahPasukanKiriman);
        StringJenisBangunan(Elmt(DaftarBangunan(*perm),idPengirim));
        printf(" ");
        TulisPOINT (Posisi(Elmt(DaftarBangunan(*perm),idPengirim)));
        printf(" telah berpindah ke ");
        StringJenisBangunan(Elmt(DaftarBangunan(*perm),idPenerima));
        printf(" ");
        TulisPOINT (Posisi(Elmt(DaftarBangunan(*perm),idPenerima)));
    }
}

void CommandSkill(Permainan *perm, int turn){
    if (IsQueueEmpty(SkillPlayer(*perm,turn))){
        printf("Tidak ada skill yang tersedia\n");
        return;
    }

    CreateEmptyStack(&StackPerm(*perm));
    infoQueue x;
    Del(&SkillPlayer(*perm,turn),&x);
    switch(x){
        case 1: // Instant Upgrade
        InstantUpgrade(perm,turn);
        printf("Skill Instant Upgrade telah digunakan\n");
        break;

        case 2: // Shield
        PlayerPerm(*perm,turn).Shield = 2;
        break;

        case 3: // Extra Turn
        (*perm).ExtraTurn = true;
        printf("Skill Extra Turn telah digunakan\n");
        // Menambahkan skill Critical Hit ke lawan
        Add(&SkillPlayer(*perm,(turn%2)+1),5);
        break;

        case 4: // Attack Up
        (*perm).AttackUp = true;
        printf("Skill Attack Up telah digunakan\n");
        break;

        case 5: // Critical Hit
        (*perm).CriticalHit = true;
        printf("Skill Critical Hit telah digunakan\n");
        break;

        case 6: // Instant Reinforcement
        InstantReinforcement(perm,turn);
        printf("Skill Instant Reinforcement telah digunakan\n");
        break;

        case 7: // Barrage
        Barrage(perm,turn);
        printf("Skill Barrage telah digunakan\n");
        break;
    }
}

void CommandSave(Permainan perm, int turn){
    char namafile[NMaxStr];
    printf("Lokasi save file: ");
    scanf("%s",namafile);
    SimpanKonfigurasi(namafile,perm,turn);
    printf("Game berhasil di save!\n");
}

void CommandExit(Permainan perm, int turn){
    char pil;
    printf("Apakah Anda ingin menyimpan permainannya dahulu?\n");
    do{
        printf("1. Ya\n");
        printf("2. Tidak\n");
        printf("Masukkan pilihan: ");
        scanf(" %c",&pil);
    }while (pil!='1' && pil!='2');
    if (pil=='1'){
        CommandSave(perm,turn);
    }
    printf("\nSampai Jumpa\n");
}

/* PROSEDUR PENUNJANG GAME LAINNYA */
void TambahPasukanDiAwalGiliran(Permainan *perm, int turn) {
    int i, A, Id;
    address P;
    
    P = First(ListBangunanPlayer(*perm,turn));
    i = 1;
    while (P != Nil) {
        Id = GetIdFromList(ListBangunanPlayer(*perm,turn),i);
        A = GetNilaiPenambahanPasukan(Elmt(DaftarBangunan(*perm),Id));
        TambahJumlahPasukan(&Elmt(DaftarBangunan(*perm),Id),A);
        
        i++;
        P = Next(P);
    }
}

/* Fungsi/Prosedur Bantuan */
boolean IsInRange(int x,int l,int r) {
    return ((l<=x) && (x<=r));
}

int InputPenggunaValidDalamRange (int l, int r, char *Pesan) {
    int input;
    do {
        printf("%s",Pesan);
        scanf("%d",&input);
        /* Masukan harus valid */ 
        if (!IsInRange(input,l,r)) {
            printf("Masukkan tidak valid\n");
        }
    } while (!IsInRange(input,l,r));
    return input;
}

int GetIdBaseOnTurn (List L, TabBANGUNAN tabel, int idx, boolean attck) {
    address P=Nil;
    int i = 0;
    while (i<idx){
        if (P==Nil){
            P = First(L);
        }
        else{
            P = Next(P);
        }
        if (((attck) && (!SudahAttack(Elmt(tabel,Info(P))))) || ((!attck) && (!SudahMove(Elmt(tabel,Info(P)))))){
            ++i;
        }
    }
    return Info(P);
}

void AkuisisiBangunan(Permainan *perm, int id, int turn) {
    int musuh = turn%2+1;
    
    if (Pemilik(Elmt(DaftarBangunan(*perm),id)) == musuh) {
        DelP(&ListBangunanPlayer(*perm,musuh),id);
    } 
    Pemilik(Elmt(DaftarBangunan(*perm),id)) = turn;
    Level(Elmt(DaftarBangunan(*perm),id)) = 1;
    // Dipastikan id tidak akan ada di dalam list si penyerang (Lewat increment idxDiSerang)
    InsVLast(&ListBangunanPlayer(*perm,turn),id);
}
