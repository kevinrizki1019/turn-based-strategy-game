#include "queueofskill.h"
#include <stdio.h>
#include <stdlib.h>

boolean IsQueueEmpty (Queue Q){
    return(Head(Q)==0 && Tail(Q)==0);
}
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsQueueFull (Queue Q){
    int m = Head(Q) - Tail(Q);
    return(m==1) || (m == (-1*MaxElQueue(Q)+1)); 
}
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxElQueue */

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max){
    (*Q).T = (infotype *) malloc ((Max+1)*sizeof(infotype));
    if ((*Q).T != NULL) {
	    MaxElQueue(*Q) = Max;
	    Head(*Q) = 0;
	    Tail(*Q) = 0;
	} else{
	    MaxElQueue(*Q) = 0;
	}
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxElQueue=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(Queue * Q){
    MaxElQueue(*Q) = 0;
	free((*Q).T);
}
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElQueue(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X){
    if (IsQueueEmpty(*Q)){	
		Tail(*Q) = 1;
		Head(*Q) = 1;
	} else{		
		Tail(*Q) += 1;
		if (Tail(*Q) == (*Q).MaxElQueue + 1) Tail(*Q) = 1;
	}
	InfoTail(*Q) = X;
}
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void Del (Queue * Q, infotype * X){
    (*X) = InfoHead(*Q);
	if (Head(*Q) == Tail(*Q)){
		Head(*Q) = 0;
		Tail(*Q) = 0;
	} else {	
		Head(*Q)++;
		if (Head(*Q) == MaxElQueue(*Q) + 1) Head(*Q) = 1;
	}
}
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */