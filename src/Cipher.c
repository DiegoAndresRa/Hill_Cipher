#include "Cipher.h"
#include "Utilities.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int** matrixKey(char* key_stream){
    // make matrix
    int **key = (int **)malloc(2 * sizeof(int*));
    for (int i = 0; i < 2; i++){
        key[i] = (int *)malloc(2 * sizeof(int));
    }
    // fill matrix
    int index = 0;
    for(int i = 0; i<2 ; i++){
        for(int j=0; j<2 ; j++){
            key[i][j] = numReassignment(toupper(key_stream[index]),1);
            index++;
        }
    }
    return key;
}


int** matrixMessage(char* plain_text){
    // discover number of matrix's
    int num_matrix = numMatrix((double)strlen(plain_text),2);
    // make matrix array
    int** message = (int**)malloc(num_matrix*sizeof(int*));
    for(int i=0; i<num_matrix; i++){
        message[i] = (int*)malloc(2*sizeof(int));
    }
    // fill matrix's
    int index = 0;
    for(int i=0; i<num_matrix; i++){
        for(int j=0; j<2; j++){
            if(index != strlen(plain_text)){
                message[i][j] = numReassignment(toupper(plain_text[index]),1);
                index++;
            }else{
                message[i][j] = numReassignment('X',1);
            }
        }
    }
    return message;
}


void encrypt(int** key_matrix, int** plain_text_matrix, char* plain_text){
    // discover number of matrix's
    int num_matrix = numMatrix((double)strlen(plain_text),2);
    // multiply
    int index_matrixs = 0;
    multiply(key_matrix,plain_text_matrix,index_matrixs,2,num_matrix);
    // print chiper text
    for(int i=0; i<num_matrix; i++){
        for(int j=0; j<2; j++)// to print the letter corresponding to the value
            printf("%c",numReassignment(plain_text_matrix[i][j],0));
    }
    printf("\n");
}


void decrypt(int** key_matrix, int** cipher_text_matrix, char* cipher_text){
    // determinante
    int det = inverseDeterminant(key_matrix);
    // adjunta
    ungetc(key_matrix[0][0],stdin);
    key_matrix[0][0] = modN(det * key_matrix[1][1]);
    key_matrix[1][1] = modN(det * getchar());
    ungetc(key_matrix[0][1],stdin);
    key_matrix[0][1] = modN(det * -key_matrix[1][0]);
    key_matrix[1][0] = modN(det * -(getchar()));
    // transpuesta
    ungetc(key_matrix[0][1],stdin);
    key_matrix[0][1] = key_matrix[1][0]; 
    key_matrix[1][0] = getchar();
    // discover number of matrix's
    int num_matrix = numMatrix((double)strlen(cipher_text),2);
    // multiply
    int index_matrixs = 0;
    multiply(key_matrix,cipher_text_matrix,index_matrixs,2,num_matrix);
    // print chiper text
    for(int i=0; i<num_matrix; i++){
        for(int j=0; j<2; j++)// to print the letter corresponding to the value
            printf("%c",numReassignment(cipher_text_matrix[i][j],0));
    }
    printf("\n");
}


int inverseDeterminant (int** key){
    int det = key[0][0]*key[1][1] - key[0][1]*key[1][0];
    if(det == 0)
        exit(EXIT_FAILURE);
    int inv_det = InverseOfN(modN(det));
    return inv_det;
}

int InverseOfN(int det) {
    for (int i=1; i<26; i++) {
        if((det*i) % 26 == 1) {
            return i;
        }
    }
    exit(EXIT_FAILURE);
}