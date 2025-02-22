#include "funcoes.h"

void boasVindas()
{
    printf("\n==========Seja bem vindo ao SlockCar==========\n");
    printf("Sistema de locacao de carros.\n\n");
    printf("Pressione ENTER para estar se encaminhando ao MENU...");
}

void menuPrincipal()
{
    int opc;
    do {
    printf("\n==========MENU==========\n");
    printf("1_Locacao de Carros \n");
    printf("2_Carros \n");
    printf("3_Clientes \n");
    printf("0_Sair \n");
    printf("========================\n");
    printf("\nOpcao: ");
    scanf("%d", &opc);

    switch (opc)
    {
    case 1:
        printf("Locacao de Carros");

        break;

    case 2:
        printf("Carros");
        
        break;

    case 3:
        printf("Clientes");

        break;

    case 0:
        printf("Saindo...\n");
        break;
    default:
        printf("Opcao indisponivel, Tente novamente. \n");
    }
} while (opc != 0);
}


void limparTela()
{
#ifdef _WIN32
    system("cls");
#endif
}
