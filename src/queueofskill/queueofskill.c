/* Nama file: queueofskill.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "queueofskill.h"

boolean IsQueueEmpty (Queue Q){
	/* KAMUS LOKAL */
	/* ALGORITMA */
    return(Head(Q)==0 && Tail(Q)==0);
}

boolean IsQueueFull (Queue Q){
	/* KAMUS LOKAL */
	/* ALGORITMA */
    return ( ((Tail(Q)%MaxElQueue(Q))+1) == Head(Q));
}
int NBElmtQueue (Queue Q){
    /* KAMUS LOKAL */
	/* ALGORITMA */
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
	/* KAMUS LOKAL */
	/* ALGORITMA */
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
	/* KAMUS LOKAL */
	/* ALGORITMA */
	MaxElQueue(*Q) = 0;
	free((*Q).T);
}


/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infoQueue X){
	/* KAMUS LOKAL */
	/* ALGORITMA */
    if (IsQueueFull(*Q)) return;
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
	/* KAMUS LOKAL */
	/* ALGORITMA */
    (*X) = InfoHead(*Q);
	if (Head(*Q) == Tail(*Q)){
		Head(*Q) = 0;
		Tail(*Q) = 0;
	} else {	
		Head(*Q)++;
		if (Head(*Q) == MaxElQueue(*Q) + 1) Head(*Q) = 1;
	}
}
