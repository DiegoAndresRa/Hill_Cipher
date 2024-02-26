#include "Utilities.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<unistd.h>

int modN (int num){
    if(num < 0){ num=26-(-num%26); } // mod does not work with negative numbers in C
    else{ num %= 26; }
    return num;
}
// Ascci numeration -> numeration [0-25]
int numReassignment(int ascciNum){
    return (-65 + ascciNum);
}

int dimMatrix(double dimension){
    dimension = sqrt(dimension);
    if(dimension != (int)dimension){
        printf("ERROR: unacceptable key\n");
        exit(EXIT_FAILURE);
    }
    return (int)dimension;
}

int** matrixKey(char* key_stream){
    // discover dimension
    int dim = dimMatrix((double)strlen(key_stream));   
    // make matrix
    int **key = (int **)malloc(dim * sizeof(int*));
    for (int i = 0; i < dim; i++){
        key[i] = (int *)malloc(dim * sizeof(int));
    }
    // fill matrix
    int index = 0;
    for(int i = 0; i<dim ; i++){
        for(int j=0; j<dim ; j++){
            key[i][j] = numReassignment(toupper(key_stream[index]));
            index++;
        }
    }
    return key;
}

int numMatrix(double len_plain_text, int dim_key){
    len_plain_text = len_plain_text/dim_key;
    if(len_plain_text != (int)len_plain_text){
        return (int)len_plain_text+1;
    }
    return (int)len_plain_text;
}

int** matrixMessage(char* plain_text,char* key){
    // discover dimension
    int dim_key = dimMatrix((double)strlen(key));
    // discover number of matrix's
    int num_matrix = numMatrix((double)strlen(plain_text),dim_key);
    // make matrix array
    int** message = (int**)malloc(num_matrix*sizeof(int*));
    for(int i=0; i<num_matrix; i++){
        message[i] = (int*)malloc(dim_key*sizeof(int));
    }
    // fill matrix's
    int index = 0;
    for(int i=0; i<num_matrix; i++){
        for(int j=0; j<dim_key; j++){
            if(index != strlen(plain_text)){
                message[i][j] = numReassignment(toupper(plain_text[index]));
                index++;
            }else{
                message[i][j] = numReassignment('X');
            }
        }
    }
    return message;
}