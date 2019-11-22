#include <stdio.h>
#include "color.h"

void red(){
    printf("\033[1;31m");
}

void blue(){
    printf("\033[1;34m");
}

void yellow(){
    printf("\033[1;33m");
}

void green(){
    printf("\033[1;32m");
}

void cyan(){
    printf("\033[1;36m");
}

void white(){
    printf("\033[1;37m");
}

void brightwhite() {
    printf("\033[1;97m");
}

void bgred(){
    printf("\033[1;41m");
}

void bgblue(){
    printf("\033[1;44m");
}

void bgwhite(){
    printf("\033[1;47m");
}

void bgyellow(){
    printf("\033[1;100m");
}

void bggreen(){
    printf("\033[1;102m");
}

void reset(){
    printf("\033[0m");
}