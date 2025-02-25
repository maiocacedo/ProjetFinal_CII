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

//?CLIENTES
#define MAX_CLIENTES 100
//#define TAM_LINHA 100

//?estrutura clientes
typedef struct
{
    char nome[TAM_LINHA];
    char telefone[TAM_LINHA];
    char endereco [TAM_LINHA];
    char CPF [TAM_LINHA];
} Cliente;

//?variaveis globais clientes
extern Cliente clientes [MAX_CLIENTES];
extern int totalClientes;

//! FUNCOES
void boasVindas(); // exibe a mensagem de boas vindas

void menuPrincipal(); // exibe o menu principal

void menuCarros(); // menu para a aba carros

void menuLocacaoCarros(); // menu para a locacao de carros

void incluirCarros(); // funcao para realizar a inclusao de novos carros

void vizualizarCarros(); // funcao para a vizualizaçao dos cadastros ja efetuados

void menuClientes();//menu da opcao clientes

void incluirClientes(); //funcao para fazer a inclusao de clientes

void vizualizarClientes(); //funcao para vizualizar os cadastros de clientes ja realizados

void limparTela(); // limpa a tela

#endif // FUNCOES_H