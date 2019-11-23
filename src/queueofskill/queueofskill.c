/* Nama file: queueofskill.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "queueofskill.h"

boolean IsQueueEmpty (Queue Q){
    return(Head(Q)==0 && Tail(Q)==0);
}

boolean IsQueueFull (Queue Q){
    return ( ((Tail(Q)%MaxElQueue(Q))+1) == Head(Q));
}
int NBElmtQueue (Queue Q){
    if (IsQueueEmpty(Q)) return 0;
    if (Head(Q)<=Tail(Q)){
        return (Tail(Q)-Head(Q)+1);
    }
    else{
        return (MaxElQueue(Q)-(Head(Q)-Tail(Q)-1));
    }
}

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max){
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */    
	(*Q).T = (infoQueue *) malloc ((Max+1)*sizeof(infoQueue));
    if ((*Q).T != NULL) {
	    MaxElQueue(*Q) = Max;
	    Head(*Q) = 0;
	    Tail(*Q) = 0;
	} else{
	    MaxElQueue(*Q) = 0;
	}
}


/* *** Destruktor *** */
void DeAlokasi(Queue * Q){
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQueue(Q) diset 0 */    
	MaxElQueue(*Q) = 0;
	free((*Q).T);
}


/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infoQueue X){
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
    if (IsQueueEmpty(*Q)){	
		Tail(*Q) = 1;
		Head(*Q) = 1;
	} else{		
		Tail(*Q) += 1;
		if (Tail(*Q) == MaxElQueue(*Q) + 1) Tail(*Q) = 1;
	}
	InfoTail(*Q) = X;
}

void Del (Queue * Q, infoQueue * X){
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
    (*X) = InfoHead(*Q);
	if (Head(*Q) == Tail(*Q)){
		Head(*Q) = 0;
		Tail(*Q) = 0;
	} else {	
		Head(*Q)++;
		if (Head(*Q) == MaxElQueue(*Q) + 1) Head(*Q) = 1;
	}
}
