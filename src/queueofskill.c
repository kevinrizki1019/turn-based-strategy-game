#include "queueofskill.h"
#include <stdio.h>

boolean IsEmpty (Queue Q){
    return(Head(Q)==Nil && Tail(Q)==Nil);
}
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFull (Queue Q){
    int m = Head(Q) - Tail(Q);
    return(m==1) || (m == (-1*MaxEl(Q)+1)); 
}
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max){
    (*Q).T = (infotype *) malloc ((Max+1)*sizeof(infotype));
    if ((*Q).T != NULL) {
	    MaxEl(*Q) = Max;
	    Head(*Q) = Nil;
	    Tail(*Q) = Nil;
	} else{
	    MaxEl(*Q) = Nil;
	}
}
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasi(Queue * Q){
    MaxEl(*Q) = Nil;
	free((*Q).T);
}
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X){
    if (IsEmpty(*Q)){	
		Tail(*Q) = 1;
		Head(*Q) = 1;
	} else{		
		Tail(*Q) += 1;
		if (Tail(*Q) == (*Q).MaxEl + 1) Tail(*Q) = 1;
	}
	InfoTail(*Q) = X;
}
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void Del (Queue * Q, infotype * X){
    (*X) = InfoHead(*Q);
	if (Head(*Q) == Tail(*Q)){
		Head(*Q) = Nil;
		Tail(*Q) = Nil;
	} else {	
		Head(*Q)++;
		if (Head(*Q) == MaxEl(*Q) + 1) Head(*Q) = 1;
	}
}
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */