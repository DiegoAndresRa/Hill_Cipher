#include "Utilities.h"
#include <stdio.h>
int ModN (int num){
    if(num < 0){ num=26-(-num%26); } // mod does not work with negative numbers in C
    else{ num %= 26; }
    return num;
}