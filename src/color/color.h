/* Nama file: color.h */
/* Copyright: Kelompok 11 K-1 IF2110 2019/2020 */

#ifndef  __printcolor__
#define __printcolor__

#include <stdio.h>

#define GREEN "\x1B[32m"

void red();
// Fungsi untuk mengubah output print ke merah
void blue();
// Fungsi untuk mengubah output print ke biru

void yellow();

void green();

void cyan();

void white();

void brightwhite();

void bgred();

void bgblue();

void bgwhite();

void bgyellow();

void bggreen();

void reset();
// Reset Warna

#endif