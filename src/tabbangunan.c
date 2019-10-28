/* Nama file: tabbangunan.c */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#include "tabbangunan.h"
#include <stdio.h>

BANGUNAN ValTabUndef() {
    BANGUNAN B;
    JenisBangunan(B) = 'X';
    return B;
}

void MakeEmpty (TabBANGUNAN * T){
    int i;
    for (i=1; i<=IdxMax; i++) {
        Elmt(*T,i) = ValTabUndef();
    }
}

int NbElmt(TabBANGUNAN T){
	int i,count;
	count = 0;
	for(i = IdxMin;i<=MaxEl(T);i++){
		if(Elmt(T,i) != ValUndef){
			count++;
		}
	}
	if (count ==0){
		return 0;
	}
	return count;
}

IdxType GetFirstIdx(TabBANGUNAN T){
	int i=1; 
	while (i<=29){
		if (Elmt(T,i)!=Undef){
			break;
		}
		i++;
	}
	return i;
}

IdxType GetLastIdx(TabBANGUNAN T){
	int i=1,checker=0;
	while (i<=29){
		if (Elmt(T,i)!=Undef){
			checker++;
			if (checker==NbElmt){
				return i;
			}
		}i++;
	}
}

boolean IsIdxValid(TabBANGUNAN T, IdxType i){
	return(i>= IdxMin && i<= IdxMax);
}

boolean IsIdxEff(TabBANGUNAN T, IdxType i){
	return(i>= IdxMin && i<= NbElmt(T));
}

boolean IsEmpty(TabBANGUNAN T){
	int i,count;
	count = 0;
	for(i = GetFirstIdx(T);i<=NbElmt(T);i++){
		if(Elmt(T,i) != ValUndef){
			count++;
		}
	}
	if (count == 0){
		return true;
	}
	else{
		return false;
	}
}

boolean IsFull(TabBANGUNAN T){
	int i,count;
	count = 0;
	for(i = GetFirstIdx(T);i<=NbElmt(T);i++){
		if(Elmt(T,i) != ValUndef){
			count++;
		}
	}
	if (count == GetLastIdx(T)){
		return true;
	}
	else{
		return false;
	}
}

void BacaIsi(TabBANGUNAN *T){
	int N,i;
	scanf("%d",&N);
	while ((N<0) || (N>GetLastIdx(*T)){
		scanf("%d",&N);
	}
	if (N == 0){
		MakeEmpty(&T, 0);
	}
	else{
		for(i=GetFirstIdx(*T); i<=N;i++){
			scanf("%d", &Elmt(*T,i));
		}
	}
}

void CopyTab (TabBANGUNAN Tin, TabBANGUNAN * Tout){
	int i;
	MakeEmpty(*Tout);
	for (i =GetFirstIdx(Tin); i<=GetLastIdx(Tin);i++){
		Elmt(*Tout,i) = Elmt(Tin,i);
	}
}

void TulisIsiTab(TabBANGUNAN T) {
    int i;
    i = IdxMin;
    while (JenisBangunan(Elmt(T, i)) != 'X' && i <= IdxMax) {
        TulisBangunan(Elmt(T, i));
        printf("\n");
        i++;
    }
}
