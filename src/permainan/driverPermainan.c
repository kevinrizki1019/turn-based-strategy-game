#include "permainan.h"
#include <stdio.h>

int main() {
    Permainan P;
    int turn;
    BacaKonfigurasi("../../config_map.txt", &P,false,&turn);
    printf("Panjang peta : %d\n", PanjangPeta(P));
    printf("Lebar peta :%d\n", LebarPeta(P));
    printf("Jumlah bangunan: %d\n", JumlahBangunan(P));
    TulisIsiTab(DaftarBangunan(P));
}