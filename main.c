/*
Gabriel Deodato Leite Brandão
2019134778
2019/2020
*/
#include <stdio.h>
#include "back_end.c"
#include <conio.h>


int main() {
    pessoa *p_pessoas = NULL;
    local *p_espaco = NULL;

    int tamanho;

    p_pessoas = read_pessoas();
    p_espaco = read_espacos(&tamanho);



    if (p_pessoas != NULL && p_espaco != NULL) {

        distribuir_aleatorio(p_pessoas, p_espaco, tamanho);
        menu(p_pessoas, p_espaco, tamanho);

    } else {
        printf("E necessario pessoas e espacos para a execucao da simulacao");
    }

    return 0;

}
