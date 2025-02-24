#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//?CARRO
#define MAX_CARROS 100
#define TAM_LINHA 100

//?estrutura do carro
typedef struct
{
    char marca[TAM_LINHA];
    char modelo[TAM_LINHA];
    int ano;
    char placa[TAM_LINHA];
} Carro;

//?variaveis globais carros
extern Carro carros[MAX_CARROS];
extern int totalCarros;

//! FUNCOES
void boasVindas(); // exibe a mensagem de boas vindas

void menuPrincipal(); // exibe o menu principal

void menuCarros(); // menu para a aba carros

void incluirCarros(); // funcao para realizar a inclusao de novos carros

void vizualizarCarros(); // funcao para a vizualizaçao dos cadastros ja efetuados

void limparTela(); // limpa a tela

#endif // FUNCOES_H