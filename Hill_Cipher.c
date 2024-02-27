/*
    2X2 KEY MATRIX HILL ENCRYPTION

    ————————————————————————————————————————
    Input: mode{C,D}, message{nxn}, key{2x2}
    ————————————————————————————————————————
    Output: text cipher or plain text
    ————————————————————————————————————————

    Author: Ramirez Garcia Diego Andres
*/
#include "Utilities.h"
#include "Cipher.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int main(int argc, char* argv[]){
    char mode;
    char* key = (char*)malloc(100*sizeof(char));
    char* message = (char*)malloc(100*sizeof(char));

    // read mode
    scanf("%c",&mode);
    getchar();
    if(mode != toupper('c') && mode != toupper('d'))
        exit(EXIT_FAILURE);
    //read plain text
    scanf("%[^\n]s",message);
    getchar();
    // read key
    scanf("%[^\n]s",key);
    getchar();


    // string -> matrix
    int** key_matrix = matrixKey(key);
    int** message_matrix = matrixMessage(message);
    
    
    // encrypt or decrypt
    if(mode != toupper('D')){
        encrypt(key_matrix,message_matrix,message);
    }else{
        decrypt(key_matrix,message_matrix,message);
    }
    free(key);
    free(message);
    exit(EXIT_SUCCESS);
}