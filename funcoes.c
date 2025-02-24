#include "funcoes.h"

void boasVindas()
{
    limparTela();
    printf("\n==========Seja bem vindo ao SlockCar==========\n");
    printf("Sistema de locacao de carros.\n\n");
    printf("Pressione ENTER para estar se encaminhando ao MENU...");
}

void menuPrincipal()
{
    int opc;
    do
    {
        limparTela();
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
            limparTela();
            printf("Locacao de Carros");

            break;

        case 2:
            limparTela();
            menuCarros();
            break;

        case 3:
            limparTela();
            printf("Clientes");

            break;

        case 0:
            limparTela();
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao indisponivel, Tente novamente. \n");
            getchar();
            getchar();    
        }
    } while (opc != 0);
}

void menuLocacaoCarros()
{
}

void menuCarros()
{ // menu para a aba de carros

    int opc;
    do
    {
        limparTela();
        printf("\n==========CARROS==========\n");
        printf("1. Vizualizar Cadastros\n");
        printf("2. Incluir Cadastros\n");
        printf("0. Voltar\n");
        printf("\n==========================\n");
        printf("\nOpcao: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            limparTela();
            vizualizarCarros();
            printf("\nPressione ENTER para voltar ao menu");
            getchar(); getchar();
            break;

        case 2:
            limparTela();
            incluirCarros();
            printf("\nPressione ENTER para voltar ao menu");
            getchar(); getchar();
            break;

        case 0:
            limparTela();
            printf("Voltando...\n");
            break;
        default:
            printf("Opcao invalida\n");
        }

        if (opc != 0)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
            getchar();
        }
    } while (opc != 0);
}

Carro carros[MAX_CARROS];//Matriz dos carros
int totalCarros = 0;

void incluirCarros(){

    limparTela();
    char nomeArquivo[TAM_LINHA];

    printf("Digite o nome do arquivo de cadastro (ex: carros_registro.txt): ");
    scanf("%s", nomeArquivo);

    //arquivo de entrada
    FILE *arquivoEntrada = fopen(nomeArquivo, "r");
    if (arquivoEntrada == NULL) {
        printf("ERRO: arquivo não encontrado");
        return;
    }

    //criando o arquivo de confirmacoa
    FILE *arquivoConfirmacao = fopen("cadastros_realizados.txt", "w");
    fprintf(arquivoConfirmacao, "=======Cadastros Realizados Com Sucesso======\n\n");
    
    char linha[TAM_LINHA];
    int linhaAtual = 0;
    Carro novoCarro;

    while (fgets(linha, TAM_LINHA, arquivoEntrada) != NULL && totalCarros < MAX_CARROS) {

        linha[strcspn(linha, "\n")] = '\0'; //remove quebra de linha

        switch (linhaAtual % 4) {
            case 0: strcpy(novoCarro.marca, linha); break;
            case 1: strcpy(novoCarro.modelo, linha); break;
            case 2: novoCarro.ano = atoi(linha); break;
            case 3:
            strcpy(novoCarro.placa, linha);

            //adiciona o carro à matriz
            carros[totalCarros] = novoCarro;

            //escrevendo o arquivo de confirmacao
            fprintf(arquivoConfirmacao, "Carro %d:\n", ++totalCarros);
                fprintf(arquivoConfirmacao, "Marca: %s\n", novoCarro.marca);
                fprintf(arquivoConfirmacao, "Modelo: %s\n", novoCarro.modelo);
                fprintf(arquivoConfirmacao, "Ano: %d\n", novoCarro.ano);
                fprintf(arquivoConfirmacao, "Placa: %s\n", novoCarro.placa);
                fprintf(arquivoConfirmacao, "-----------------------------\n\n");

            totalCarros ++;
            break;
        }
        linhaAtual ++;
    }

    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);

    FILE *arquivoSaida = fopen("carros.txt", "a");
    for (int i = 0; i < totalCarros; i++) {
        fprintf(arquivoSaida, "%s\n%s\n%d\n%s\n", 
                carros[i].marca, 
                carros[i].modelo, 
                carros[i].ano, 
                carros[i].placa);
    }
    fclose(arquivoSaida);

    printf("\n%d carros cadastrados com sucesso!\n");
    printf("Comprovante salvo em: cadastros_realizados.txt\n");
}


void vizualizarCarros(){
   
    limparTela();
    if (totalCarros == 0){
        printf("Nenhum Cadastro Efetuado!\n");
        return;
    }

    printf("\n========== CARROS CADASTRADOS ==========\n");
    for (int i = 0; i < totalCarros; i++) {
        printf("\nCarro %d:\n", i + 1);
        printf("Marca: %s\n", carros[i].marca);
        printf("Modelo: %s\n", carros[i].modelo);
        printf("Ano: %d\n", carros[i].ano);
        printf("Placa: %s\n", carros[i].placa);
        printf("-----------------------------\n");
    }
}

void limparTela()
{
#ifdef _WIN32
    system("cls");
#endif
}
