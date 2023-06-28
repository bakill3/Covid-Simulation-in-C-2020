/*
Gabriel Deodato Leite Brandão
2019134778
2019/2020
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#ifndef UTILS_H
#define UTILS_H

// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int intUniformRnd(int a, int b);

// Devolve o valor 1 com probabilidade prob. Caso contrario, devolve 0
int probEvento(float prob);

#endif /* UTILS_H */


typedef struct sala local, *plocal;
struct sala {
    int id;
    int capacidade;
    int liga[3];
};

typedef struct pessoas pessoa, *ppessoas;
struct pessoas {
    char nome[30];
    int idade;
    char estado_paciente[1]; // - I / D / S
    int dias_infetados;
    local* x_sala;
    pessoa* prox;
};



pessoa* read_pessoas();
local* read_espacos(int* tamanho);
void distribuir_aleatorio(pessoa* p_pessoas, local* p_espaco, int tamanho);
int conta_pessoas_na_sala(int id_sala, pessoa* p_pessoas);
void menu(pessoa* p_pessoas, local* p_espaco, int tamanho);
void avancar_um_dia(pessoa* p_pessoas, local* p_espaco, int tamanho);
void apresentar_estatistica(pessoa* p_pessoas, local* p_espaco, int tamanho);
void adicionar_doente(pessoa* p_pessoas, local* p_espaco, int tamanho);
void transferir_pessoas(pessoa* p_pessoas, local* p_espaco, int tamanho);
void terminar_simulacao(pessoa* p_pessoas, local* p_espaco, int tamanho);
int calcular_novos_infetados(pessoa* p_pessoas, local* p_espaco, int tamanho);
int verificar_ligacao(local* p_espaco, int sala_escolhida_1, int sala_escolhida_2, int tamanho);
int conta_todas_as_pessoas(pessoa* p_pessoas);

//int read_espacos(int* espaco_tam);
