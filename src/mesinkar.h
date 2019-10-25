/* File: mesinkar.h */
/* Definisi Mesin Karakter */

#ifndef __MESIN_KAR_H_
#define __MESIN_KAR_H_

#include "boolean.h"

/* State Mesin */
extern char CC;
extern boolean EndPita;

void START(char NamaFile[]);
/* Mesin siap dioperasikan. Pita dengan nama file 'NamaFile' disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : 'NamaFile' terdefinisi dan ada filenya
   F.S. : Membuka file 'NamaFile'. CC adalah karakter pertama pada pita. 
          Apabila pita langsung sampai terakhir, maka EndPita=true; selainnya
          EndPita=false */

void ADV();
/* Pita dimajukan satu karakter.
   I.S. : Karakter pada jendela = CC
   F.S. : CC adalah karakter berikutnya dari CC yang lama Apabila pita telah sampai 
          akhir, EndPita=true */

void FINISH();
/* Menutup pita dengan nama file 'NamaFile'
   I.S. : Pita 'NamaFile' telah dibuka
   F.S. : Pita 'NamaFile' ditutup */

#endif
