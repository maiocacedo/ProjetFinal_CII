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
    boasVindas();
    getchar();

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
        if (scanf("%d", &opc) != 1)
        {
            limparBuffer();
            opc = -1;
        }
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
            printf("Opcao indisponivel, Precione ENTER para contiuar... \n");
            limparBuffer();

#ifdef _WIN322
            Sleep(500);
#endif

            // getchar();
        }
    } while (opc != 0);
}

void menuLocacaoCarros()
{ // menu para a aba de locação de carros
    int opc;
    do
    {
        printf("\n==========LOCACAO DE CARROS==========\n");
        printf("1. Vizualizar Locacoes\n");
        printf("2. Incluir Locacoes\n");
        printf("3. Dar baixa Locacoes\n");
        printf("0. Voltar\n");
        printf("\n==========================\n");
        printf("\nOpcao: ");
        if (scanf("%d", &opc) != 1)
        {
            limparBuffer();
            opc = -1;
        }

        switch (opc)
        {
        case 1:
            // Vizualizar as locacoes cadastradas
            limparTela();
            vizualizarLocacoes();
            getchar();
            break;

        case 2:
            // Incluir novas locacoes
            limparTela();
            incluirLocacoes();
            getchar();
            break;

        case 3:
            // Dar baixa nas locacoes
            limparTela();
            darBaixaLocacoes();
            getchar();
            break;

        case 0:
            // Retornar ao menu principal
            limparTela();
            printf("Voltando");
            pontinhos();
            break;

        default:
            printf("Opcao invalida\n");
            limparBuffer();

#ifdef _WIN32
            Sleep(1000);
#endif
        }

        if (opc != 0)
        {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }

    } while (opc != 0);
}

Locacao *locacoes; // Matriz das locacoes

void incluirLocacoes()
{
    // Verificando se há carros e clientes cadastrados
    if (totalCarros == 0 && totalClientes == 0)
    {
        printf("Nao ha carros ou clientes cadastrados\n");
        return;
    }
    // Verificando se há clientes cadastrados
    if (totalClientes == 0)
    {
        printf("Nao ha clientes cadastrados\n");
        return;
    }
    // Verificando se há carros cadastrados
    if (totalCarros == 0)
    {
        printf("Nao ha carros cadastrados\n");
        return;
    }
    // Verificando se locacoes é nula para a primeira locacao
    if (locacoes == NULL)
    {
        locacoes = (Locacao *)malloc(sizeof(Locacao));
    }

    char nomeArquivo[TAM_LINHA];
    limparTela();
    printf("Digite o nome do arquivo de cadastro (ex: locacao_registro.txt): "); // Solicita o nome do arquivo de entrada
    scanf("%s", nomeArquivo);

    // Adiciona o caminho do arquivo de entrada
    char caminhoArquivoEntrada[TAM_LINHA + 20];
    snprintf(caminhoArquivoEntrada, sizeof(caminhoArquivoEntrada), "txt/Entradas/%s", nomeArquivo); // Adiciona o caminho do arquivo de entrada

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

    // criando o arquivo de confirmacao
    FILE *arquivoTotais = fopen("txt/Saidas/cadastros_de_locacoes_realizados.txt", "w");

    char linha[TAM_LINHA];
    int linhaAtual = 0;
    Locacao *temp = locacoes;
    Locacao novaLocacao;

    while (fgets(linha, TAM_LINHA, arquivoEntrada) != NULL)
    {
        linha[strcspn(linha, "\n")] = '\0'; // remove quebra de linha

        switch (linhaAtual % 6) // usa as quatro primeiras linhas para adicionar um novo cadastro na formataçao do arquivo de entrada
        {
        case 0:
            // verificando se o carro existe
            if (atoi(linha) > totalCarros + 1)
            {
                printf("Carro %d nao cadastrado\n", atoi(linha));
                fclose(arquivoEntrada);
                return;
            }
            sscanf(linha, "Codigo Carro: %d", &novaLocacao.codigoCarro); // adiciona o codigo do carro
            break;

        case 1:
            // verificando se o carro existe
            if (atoi(linha) > totalClientes + 1)
            {
                printf("Cliente %d nao cadastrado\n", atoi(linha));
                fclose(arquivoEntrada);
                return;
            }
            sscanf(linha, "Codigo Cliente: %d", &novaLocacao.codigoCliente); // adiciona o codigo do cliente
            break;

        case 2:
            sscanf(linha, "Valor da locacao: %lf", &novaLocacao.valorLocacao); // adiciona o valor da locacao
            break;

        case 3:
            sscanf(linha, "Data da locacao: %d/%d/%d", &novaLocacao.dataLocacao.dia, &novaLocacao.dataLocacao.mes, &novaLocacao.dataLocacao.ano); // adiciona a data da locacao
            break;

        case 4:
            sscanf(linha, "Data de Devolucao: %d/%d/%d", &novaLocacao.dataDevolucao.dia, &novaLocacao.dataDevolucao.mes, &novaLocacao.dataDevolucao.ano); // adiciona a data de devolucao
            break;

        case 5:
            sscanf(linha, "Status: %s", novaLocacao.status);                          // adiciona o status da locacao
            temp = (Locacao *)realloc(locacoes, sizeof(*temp) * (totalLocacoes + 1)); // realoca a memoria para alocar a nova locacao
            if (temp != NULL)
            {
                locacoes = temp;
                locacoes[totalLocacoes] = novaLocacao;

                // escrevendo o arquivo de confirmacao
                fprintf(arquivoConfirmacao, "Locacao %d:\n", totalLocacoes + 1);
                fprintf(arquivoConfirmacao, "Codigo do carro: %d\n", novaLocacao.codigoCarro);
                fprintf(arquivoConfirmacao, "Codigo do cliente: %d\n", novaLocacao.codigoCliente);
                fprintf(arquivoConfirmacao, "Valor da locacao: %.2f\n", novaLocacao.valorLocacao);
                fprintf(arquivoConfirmacao, "Data da locacao: %d/%d/%d\n", novaLocacao.dataLocacao.dia, novaLocacao.dataLocacao.mes, novaLocacao.dataLocacao.ano);
                fprintf(arquivoConfirmacao, "Data da devolucao: %d/%d/%d\n", novaLocacao.dataDevolucao.dia, novaLocacao.dataDevolucao.mes, novaLocacao.dataDevolucao.ano);
                fprintf(arquivoConfirmacao, "Status: %s\n", novaLocacao.status);
                fprintf(arquivoConfirmacao, "-----------------------------\n\n");

                // Escreve no arquivo de todos os cadastros
                fprintf(arquivoTotais, "Locacao %d:\n", totalLocacoes + 1);
                fprintf(arquivoTotais, "Codigo do carro: %d\n", novaLocacao.codigoCarro);
                fprintf(arquivoTotais, "Codigo do cliente: %d\n", novaLocacao.codigoCliente);
                fprintf(arquivoTotais, "Valor da locacao: %.2f\n", novaLocacao.valorLocacao);
                fprintf(arquivoTotais, "Data da locacao: %d/%d/%d\n", novaLocacao.dataLocacao.dia, novaLocacao.dataLocacao.mes, novaLocacao.dataLocacao.ano);
                fprintf(arquivoTotais, "Data da devolucao: %d/%d/%d\n", novaLocacao.dataDevolucao.dia, novaLocacao.dataDevolucao.mes, novaLocacao.dataDevolucao.ano);
                fprintf(arquivoTotais, "Status: %s\n", novaLocacao.status);
                fprintf(arquivoTotais, "-----------------------------\n\n");

                totalLocacoes++;
                break;
            }
            else
            {
                // Caso não consiga alocar a memoria
                printf("Erro ao alocar memoria\n");
                fclose(arquivoEntrada);
                fclose(arquivoConfirmacao);
                fclose(arquivoTotais);
                return;
            }
        }

        linhaAtual++;
    }

    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);
    fclose(arquivoTotais);

    printf("\n%d locacoes cadastrados com sucesso!\n", totalLocacoes);
    printf("Comprovante salvo em: txt/Saidas/cadastros_de_locacoes_realizados.txt\n");
}

void vizualizarLocacoes()
{
    limparTela();
    // Verifica se há locacoes cadastradas
    if (totalLocacoes == 0)
    {
        printf("Nenhuma Locacao Ativa!\n");
        return;
    }
    // Vizualiza as locacoes cadastradas e as imprime
    printf("\n========== LOCACOES CADASTRADAS ==========\n");
    for (int i = 0; i < totalLocacoes; i++)
    {
        printf("\nLocacao %d:\n", i + 1);
        printf("Codigo Carro: %d\n", locacoes[i].codigoCarro);
        printf("Codigo Cliente %d\n", locacoes[i].codigoCliente);
        printf("Valor da locacao %.2f\n", locacoes[i].valorLocacao);
        printf("Data de locacao: %d/%d/%d\n", locacoes[i].dataLocacao.dia, locacoes[i].dataLocacao.mes, locacoes[i].dataLocacao.ano);
        printf("Data de devolucao: %d/%d/%d\n", locacoes[i].dataDevolucao.dia, locacoes[i].dataDevolucao.mes, locacoes[i].dataDevolucao.ano);
        printf("Status: %s\n", locacoes[i].status);
        printf("-----------------------------\n");
    }
}

void darBaixaLocacoes()
{
    int op = 1;
    // enquanto o usuario desejar dar baixa em locacoes
    while (op != 0)
    {
        limparTela();
        vizualizarLocacoes(); // Vizualiza as locacoes cadastradas

        // Verifica se há locacoes cadastradas
        if (totalLocacoes == 0)
        {
            return;
        }
        // Solicita a locacao que deseja dar baixa
        printf("Qual locacao deseja dar baixa? \n");
        scanf("%d", &op);
        Locacao temp;

        op--; // decrementa a opcao para o indice da matriz (para deixar mais intuitivo ao usuario)

        // Move a locacao para o final da matriz
        temp = locacoes[op];
        locacoes[op] = locacoes[totalLocacoes - 1];
        locacoes[totalLocacoes - 1] = temp;

        totalLocacoes--;                                                // decrementa o total de locacoes
        printf("Deseja dar baixa em outra locacao? \n0.Nao \n1.Sim\n"); // Pergunta se deseja dar baixa em outra locacao
        scanf("%d", &op);
    }

    system("cls");

    FILE *arquivoConfirmacao = fopen("txt/CadastrosTotais/todas_as_locacoes.txt", "w");
    // Escreve no arquivo de todos os cadastros a fim de salvar a baixa
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

    fclose(arquivoConfirmacao);

    printf("Retornando ao menu");
    pontinhos();
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
        if (scanf("%d", &opc) != 1)
        {
            opc = -1;
        }

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
            limparBuffer();

#ifdef _WIN32
            Sleep(500); // timer de 1 segundo quando for dado uma opcao invalida
#endif
        }

        if (opc != 0)
        {
            printf("Pressione ENTER para continuar...");
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

    printf("Exemplo de formatacao para o arquivo de entrada:\n");
    printf("\n> Marca: Fiat\n");
    printf("> Modelo: Palio\n");
    printf("> Ano: 2011\n");
    printf("> Placa: ABC123\n");
    printf("\nCOLOQUE NO ARQUIVO DE ENTRADA APENAS SOMENTE OS DADOS DO CARRO, CADA DADO EM UMA LINHA.\n");

    printf("\nDigite o nome do arquivo de cadastro (ex: carros_registro.txt): ");
    scanf("%s", nomeArquivo);

    // Adiciona o caminho do arquivo de entrada
    char caminhoArquivoEntrada[TAM_LINHA + 20];
    snprintf(caminhoArquivoEntrada, sizeof(caminhoArquivoEntrada), "txt/Entradas/%s", nomeArquivo);

    // abre o arquivo
    FILE *arquivoEntrada = fopen(caminhoArquivoEntrada, "r");
    if (arquivoEntrada == NULL)
    {
        printf("ERRO: arquivo nao encontrado. \n");
        return;
    }

    // criando o arquivo de confirmacoa
    FILE *arquivoConfirmacao = fopen("txt/Saidas/cadastros_de_carros_realizados.txt", "w");
    fprintf(arquivoConfirmacao, "=======Cadastros Realizados Com Sucesso======\n\n");

    // Abre o arquivo de todos os cadastros no modo de adição
    FILE *arquivoTodosCadastros = fopen("txt/CadastrosTotais/todos_os_carros.txt", "a");
    if (arquivoTodosCadastros == NULL)
    {
        printf("ERRO: não foi possível abrir o arquivo de todos os cadastros");
        fclose(arquivoEntrada);
        fclose(arquivoConfirmacao);
        return;
    }

    char linha[TAM_LINHA];
    int linhaAtual = 0;
    Carro novoCarro;

    // Lê o arquivo de entrada linha por linha
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

            // Escreve no arquivo de todos os cadastros
            fprintf(arquivoTodosCadastros, "Carro %d:\n", totalCarros + 1);
            fprintf(arquivoTodosCadastros, "Marca: %s\n", novoCarro.marca);
            fprintf(arquivoTodosCadastros, "Modelo: %s\n", novoCarro.modelo);
            fprintf(arquivoTodosCadastros, "Ano: %d\n", novoCarro.ano);
            fprintf(arquivoTodosCadastros, "Placa: %s\n", novoCarro.placa);
            fprintf(arquivoTodosCadastros, "-----------------------------\n\n");

            totalCarros++;
            break;
        }
        linhaAtual++;
    }

    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);
    fclose(arquivoTodosCadastros);

    printf("\n%d carros cadastrados com sucesso!\n", totalCarros);
    printf("Comprovante salvo em: txt/Saidas/cadastros_de_carros_realizados.txt\n");
    printf("Todos os cadastros salvos em: txt/CadastrosTotais/todos_os_carros.txt\n");
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
        if (scanf("%d", &opc) != 1)
        {
            opc = -1;
        }

        switch (opc)
        {
        case 1:
            limparTela();
            vizualizarClientes();
            getchar();

            break;

        case 2:
            limparTela();
            incluirClientes();
            getchar();
            break;

        case 0:
            limparTela();
            printf("Voltando...\n");
            break;

        default:
            printf("Opcao invalida\n");
            limparBuffer();

#ifdef _WIN32
            Sleep(500); // timer de 1 segundo apos dar uma opcao invalida
#endif
        }

        if (opc != 0)
        {
            printf("Pressione ENTER para continuar...");
            getchar();
        }
    } while (opc != 0);
}

void incluirClientes()
{
    limparTela();

    char nomeArquivoCli[TAM_LINHA];

    printf("Exemplo de formatacao para o arquivo de entrada:\n");
    printf("\n> Nome: jose\n");
    printf("> Telefone: (42) 9984-2578\n");
    printf("> Endereco: Rua Sao Paulo\n");
    printf("> CPF: 189.005.302-64\n");
    printf("\nCOLOQUE NO ARQUIVO DE ENTRADA APENAS SOMENTE OS DADOS DO CLIENTE, CADA DADO EM UMA LINHA.\n");

    printf("\nDigite o nome do arquivo de cadastro (ex: cliente_registro.txt): ");
    scanf("%s", nomeArquivoCli);

    char caminhoArquivoEntrada[TAM_LINHA + 20];
    snprintf(caminhoArquivoEntrada, sizeof(caminhoArquivoEntrada), "txt/Entradas/%s", nomeArquivoCli);

    // arquivo de entrada
    FILE *arquivoEntrada = fopen(caminhoArquivoEntrada, "r");
    if (arquivoEntrada == NULL)
    {
        printf("ERRO: arquivo nao encontrado. \n");
        return;
    }

    // criando o arquivo de confirmacoa
    FILE *arquivoConfirmacao = fopen("txt/Saidas/cadastros_de_clientes_realizados.txt", "w");
    fprintf(arquivoConfirmacao, "=======Cadastros Realizados Com Sucesso======\n\n");

    // Abre o arquivo de todos os cadastros no modo de adiçao
    FILE *arquivoTodosCadastros = fopen("txt/CadastrosTotais/todos_os_clientes.txt", "a");
    if (arquivoTodosCadastros == NULL)
    {
        printf("ERRO: nao foi possivel abrir o arquivo de todos os cadastros");
        fclose(arquivoEntrada);
        fclose(arquivoConfirmacao);
        return;
    }

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

            // adiciona o carro a matriz
            clientes[totalClientes] = novoCliente;

            // escrevendo o arquivo de confirmacao
            fprintf(arquivoConfirmacao, "Cliente %d:\n", totalClientes + 1);
            fprintf(arquivoConfirmacao, "Nome: %s\n", novoCliente.nome);
            fprintf(arquivoConfirmacao, "Telefone: %s\n", novoCliente.telefone);
            fprintf(arquivoConfirmacao, "Endereco: %s\n", novoCliente.endereco);
            fprintf(arquivoConfirmacao, "CPF: %s\n", novoCliente.CPF);
            fprintf(arquivoConfirmacao, "-----------------------------\n\n");

            // escreve no arquivo de todos os cadastros
            fprintf(arquivoTodosCadastros, "Cliente %d:\n", totalClientes + 1);
            fprintf(arquivoTodosCadastros, "Nome: %s\n", novoCliente.nome);
            fprintf(arquivoTodosCadastros, "Telefone: %s\n", novoCliente.telefone);
            fprintf(arquivoTodosCadastros, "Endereco: %s\n", novoCliente.endereco);
            fprintf(arquivoTodosCadastros, "CPF: %s\n", novoCliente.CPF);
            fprintf(arquivoTodosCadastros, "-----------------------------\n\n");

            totalClientes++;
            break;
        }
        linhaAtual++;
    }

    fclose(arquivoEntrada);
    fclose(arquivoConfirmacao);
    fclose(arquivoTodosCadastros);

    printf("\n%d clientes cadastrados com sucesso!\n", totalClientes);
    printf("Detalhes salvos em: txt/Saidas/cadastros_de_clientes_realizados.txt\n");
    printf("\nTodos os cadastros salvos em: txt/CadastrosTotais/todos_os_clientes.txt\n");
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

void limparBuffer()
{
    int b;
    while ((b = getchar()) != '\n' && b != EOF)
        ;
}