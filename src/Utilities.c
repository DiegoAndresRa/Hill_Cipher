#include "Utilities.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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

int isDoubleOrInteger(double digit){
    if(digit != (int)digit)
        return 0;
    return 1;
}

int dimMatrix(double dimension){
    dimension = sqrt(dimension);
    if (isDoubleOrInteger(dimension) == 0)
        exit(EXIT_FAILURE);
    return (int)dimension;
}

int numMatrix(double len_plain_text, int dim_key){
    len_plain_text = len_plain_text/dim_key;
    if(len_plain_text != (int)len_plain_text){
        return (int)len_plain_text+1;
    }
    return (int)len_plain_text;
}

void multiply(int** key, int** plain_text,int matrix,int dim_key,int num_matrix){
    int result;
    int* compy_n_matrix = (int*)malloc(dim_key*sizeof(int));
    // copy the vector to save the multiplication in the same vector
    for(int j=0; j<dim_key; j++)
        compy_n_matrix[j]  = plain_text[matrix][j];
    // multiply
    for(int i=0; i<dim_key; i++){
        plain_text[matrix][i] = 0; 
        for(int j=0; j<dim_key; j++){
            plain_text[matrix][i] += (key[j][i]*compy_n_matrix[j]);
        }
        plain_text[matrix][i] = modN(plain_text[matrix][i]);
    }
    matrix++;
    free(compy_n_matrix);
    if(matrix < num_matrix)
        multiply(key,plain_text,matrix,dim_key,num_matrix);
}