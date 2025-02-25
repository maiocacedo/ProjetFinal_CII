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
            menuLocacaoCarros();
            break;

        case 2:
            limparTela();
            menuCarros(); // chama a funcao de menu do modulo de carros
            break;

        case 3:
            limparTela();
            menuClientes(); // chama a funcao de menu do modulo de clientes
            break;

        case 0:
            limparTela();
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao indisponivel, Tente novamente. \n");
#ifdef _WIN32
            Sleep(1000);
#endif

            getchar();
        }
    } while (opc != 0);
}

void menuLocacaoCarros()
{//? menu para a aba de locação de carros

    int opc;
    do
    {
       limparTela();
        printf("\n==========LOCACAO DE CARROS==========\n");
        printf("1. Vizualizar Locacoes\n");
        printf("2. Incluir Locacoes\n");
        printf("3. Dar baixa Locacoes\n");
        printf("0. Voltar\n");
        printf("\n==========================\n");
        printf("\nOpcao: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            limparTela();
            // vizualizarLocacoes();
            printf("\nPressione ENTER para voltar ao menu");
            getchar();
            getchar();
            break;

        case 2:
            limparTela();
           //incluirLocacoes();
            printf("\nPressione ENTER para voltar ao menu");
            getchar();
            getchar();
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

            getchar();

            break;

        case 2:
            limparTela();
            incluirCarros();

            getchar();

            break;

        case 0:
            limparTela();
            printf("Voltando...\n");
            break;
        default:
            printf("Opcao invalida\n");
#ifdef _WIN32
            Sleep(1000); //timer de 1 segundo quando for dado uma opcao invalida
#endif
        }

        if (opc != 0)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while (opc != 0);
}

Carro carros[MAX_CARROS]; // Matriz dos carros
int totalCarros = 0;

void incluirCarros()
{
    limparTela();
    char nomeArquivo[TAM_LINHA];

    printf("Digite o nome do arquivo de cadastro (ex: carros_registro.txt): ");
    scanf("%s", nomeArquivo);

    // Adiciona o caminho do arquivo de entrada
    char caminhoArquivoEntrada[TAM_LINHA + 20];
    snprintf(caminhoArquivoEntrada, sizeof(caminhoArquivoEntrada), "txt/Entradas/%s", nomeArquivo);

    // abre o arquivo
    FILE *arquivoEntrada = fopen(caminhoArquivoEntrada, "r");
    if (arquivoEntrada == NULL)
    {
        printf("ERRO: arquivo nao encontrado");
        return;
    }

    // criando o arquivo de confirmacoa
    FILE *arquivoConfirmacao = fopen("txt/Saidas/cadastros_de_carros_realizados.txt", "w");
    fprintf(arquivoConfirmacao, "=======Cadastros Realizados Com Sucesso======\n\n");

    char linha[TAM_LINHA];
    int linhaAtual = 0;
    Carro novoCarro;

    while (fgets(linha, TAM_LINHA, arquivoEntrada) != NULL && totalCarros < MAX_CARROS)
    {
        linha[strcspn(linha, "\n")] = '\0'; // remove quebra de linha

        switch (linhaAtual % 4) // usa as quatro primeiras linhas para adicionar um novo cadastro na formataçao do arquivo de entrada
        {
        case 0:
            strcpy(novoCarro.marca, linha);
            break;
        case 1:
            strcpy(novoCarro.modelo, linha);
            break;
        case 2:
            novoCarro.ano = atoi(linha);
            break;
        case 3:
            strcpy(novoCarro.placa, linha);

            // adiciona o carro a matriz
            carros[totalCarros] = novoCarro;

            // escrevendo o arquivo de confirmacao
            fprintf(arquivoConfirmacao, "Carro %d:\n", totalCarros + 1);
            fprintf(arquivoConfirmacao, "Marca: %s\n", novoCarro.marca);
            fprintf(arquivoConfirmacao, "Modelo: %s\n", novoCarro.modelo);
            fprintf(arquivoConfirmacao, "Ano: %d\n", novoCarro.ano);
            fprintf(arquivoConfirmacao, "Placa: %s\n", novoCarro.placa);
            fprintf(arquivoConfirmacao, "-----------------------------\n\n");

            totalCarros++;
            break;
        }
        linhaAtual++;
    }

    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);

    printf("\n%d carros cadastrados com sucesso!\n", totalCarros);
    printf("Comprovante salvo em: txt/Saidas/cadastros_de_carros_realizados.txt\n");
}

void vizualizarCarros()
{

    limparTela();
    if (totalCarros == 0)
    {
        printf("Nenhum Cadastro Efetuado!\n");
        return;
    }

    limparTela();
    printf("\n========== CARROS CADASTRADOS ==========\n");
    for (int i = 0; i < totalCarros; i++)
    {
        printf("\nCarro %d:\n", i + 1);
        printf("Marca: %s\n", carros[i].marca);
        printf("Modelo: %s\n", carros[i].modelo);
        printf("Ano: %d\n", carros[i].ano);
        printf("Placa: %s\n", carros[i].placa);
        printf("-----------------------------\n");
    }
}

Cliente clientes[MAX_CLIENTES]; // Matriz dos clientes
int totalClientes = 0;

void menuClientes()
{
    int opc;
    do
    {
        limparTela();
        printf("\n==========CLIENTES==========\n");
        printf("1. Vizualizar Cadastros\n");
        printf("2. Incluir Cadastros\n");
        printf("0. Voltar\n");
        printf("\n==========================\n");
        printf("\nOpcao: ");
        scanf("%d", &opc);
        getchar();

        switch (opc)
        {
        case 1:
            limparTela();
            vizualizarClientes();
            // printf("\nPressione ENTER para voltar ao menu");
            getchar();

            break;

        case 2:
            limparTela();
            incluirClientes();
            // printf("\nPressione ENTER para voltar ao menu");
            getchar();
            break;

        case 0:
            limparTela();
            printf("Voltando...\n");
            break;
        default:
            printf("Opcao invalida\n");
#ifdef _WIN32
            Sleep(1000); // timer de 1 segundo apos dar uma opcao invalida
#endif
        }

        if (opc != 0)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    } while (opc != 0);
}

void incluirClientes()
{
    limparTela();

    char nomeArquivoCli[TAM_LINHA];
    // int totalClientes = 0;

    printf("Digite o nome do arquivo de cadastro (ex: cliente_registro.txt): ");
    scanf("%s", nomeArquivoCli);

    char caminhoArquivoEntrada[TAM_LINHA + 20];
    snprintf(caminhoArquivoEntrada, sizeof(caminhoArquivoEntrada), "txt/Entradas/%s", nomeArquivoCli);

    // arquivo de entrada
    FILE *arquivoEntrada = fopen(caminhoArquivoEntrada, "r");
    if (arquivoEntrada == NULL)
    {
        printf("ERRO: arquivo nao encontrado");
        return;
    }

    // criando o arquivo de confirmacoa
    FILE *arquivoConfirmacao = fopen("txt/Saidas/cadastros_de_clientes_realizados.txt", "w");
    fprintf(arquivoConfirmacao, "=======Cadastros Realizados Com Sucesso======\n\n");

    char linha[TAM_LINHA];
    int linhaAtual = 0;
    Cliente novoCliente;

    while (fgets(linha, TAM_LINHA, arquivoEntrada) != NULL && totalClientes < MAX_CLIENTES)
    {

        linha[strcspn(linha, "\n")] = '\0'; // remove quebra de linha

        switch (linhaAtual % 4) // usa as quatro primeiras linhas para adicionar um novo cadastro na formataçao do arquivo de entrada
        {
        case 0:
            strcpy(novoCliente.nome, linha);
            break;
        case 1:
            strcpy(novoCliente.telefone, linha);
            break;
        case 2:
            strcpy(novoCliente.endereco, linha);
            break;
        case 3:
            strcpy(novoCliente.CPF, linha);

            // adiciona o carro à matriz
            clientes[totalClientes] = novoCliente;

            // escrevendo o arquivo de confirmacao
            fprintf(arquivoConfirmacao, "Cliente %d:\n", totalClientes + 1);
            fprintf(arquivoConfirmacao, "Nome: %s\n", novoCliente.nome);
            fprintf(arquivoConfirmacao, "Telefone: %s\n", novoCliente.telefone);
            fprintf(arquivoConfirmacao, "Endereco: %s\n", novoCliente.endereco);
            fprintf(arquivoConfirmacao, "CPF: %s\n", novoCliente.CPF);
            fprintf(arquivoConfirmacao, "-----------------------------\n\n");

            totalClientes++;
            break;
        }
        linhaAtual++;
    }

    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);

    printf("\n%d clientes cadastrados com sucesso!\n", totalClientes);
    printf("Detalhes salvos em: txt/Saidas/cadastros_de_clientes_realizados.txt\n");
}

void vizualizarClientes()
{
    limparTela();
    if (totalClientes == 0)
    {
        printf("Nenhum Cadastro Efetuado!\n");
        return;
    }

    printf("\n========== CLIENTES CADASTRADOS ==========\n");
    for (int i = 0; i < totalClientes; i++)
    {
        printf("\nCientes %d:\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Endereco: %s\n", clientes[i].endereco);
        printf("CPF: %s\n", clientes[i].CPF);
        printf("-----------------------------\n");
    }
}

void limparTela()
{
#ifdef _WIN32
    system("cls");
#endif
}
