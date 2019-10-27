#include "permainan.h"

int main() {
    Permainan P;
    BacaKonfigurasi("../config_map.txt", &P);
    printf("Panjang peta : %d\n", PanjangPeta(P));
    printf("Lebar peta :%d\n", LebarPeta(P));
    printf("Jumlah bangunan: %d\n", JumlahBangunan(P));
    TulisIsiTab(DaftarBangunan(P));
}