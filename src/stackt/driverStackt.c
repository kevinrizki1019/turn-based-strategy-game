#include "stackt.h"
#include <stdio.h>

int main(){
    // compile command: gcc -o a driverStackt.c stackt.c ../bangunan/bangunan.c ../color/color.c ../point/point.c
    BANGUNAN b;
    Stack s;
    CreateEmptyStack(&s);
    printf("Stack kosong: %d\n",IsStackEmpty(s));
    for (int i=0; i<6; ++i){
        b = MakeBANGUNAN('C',MakePOINT(i,5-i),0);
        Push(&s,MakeInfoStack(b,i,i%2));
    }
    while (!IsStackEmpty(s))
    {
        infoStack x;
        Pop(&s,&x);
        TulisBangunan(x.bangunan);
        printf(" %d %d\n",x.idBangunan,x.jenis);
    }
    
    return 0;
}