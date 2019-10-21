#include <stdio.h>
#include "color.h"

void red(){
    printf("\033[1;31m");
}

void blue(){
    printf("\033[1;34m");
}

void reset(){
    printf("\033[0m");
}