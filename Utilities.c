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
int numReassignment(int ascciNum,int mode){
    if(mode == 1){return (-65 + ascciNum);}
    else{return(65+ascciNum);}
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
            key[i][j] = numReassignment(toupper(key_stream[index]),1);
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
                message[i][j] = numReassignment(toupper(plain_text[index]),1);
                index++;
            }else{
                message[i][j] = numReassignment('X',1);
            }
        }
    }
    return message;
}
void cipher(int** key_matrix,char* key, int** plain_text_matrix, char* plain_text){
    // discover dimension
    int dim_key = dimMatrix((double)strlen(key)); 
    // discover number of matrix's
    int num_matrix = numMatrix((double)strlen(plain_text),dim_key);
    // multiplie
    int index_matrixs = 0;
    multiply(key_matrix,plain_text_matrix,index_matrixs,dim_key,num_matrix);

    for(int i=0; i<num_matrix; i++){
        for(int j=0; j<dim_key; j++){
            printf("%c ",plain_text_matrix[i][j]);
        }
    }
}

void multiply(int** key, int** plain_text,int matrix,int dim_key,int num_matrix){
    int result;
    int* compy_n_matrix = (int*)malloc(dim_key*sizeof(int));
    // copy the vector to save the multiplication in the same vector
    for(int j=0; j<dim_key; j++)
        compy_n_matrix[j]  = plain_text[matrix][j];
    // multiply
    for(int i=0; i<dim_key; i++){
        result = 0; 
        for(int j=0; j<dim_key; j++)
            result += key[j][i]*compy_n_matrix[j];
        plain_text[matrix][i] = numReassignment(modN(result),0);
    }

    matrix++;
    free(compy_n_matrix);
    if(matrix < num_matrix)
        multiply(key,plain_text,matrix,dim_key,num_matrix);
}