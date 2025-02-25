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
{ // menu para a aba de locação de carros

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
            vizualizarLocacoes();
            printf("\nPressione ENTER para voltar ao menu");
            getchar();
            getchar();
            break;

        case 2:
            limparTela();
            incluirLocacoes();
            printf("\nPressione ENTER para voltar ao menu");
            getchar();
            getchar();
            break;
        case 3:
            limparTela();
            darBaixaLocacoes();
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

Locacao *locacoes; // Matriz das locacoes
int totalLocacoes = 0;
void incluirLocacoes()
{

    if(totalCarros == 0 && totalClientes == 0){printf("Nao ha carros ou clientes cadastrados\n");return;}
    if(totalClientes == 0){printf("Nao ha clientes cadastrados\n");return;}
    if(totalCarros == 0 ){printf("Nao ha carros cadastrados\n");return;}


    locacoes = (Locacao*)malloc((totalLocacoes+1)*sizeof(Locacao));
    char nomeArquivo[TAM_LINHA];
    limparTela();
    printf("Digite o nome do arquivo de cadastro (ex: locacao_registro.txt): ");
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

    // criando o arquivo de confirmacao
    FILE *arquivoConfirmacao = fopen("txt/Saidas/cadastros_de_locacoes_realizados.txt", "w");
    fprintf(arquivoConfirmacao, "=======Cadastros Realizados Com Sucesso======\n\n");

    char linha[TAM_LINHA];
    int linhaAtual = 0;
    Locacao *temp = locacoes;
    Locacao novaLocacao;
    while (fgets(linha, TAM_LINHA, arquivoEntrada) != NULL )
    {
        linha[strcspn(linha, "\n")] = '\0'; // remove quebra de linha
        

        switch (linhaAtual % 6) // usa as quatro primeiras linhas para adicionar um novo cadastro na formataçao do arquivo de entrada
        {
        case 0:
            if (atoi(linha) > totalCarros)
            {
                printf("Carro %d nao cadastrado\n", atoi(linha));
                return;
            }
            novaLocacao.codigoCarro = atoi(linha);
            break;
        case 1:
            if (atoi(linha) > totalClientes)
            {
                printf("Cliente %d nao cadastrado\n", atoi(linha));
                return;
            }
            novaLocacao.codigoCliente = atoi(linha);
            break;
        case 2:
            novaLocacao.valorLocacao = atof(linha);
            break;
        case 3:
            sscanf(linha, "%d/%d/%d", &novaLocacao.dataLocacao.dia, &novaLocacao.dataLocacao.mes, &novaLocacao.dataLocacao.ano);
            break;
        case 4:
            sscanf(linha, "%d/%d/%d", &novaLocacao.dataDevolucao.dia, &novaLocacao.dataDevolucao.mes, &novaLocacao.dataDevolucao.ano);        
            break;
        case 5:
            strcpy(novaLocacao.status, linha);
            temp = (Locacao *)realloc(locacoes, sizeof(*temp) * (totalLocacoes + 1));
            if (temp != NULL)
            {
                locacoes = temp;
                locacoes[totalLocacoes] = novaLocacao;
    
                // escrevendo o arquivo de confirmacao
                fprintf(arquivoConfirmacao, "Locacao %d:\n", totalLocacoes + 1);
                fprintf(arquivoConfirmacao, "Codigo do carro: %d\n", novaLocacao.codigoCarro);
                fprintf(arquivoConfirmacao, "Codigo do cliente: %d\n", novaLocacao.codigoCliente);
                fprintf(arquivoConfirmacao, "Valor da Locacao: %.2f\n", novaLocacao.valorLocacao);
                fprintf(arquivoConfirmacao, "Data da Locacao: %d/%d/%d\n", novaLocacao.dataLocacao.dia, novaLocacao.dataLocacao.mes, novaLocacao.dataLocacao.ano);
                fprintf(arquivoConfirmacao, "Data da Devolucao: %d/%d/%d\n", novaLocacao.dataDevolucao.dia, novaLocacao.dataDevolucao.mes, novaLocacao.dataDevolucao.ano);
                fprintf(arquivoConfirmacao, "Status: %s\n", novaLocacao.status);
                fprintf(arquivoConfirmacao, "-----------------------------\n\n");
    
                totalLocacoes++;
                break;
            }
            else
            {
                printf("Erro ao alocar memoria\n");
                fclose(arquivoEntrada);
                fclose(arquivoConfirmacao);
                return;
            }
        }
        
        linhaAtual++;
    }

    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);

    printf("\n%d locacoes cadastrados com sucesso!\n", totalLocacoes);
    printf("Comprovante salvo em: txt/Saidas/cadastros_de_locacoes_realizados.txt\n");
}



void vizualizarLocacoes()
{
    limparTela();
    if (totalLocacoes == 0)
    {
        printf("Nenhuma Locacao Ativa!\n");
        return;
    }

    printf("\n========== LOCACOES CADASTRADAS ==========\n");
    for (int i = 0; i < totalLocacoes; i++)
    {
        printf("\nLocacao %d:\n", i + 1);
        printf("ID Cliente %d\n", locacoes[i].codigoCliente);
        printf("ID Carro: %d\n", locacoes[i].codigoCarro);
        printf("Valor da Locacao %.2f\n", locacoes[i].valorLocacao);
        printf("Data de Locacao: %d/%d/%d\n", locacoes[i].dataLocacao.dia, locacoes[i].dataLocacao.mes, locacoes[i].dataLocacao.ano);
        printf("Data de Devolucao: %d/%d/%d\n", locacoes[i].dataDevolucao.dia, locacoes[i].dataDevolucao.mes, locacoes[i].dataDevolucao.ano);
        printf("Status: %s\n", locacoes[i].status);
        printf("-----------------------------\n");
    }
}

void darBaixaLocacoes()
{
    int op=1;
    while (op != 0){
    limparTela();
    vizualizarLocacoes();
    printf("Qual locacao deseja dar baixa? \n");
    scanf("%d", &op);
    Locacao temp;

    temp = locacoes[op];
    locacoes[op] = locacoes[totalLocacoes-1];
    locacoes[totalLocacoes-1] = temp;

    totalLocacoes--;
    printf("Deseja dar baixa em outra locacao? \n0.Nao \n1.Sim\n");
    scanf("%d", &op);
}
    system("cls");
    for(int i = 0; i<totalLocacoes; i++){
        printf("\nLocacao %d:\n", i + 1);
        printf("ID Cliente %d\n", locacoes[i].codigoCliente);
        printf("ID Carro: %d\n", locacoes[i].codigoCarro);
        printf("Valor da Locacao %.2f\n", locacoes[i].valorLocacao);
        printf("Data de Locacao: %d/%d/%d\n", locacoes[i].dataLocacao.dia, locacoes[i].dataLocacao.mes, locacoes[i].dataLocacao.ano);
        printf("Data de Devolucao: %d/%d/%d\n", locacoes[i].dataDevolucao.dia, locacoes[i].dataDevolucao.mes, locacoes[i].dataDevolucao.ano);
        printf("Status: %s\n", locacoes[i].status);
        printf("-----------------------------\n");

        FILE *arquivoConfirmacao = fopen("txt/Saidas/cadastros_de_locacoes_realizados.txt", "w");
        fprintf(arquivoConfirmacao, "=======Cadastros Realizados Com Sucesso======\n\n");
        // escrevendo o arquivo de confirmacao
        fprintf(arquivoConfirmacao, "Locacao %d:\n", totalLocacoes + 1);
        fprintf(arquivoConfirmacao, "Codigo do carro: %d\n", locacoes[i].codigoCarro);
        fprintf(arquivoConfirmacao, "Codigo do cliente: %d\n", locacoes[i].codigoCliente);
        fprintf(arquivoConfirmacao, "Valor da Locacao: %.2f\n", locacoes[i].valorLocacao);
        fprintf(arquivoConfirmacao, "Data da Locacao: %d/%d/%d\n", locacoes[i].dataLocacao.dia, locacoes[i].dataLocacao.mes, locacoes[i].dataLocacao.ano);
        fprintf(arquivoConfirmacao, "Data da Devolucao: %d/%d/%d\n", locacoes[i].dataDevolucao.dia, locacoes[i].dataDevolucao.mes, locacoes[i].dataDevolucao.ano);
        fprintf(arquivoConfirmacao, "Status: %s\n", locacoes[i].status);
        fprintf(arquivoConfirmacao, "-----------------------------\n\n");
    }
    system("PAUSE");
    printf("Retornando ao menu");
    for(int i = 0; i<3; i++){
        Sleep(300);
        printf(".");
    }
    printf("Dar Baixa\n");
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
            Sleep(1000); // timer de 1 segundo quando for dado uma opcao invalida
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
void limparMemoria()
{
    free(locacoes);
}
