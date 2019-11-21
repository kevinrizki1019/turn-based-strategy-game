/* Nama file: command.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */
/* Mengolah command (input) dari user */

#include "command.h"
#include "skill.h"
#include <stdio.h>

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
    printf("- ATTACK\n");
    printf("- LEVEL_UP\n");
    printf("- SKILL\n");
    printf("- UNDO\n");
    printf("- END_TURN\n");
    printf("- SAVE\n");
    printf("- MOVE\n");
    printf("- EXIT\n");
}
    
/* IMPLEMENTASI PROSEDUR-PROSEDUR COMMAND */
void CommandAttack(Permainan *perm, int turn, List *ListBangunanPlayerAvailableToAttack,  List *ListBangunanPlayerAvailableToMove, int *NbBangunanAttackOff) {
    IdxType idPenyerang,idDiSerang;
    int idxPenyerang,idxDiSerang,BanyakBangunanPenyerang,BanyakBangunanDapatDiSerang, jumlahPasukanPenyerang, jumlahPasukanDiSerang,jumlahPasukanPenyerangEfektif;
    BANGUNAN *bangunanPenyerang, *bangunanDiSerang;

    /* Mencetak daftar bangunan player */
    /* Satu bangunan cuman bisa nyerang sekali -> buat mark, jadi kalo udah nyerang gak ditampilin lagi di sini */
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(*ListBangunanPlayerAvailableToAttack,DaftarBangunan(*perm),&BanyakBangunanPenyerang); 

    /* Input player bangunan mana yang digunakan untuk menyerang */
    /* Input pengguna bangunan mana yang ingin digunakan untuk menyerang */
    idxPenyerang = InputPenggunaValidDalamRange (1, BanyakBangunanPenyerang, "Bangunan yang akan digunakan untuk menyerang: ");
    idxPenyerang += (*NbBangunanAttackOff);
    idPenyerang = GetIdBaseOnTurn(perm,idxPenyerang,turn);

    /* Mencetak daftar bangunan yang terhubung dengan bangunan player yang dipilih jika ada */
    printf("Daftar bangunan yang dapat diserang: \n");
    TulisDaftarBangunanMusuhTerhubung(*perm,idPenyerang,&BanyakBangunanDapatDiSerang,turn);
    printf("\n");
    
    if (BanyakBangunanDapatDiSerang == 0) {
        printf("Tidak ada bangunan yang dapat diserang\n");
    } else {
        int i=1,count=0;
        /* Meminta input bangunan diserang */
        idxDiSerang = InputPenggunaValidDalamRange (1, BanyakBangunanDapatDiSerang, "Bangunan yang diserang: ");
        // Mengincrement idxDiSerang agar bangunan yang sudah dimiliki si penyerang tidak ditampilkan ke opsi
        do {
            idDiSerang = GetIdAdj(Graph(*perm),idPenyerang,i);
            if (Pemilik(Elmt(DaftarBangunan(*perm),idDiSerang)) == turn){      
            } else {
                count++;
            }
            i++;
        } while (count!=idxDiSerang);
        
        /* Meminta input jumlah pasukan untuk menyerang */
        jumlahPasukanPenyerang = InputPenggunaValidDalamRange (0, JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenyerang)),"Jumlah pasukan: ");
        jumlahPasukanDiSerang = JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang));
        /* Cek pertahanan, Pertahanan(B) */
        if (Pertahanan(Elmt(DaftarBangunan(*perm),idDiSerang))) {
            jumlahPasukanPenyerangEfektif = jumlahPasukanPenyerang * 3 / 4;
        } else {
            jumlahPasukanPenyerangEfektif = jumlahPasukanPenyerang;
        }
        /* MELAKUKAN SERANGAN */
        /* Melakukan pembandingan jumlah pasukan bangunan penyerang dan diserang */
        if (jumlahPasukanPenyerangEfektif < jumlahPasukanDiSerang) {
            printf("Bangunan gagal direbut. \n");
            Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idPenyerang),idPenyerang,'2'));
            Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idDiSerang),idDiSerang,'2'));
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenyerang)) -= jumlahPasukanPenyerang;
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang)) -= jumlahPasukanPenyerangEfektif;
        } else {
            printf("Bangunan menjadi milikmu! \n");
            Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idPenyerang),idPenyerang,'1'));
            Push(&StackPerm(*perm),MakeInfoStack(Elmt(DaftarBangunan(*perm),idDiSerang),idDiSerang,'1'));
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenyerang)) -= jumlahPasukanPenyerang;
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang)) = jumlahPasukanPenyerangEfektif - JumlahPasukan(Elmt(DaftarBangunan(*perm),idDiSerang));
            AkuisisiBangunan(perm, idDiSerang, turn);
            InsVLast(ListBangunanPlayerAvailableToAttack,idDiSerang);
            InsVLast(ListBangunanPlayerAvailableToMove,idDiSerang);
            if (JenisBangunan(Elmt(DaftarBangunan(*perm),idDiSerang))=='F'){
                Add(&SkillPlayer(*perm,(turn%2+1)),3);
            }
        }
        DelP(ListBangunanPlayerAvailableToAttack,idPenyerang);
        (*NbBangunanAttackOff)++;
        /* Cek skill AttackUp dan CriticalHit */
    }
}
void CommandLevelUp(Permainan *perm,int turn) {  
    IdxType idx;
    int IdBangunan,BanyakBangunan;
    boolean success;
    BANGUNAN B_lama;

    /* Mencetak daftar bangunan player*/ 
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(ListBangunanPlayer(*perm,turn),DaftarBangunan(*perm),&BanyakBangunan);
    
    /* Input pengguna bangunan mana yang ingin di level up */
    idx = InputPenggunaValidDalamRange(1,BanyakBangunan,"Bangunan yang akan di level up : ");

    /* Mendapatkan IdBangunan mana yang akan di level up */
    IdBangunan = GetIdBaseOnTurn(perm,idx,turn);

    /* Menambah level, evaluasi kevalidan penambahan pasukan ada di dalam prosedur  */
    TambahSatuLevel(&Elmt(DaftarBangunan(*perm),IdBangunan),&success,&B_lama);
    
    if (success){
        Push(&StackPerm(*perm),MakeInfoStack(B_lama,IdBangunan,'0'));
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
        TulisBangunan(s.bangunan);
        printf("\n%d %c\n",s.idBangunan,s.jenis);

        // mengganti elemen di daftar bangunan
        Elmt(DaftarBangunan(*perm),s.idBangunan) = s.bangunan;
        if(s.jenis=='1'){   // merupakan command ATTACK berhasil
            int pemilikSekarang = Pemilik(InfoTop(StackPerm(*perm)).bangunan);
            DelP(&ListBangunanPlayer(*perm,pemilikSekarang),s.idBangunan); // dihapus dari list (bisa juga pakai dellast)

            if (Pemilik(s.bangunan)==(pemilikSekarang%2+1)){
                InsVLast(&ListBangunanPlayer(*perm,(pemilikSekarang%2+1)),s.idBangunan);
            }
            Pop(&StackPerm(*perm),&s);
            TulisBangunan(s.bangunan);
            printf("\n%d %c\n",s.idBangunan,s.jenis);
            Elmt(DaftarBangunan(*perm),s.idBangunan) = s.bangunan;
        }
        if (s.jenis=='2'){  // merupakan command ATTACK gagal atau MOVE
            Pop(&StackPerm(*perm),&s);
            TulisBangunan(s.bangunan);
            printf("\n%d %c\n",s.idBangunan,s.jenis);
            Elmt(DaftarBangunan(*perm),s.idBangunan) = s.bangunan;
        }
    }
}

void CommandMove(Permainan *perm, int turn,List *ListBangunanPlayerAvailableToMove, int *NbBangunanMoveOff) {
    int idxPengirim, idxPenerima, BanyakBangunanPlayer, BanyakBangunanPlayerTerhubung, jumlahPasukanKiriman;
    IdxType idPengirim, idPenerima;
    
    /* Mencetak daftar bangunan player */
    /* Satu bangunan cuman bisa move sekali -> buat mark, jadi kalo udah nyerang gak ditampilin lagi di sini */
    printf("Daftar bangunan:\n");
    TulisDaftarBangunan(*ListBangunanPlayerAvailableToMove,DaftarBangunan(*perm),&BanyakBangunanPlayer); 
    
    /* Input player bangunan mana yang digunakan untuk move */
    idxPengirim = InputPenggunaValidDalamRange (1, BanyakBangunanPlayer, "Pilih bangunan: ");
    idxPengirim+= (*NbBangunanMoveOff);
    idPengirim = GetIdBaseOnTurn(perm,idxPengirim,turn);

    /* Mencetak daftar bangunan yang terhubung dengan bangunan player yang dipilih jika ada */
    printf("Daftar bangunan yang terdekat: \n");
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
            if (Pemilik(Elmt(DaftarBangunan(*perm),idPenerima)) != turn){      
            } else {
                count++;
            }
            i++;
        } while (count!=idxPenerima);
        
        /* Meminta input jumlah pasukan untuk menyerang */
        jumlahPasukanKiriman = InputPenggunaValidDalamRange (0, JumlahPasukan(Elmt(DaftarBangunan(*perm),idPengirim)),"Jumlah pasukan: ");
        /* Melakukan pembandingan jumlah pasukan bangunan penyerang dan diserang */
        JumlahPasukan(Elmt(DaftarBangunan(*perm),idPengirim)) -= jumlahPasukanKiriman;
        if (JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenerima)) + jumlahPasukanKiriman < MAX_PASUKAN) {
            JumlahPasukan(Elmt(DaftarBangunan(*perm),idPenerima)) += jumlahPasukanKiriman;
        }
        printf("%d pasukan dari ",jumlahPasukanKiriman);
        StringJenisBangunan(Elmt(DaftarBangunan(*perm),idPengirim));
        printf(" ");
        TulisPOINT (Posisi(Elmt(DaftarBangunan(*perm),idPengirim)));
        printf("telah berpindah ke ");
        StringJenisBangunan(Elmt(DaftarBangunan(*perm),idPenerima));
        printf(" ");
        TulisPOINT (Posisi(Elmt(DaftarBangunan(*perm),idPenerima)));
        
        DelP(ListBangunanPlayerAvailableToMove,idPengirim);
        (*NbBangunanMoveOff)++;
    }
}

void CommandSkill(Permainan *perm, int turn){
    if (IsQueueEmpty(SkillPlayer(*perm,turn))){
        printf("You don\'t have any skill\n");
        return;
    }

    infoQueue x;
    Del(&SkillPlayer(*perm,turn),&x);
    switch(x){
        case 1: // Instant Upgrade
        // InstantUpgrade(perm,turn);
        break;

        case 2: // Shield
        
        break;

        case 3: // Extra Turn
        (*perm).ExtraTurn = true;
        break;

        case 4: // Attack Up
        
        break;

        case 5: // Critical Hit

        break;

        case 6: // Instant Reinforcement
        // InstantReinforcement(perm,turn);
        break;

        case 7: // Barrage
        // Barrage(perm,turn);
        break;
    }
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

int GetIdBaseOnTurn (Permainan *perm,int index, int turn) {
    return GetIdFromList(ListBangunanPlayer(*perm,turn),index);
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
