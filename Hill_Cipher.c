#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Utilities.h"
int main(int argc, char* argv[]){
    char mode;
    char* key = (char*)malloc(100*sizeof(char));
    char* plain_text = (char*)malloc(100*sizeof(char));

    scanf("%c",&mode);
    fpurge(stdin);

    scanf("%[^\n]s",plain_text);
    fpurge(stdin);

    scanf("%[^\n]s",key);
    fpurge(stdin);

    int** key_matrix = matrixKey(key);
    int** plain_text_matrix = matrixMessage(plain_text,key);
    
    int dim_key = dimMatrix((double)strlen(key));
    // discover number of matrix's
    int num_matrix = numMatrix((double)strlen(plain_text),dim_key);
    for(int i=0; i<num_matrix; i++){
        for(int j=0; j<dim_key; j++){
            printf("%d |",plain_text_matrix[i][j]);
        }
        printf("\n");
    }
    cipher(key_matrix,key,plain_text_matrix,plain_text);

    free(key);
    free(plain_text);

}