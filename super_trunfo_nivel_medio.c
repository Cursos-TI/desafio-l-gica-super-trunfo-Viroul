#include <stdio.h>
#include <string.h>
#include <ctype.h>

//VARIAVEIS DA CARTA
struct Carta {
    int num_estados;                    // Quantidade de estados cadastrados
    int cidades_por_estado[8];          // Quantidade de cidades cadastradas por estado
    int estado_atual;                   // Índice do estado atual
    int num_cartas;                     // Quantidade de cartas cadastradas
    int cartas_selecionadas[2][2];      // Quantidade de cartas selecionadas

    // PROPRIEDADES DAS CARTAS
    char codigo[8][4][4];               // Codigo da carta
    char Estado_nome[8][50];            // Nome do estado (máximo de 8 estados)
    char cidades[8][4][50];             // Até 4 cidades por estado
    int populacao[8][4];                // População de cada cidade
    float area[8][4];                   // Área de cada cidade
    float Densidade_populacional[8][4]; // Densidade populacional de cada cidade
    float PIB_per_capita[8][4];         // PIB per capita de cada cidade
    double PIB[8][4];                   // PIB da cidade
    int pontos_turisticos[8][4];        // Pontos turísticos da cidade

};
// Verifica se uma carta com o código existe
int carta_existe(struct Carta *informacoes, const char *codigo_busca) {
    for (int i = 0; i < informacoes->num_estados; i++) {
        for (int j = 0; j < informacoes->cidades_por_estado[i]; j++) {
            if (strcmp(informacoes->codigo[i][j], codigo_busca) == 0) {
                return 1;}}}
    return 0;
}

// Encontra os índices da carta pelo código
int encontrar_indices_carta(struct Carta *dados, const char *codigo, int *estado_index, int *cidade_index) {
    for (int i = 0; i < dados->num_estados; i++) {
        for (int j = 0; j < dados->cidades_por_estado[i]; j++) {
            if (strcmp(dados->codigo[i][j], codigo) == 0) {
                *estado_index = i;
                *cidade_index = j;
                return 1;}}}
    return 0;
}

// Verifica se o estado já existe
int estado_existente(struct Carta *verificar_estado, const char *estado_nome) {
    for (int i = 0; i < verificar_estado->num_estados; i++) {
        if (strcmp(verificar_estado->Estado_nome[i], estado_nome) == 0) {
            verificar_estado->estado_atual = i; // Define o índice do estado existente como o atual
            return 1; // Estado encontrado
        }
    }
    return 0; // Estado não encontrado
}

// Verifica se a cidade já existe
int cidade_existente(struct Carta *verificar_cidade, const char *cidade_nome) {
    // Verifica se a cidade já foi cadastrada em algum estado
    for (int i = 0; i < verificar_cidade->num_estados; i++) {
        for (int j = 0; j < verificar_cidade->cidades_por_estado[i]; j++) {
            if (strcmp(verificar_cidade->cidades[i][j], cidade_nome) == 0) {
                return 1; // Cidade já existe
            }
        }
    }
    return 0; // Cidade não encontrada
}

// Cadastro de estado
void adicionar_estado(struct Carta *Dados_do_estado) {
    // Limite de estados atingido
    if (Dados_do_estado->num_estados >= 8) {
        printf("Limite de estados atingido\n");
        return;
    }

    char estado_nome[50];

    printf("\n====== CADASTRE UM NOVO ESTADO ========\n");
    while (1) {
        printf("\nDigite o nome do Estado: ");
        scanf(" %49[^\n]", estado_nome);

        // Verificar se o estado já foi cadastrado
        if (estado_existente(Dados_do_estado, estado_nome)) {
            printf("Estado já cadastrado.\n");
            break;
        } else {
            // Adiciona o nome do estado à lista
            strcpy(Dados_do_estado->Estado_nome[Dados_do_estado->num_estados], estado_nome);
            Dados_do_estado->cidades_por_estado[Dados_do_estado->num_estados] = 0; // Inicializa o contador de cidades para este estado
            Dados_do_estado->num_estados++;
            Dados_do_estado->estado_atual = Dados_do_estado->num_estados - 1; // Atualiza o estado atual
            break;
        }
    }
}

// Cadastro de cidade
void adicionar_cidade(struct Carta *Dados_da_cidade) {
    if (Dados_da_cidade->cidades_por_estado[Dados_da_cidade->estado_atual] >= 4) {
        printf("Limite de cidades para este estado atingido.\n");
        return;
    }
    //variaveis temporarias
    char cidade_nome[50];
    char codigo_carta[4];

    while (1) {
        //Recebendo o codigo da carta
        printf("\nDigite o código da carta (ex: A01): ");
        scanf(" %3s", codigo_carta);
        
        //codigo ja utilizado
        if (carta_existe(Dados_da_cidade, codigo_carta)) {
            printf("Código já utilizado. Tente outro.\n");
        } else {
            break;
        }
    }

    while (1) {
        printf("\nDigite o nome da Cidade: ");
        scanf(" %49[^\n]", cidade_nome);

        // Verifica se a cidade já foi cadastrada
        if (cidade_existente(Dados_da_cidade, cidade_nome)) {
            printf("Cidade já existente. Crie outra cidade.\n");
        } else {
            break; // Cidade válida
        }
    }
    // Adiciona a cidade à lista do estado atual
    int cidade_index = Dados_da_cidade->cidades_por_estado[Dados_da_cidade->estado_atual];
    strcpy(Dados_da_cidade->codigo[Dados_da_cidade->estado_atual][cidade_index], codigo_carta);
    strcpy(Dados_da_cidade->cidades[Dados_da_cidade->estado_atual][cidade_index], cidade_nome);
    Dados_da_cidade->cidades_por_estado[Dados_da_cidade->estado_atual]++;

    // Solicitando os dados adicionais da cidade

    // Solicitando a População com verificação
    printf("Digite a População (exemplo: 12324): ");
    while (scanf(" %d", &Dados_da_cidade->populacao[Dados_da_cidade->estado_atual][cidade_index]) != 1) {
        printf("\nEntrada INVÁLIDA! Por favor, digite um número válido\n\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        printf("Digite a População (exemplo: 12324): ");
    }
    // Solicita a área com verificação
    printf("Digite a Área em km2 (exemplo: 1000.25): ");
    while (scanf(" %f", &Dados_da_cidade->area[Dados_da_cidade->estado_atual][cidade_index]) != 1) {
        printf("\nEntrada INVÁLIDA! Por favor, digite um número válido\n\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        printf("Digite a Área em km2 (exemplo: 1000.25): ");
    }
    // Solicita o PIB com verificação
    printf("Digite o PIB (exemplo: 214453.00): ");
    while (scanf(" %lf", &Dados_da_cidade->PIB[Dados_da_cidade->estado_atual][cidade_index]) != 1) {
        printf("\nEntrada INVÁLIDA! Por favor, digite um número válido\n\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        printf("Digite o PIB (exemplo: 214453.00): ");
    }
    // Solicita os pontos turísticos com verificação
    printf("Digite quantos Pontos turísticos tem a cidade (exemplo: 5): ");
    while (scanf(" %d", &Dados_da_cidade->pontos_turisticos[Dados_da_cidade->estado_atual][cidade_index]) != 1) {
        printf("\nEntrada INVÁLIDA! Por favor, digite um número válido\n\n");
        while (getchar() != '\n'); // Limpa o buffer de entrada
        printf("Digite os Pontos turísticos (exemplo: 5): ");
    }

    // Calculando a densidade populacional
    Dados_da_cidade->Densidade_populacional[Dados_da_cidade->estado_atual][cidade_index] =
        (float)Dados_da_cidade->populacao[Dados_da_cidade->estado_atual][cidade_index] /
        Dados_da_cidade->area[Dados_da_cidade->estado_atual][cidade_index];
    // Calculando o PIB per capita
    Dados_da_cidade->PIB_per_capita[Dados_da_cidade->estado_atual][cidade_index] =
        Dados_da_cidade->PIB[Dados_da_cidade->estado_atual][cidade_index] /
        (float)Dados_da_cidade->populacao[Dados_da_cidade->estado_atual][cidade_index];

    Dados_da_cidade->num_cartas++; // Incrementa o contador de cartas e CARTA CADASTRADA
    // Mostrar os detalhes da carta cadastrada
    printf("\n======= Detalhes da carta cadastrada =======\n");
    printf("Código da carta: %s\n", Dados_da_cidade->codigo[Dados_da_cidade->estado_atual][cidade_index]);
    printf("Estado: %s\n", Dados_da_cidade->Estado_nome[Dados_da_cidade->estado_atual]);
    printf("Cidade: %s\n", Dados_da_cidade->cidades[Dados_da_cidade->estado_atual][cidade_index]);
    printf("População: %d\n", Dados_da_cidade->populacao[Dados_da_cidade->estado_atual][cidade_index]);
    printf("Área: %.2f km\n", Dados_da_cidade->area[Dados_da_cidade->estado_atual][cidade_index]);
    printf("Densidade populacional: %.2f\n", Dados_da_cidade->Densidade_populacional[Dados_da_cidade->estado_atual][cidade_index]);
    printf("PIB: %.2lf\n", Dados_da_cidade->PIB[Dados_da_cidade->estado_atual][cidade_index]);
    printf("PIB per capita: %.2f reais\n", Dados_da_cidade->PIB_per_capita[Dados_da_cidade->estado_atual][cidade_index]);
    printf("Pontos turísticos: %d\n", Dados_da_cidade->pontos_turisticos[Dados_da_cidade->estado_atual][cidade_index]);
    printf("============================================\n");
}

// Buscar carta por código
void buscar_carta_por_codigo(struct Carta *dados, const char *codigo) {
    int estado_index, cidade_index;

    if (encontrar_indices_carta(dados, codigo, &estado_index, &cidade_index)) {
        printf("\n======= Carta encontrada =======\n");
        printf("Código da carta: %s\n", codigo);
        printf("  Estado: %s\n", dados->Estado_nome[estado_index]);
        printf("  Cidade: %s\n", dados->cidades[estado_index][cidade_index]);
        printf("  População: %d\n", dados->populacao[estado_index][cidade_index]);
        printf("  Área: %.2f km\n", dados->area[estado_index][cidade_index]);
        printf("  Densidade populacional: %.2f\n", dados->Densidade_populacional[estado_index][cidade_index]);
        printf("  PIB: %.2lf\n", dados->PIB[estado_index][cidade_index]);
        printf("  PIB per capita: %.2f reais\n", dados->PIB_per_capita[estado_index][cidade_index]);
        printf("  Pontos turísticos: %d\n", dados->pontos_turisticos[estado_index][cidade_index]);
        printf("================================\n");
    } else {
        printf("\nCódigo inválido ou carta não encontrada.\n");
    }
}

// Seleciona carta para comparação
int selecionar_carta(struct Carta *cartas, char *carta, int posicao) {
    int estado_index, cidade_index;
    if (encontrar_indices_carta(cartas, carta, &estado_index, &cidade_index)) {
        // Armazena a carta na posição correspondente (0 para a primeira, 1 para a segunda)
        cartas->cartas_selecionadas[posicao][0] = estado_index;
        cartas->cartas_selecionadas[posicao][1] = cidade_index;

        buscar_carta_por_codigo(cartas, carta);
        return 1; // Retorna 1 indicando sucesso
    } else {
        printf("\nCarta não encontrada. TENTE NOVAMENTE.\n");
        return 0;  // Retorna 0 indicando falha
    }
}

// Lista todas as cartas cadastradas
void listar_cartas(struct Carta *informacoes) {
    printf("\n-------- Cartas Cadastradas --------\n");
    for (int i = 0; i < informacoes->num_estados; i++) {
        printf("\nEstado: %s\n", informacoes->Estado_nome[i]);
        for (int j = 0; j < informacoes->cidades_por_estado[i]; j++) {
            printf("  Código: %s | Cidade: %s\n", informacoes->codigo[i][j], informacoes->cidades[i][j]);
        }
    }
    printf("\nTotal de cartas cadastradas: %d\n", informacoes->num_cartas);
    printf("------------------------------------\n");
}

int main() {
    struct Carta Especificacoes_da_Carta = {0}; // Inicializando a struct com valores padrão
    int categoria_cadastro;
    int categoria_cartas, opcao_de_comparacao;

    do {
        // Exibição do menu
        printf("\n******* MENU PARA CADASTRO DE CARTAS *******\n\n");
        printf("1. Cadastrar carta\n");
        printf("2. Finalizar Cadastros e Começar o jogo\n");
        printf("\nDigite uma opção: ");

        // Verifica se a entrada é um número
        while (scanf(" %d", &categoria_cadastro) != 1) {
            printf("Entrada INVÁLIDA! Por favor, digite um número válido\n"); // Se não for um numero, mostra uma mensagem de erro e limpa a entrada
            printf("\nMENU PARA CADASTRO DE CARTAS\n");
            printf("1. Cadastrar carta\n");
            printf("2. Finalizar Cadastros e Começar o jogo\n");
            printf("\nDigite uma opção: ");
            while (getchar() != '\n'); // Limpa o buffer
        }

        switch (categoria_cadastro) {
            case 1: // 1. cadastrar carta
                adicionar_estado(&Especificacoes_da_Carta);
                adicionar_cidade(&Especificacoes_da_Carta);
                break;

            case 2:
                if (Especificacoes_da_Carta.num_cartas < 2) {//retorna ao cadastro
                    printf("CARTAS INSUFICIENTES PARA COMEÇAR O JOGO (MÍNIMO 2 CARTAS)\n"); // Verifica se o número de estados é insuficiente (mínimo de 2)
                } else {
                    printf("Cadastro finalizado. Iniciando o jogo...\n");
                    categoria_cadastro = 5; // Finaliza o cadastro e sai do loop
                }
                break;

            default:
                printf("OPÇÃO INVÁLIDA. TENTE NOVAMENTE.\n");
                break;
        }

    } while (categoria_cadastro != 5);

    do {//Comparacao das cartas
        // Exibicao do menu
        printf("\nSUPER TRUNFO\n");
        printf("1. Escolher as Cartas\n");
        printf("2. Sair do programa\n");
        printf("\nDigite uma opção: ");
         // Verifica se a entrada é um numero
        while (scanf(" %d", &categoria_cartas) != 1) {

            // Se não for um numero, mostra um erro e limpa o buffer
            printf("Entrada INVÁLIDA! Por favor, digite um número válido\n");

            printf("\nSUPER TRUNFO\n");
            printf("1. Escolher as Cartas\n");
            printf("2. Sair do programa\n");
            printf("\nDigite uma opção: ");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }
        switch(categoria_cartas){
            
            case 1: // Escolhendo as cartas
                listar_cartas(&Especificacoes_da_Carta);

                // Solicita o código da carta 1
                char carta_1[4];
                int carta_valida = 0;
                while (!carta_valida) {
                    printf("\nDigite o codigo da PRIMEIRA carta (ex: A01): ");
                    scanf(" %3s", carta_1);
                    carta_valida = selecionar_carta(&Especificacoes_da_Carta, carta_1, 0); //posicao [0]
                }

                // Solicita o código da carta 2
                char carta_2[4];
                carta_valida = 0;
                while (!carta_valida) {
                    listar_cartas(&Especificacoes_da_Carta);
                    printf("\nDigite o codigo da SEGUNDA carta (ex: A02): ");
                    scanf(" %3s", carta_2);
                    if (strcmp(carta_1, carta_2) == 0) {
                        printf("Você já escolheu essa carta. Digite um código diferente.\n");
                        continue; // volta ao início do loop
                }
                    carta_valida = selecionar_carta(&Especificacoes_da_Carta, carta_2, 1); //posicao [1]
            }
                // Simplificando as variaveis
                int e1 = Especificacoes_da_Carta.cartas_selecionadas[0][0];
                int c1 = Especificacoes_da_Carta.cartas_selecionadas[0][1];
                int e2 = Especificacoes_da_Carta.cartas_selecionadas[1][0];
                int c2 = Especificacoes_da_Carta.cartas_selecionadas[1][1];
                
                // Comparando as cartas
                printf("\nComparando:\n");
                printf("Carta %s - Estado: %s, Cidade: %s\n", carta_1, Especificacoes_da_Carta.Estado_nome[e1], Especificacoes_da_Carta.cidades[e1][c1]);
                printf("Carta %s - Estado: %s, Cidade: %s\n", carta_2, Especificacoes_da_Carta.Estado_nome[e2], Especificacoes_da_Carta.cidades[e2][c2]);
            
                // Escolhendo uma das propriedades para comparar
                printf("\nEscolha uma das propriedades numéricas para comparar:\n");
                printf("\n1. População\n");  
                printf("2. Área\n");
                printf("3. PIB\n");
                printf("4. Densidade populacional\n");
                printf("5. PIB per capita\n");
                printf("\nDigite uma opção: ");
                scanf(" %d", &opcao_de_comparacao);
                while (getchar() != '\n');

                switch (opcao_de_comparacao){
                    case 1: // Populacao
                    printf("Carta %s - Estado: %s, Cidade: %s, População: %d\n", carta_1, Especificacoes_da_Carta.Estado_nome[e1], Especificacoes_da_Carta.cidades[e1][c1], Especificacoes_da_Carta.populacao[e1][c1]);
                    printf("Carta %s - Estado: %s, Cidade: %s, População: %d\n", carta_2, Especificacoes_da_Carta.Estado_nome[e2], Especificacoes_da_Carta.cidades[e2][c2], Especificacoes_da_Carta.populacao[e2][c2]);
                    printf("Resultado: %s\n", Especificacoes_da_Carta.populacao[e1][c1] > Especificacoes_da_Carta.populacao[e2][c2] ? "Carta 1 é a vencedora!" : (Especificacoes_da_Carta.populacao[e1][c1] < Especificacoes_da_Carta.populacao[e2][c2] ? "Carta 2 é a vencedora!" : "Empate"));
                    break;

                    case 2: // Área
                    printf("Carta %s - Estado: %s, Cidade: %s, Área: %.2f\n", carta_1, Especificacoes_da_Carta.Estado_nome[e1], Especificacoes_da_Carta.cidades[e1][c1], Especificacoes_da_Carta.area[e1][c1]);
                    printf("Carta %s - Estado: %s, Cidade: %s, Área: %.2f\n", carta_2, Especificacoes_da_Carta.Estado_nome[e2], Especificacoes_da_Carta.cidades[e2][c2], Especificacoes_da_Carta.area[e2][c2]);
                    printf("Resultado: %s\n", Especificacoes_da_Carta.area[e1][c1] > Especificacoes_da_Carta.area[e2][c2] ? "Carta 1 é a vencedora!" : (Especificacoes_da_Carta.area[e1][c1] < Especificacoes_da_Carta.area[e2][c2] ? "Carta 2 é a vencedora!" : "Empate"));
                    break;

                    case 3: // PIB
                    printf("Carta %s - Estado: %s, Cidade: %s, PIB: %.2lf\n", carta_1, Especificacoes_da_Carta.Estado_nome[e1], Especificacoes_da_Carta.cidades[e1][c1], Especificacoes_da_Carta.PIB[e1][c1]);
                    printf("Carta %s - Estado: %s, Cidade: %s, PIB: %.2lf\n", carta_2, Especificacoes_da_Carta.Estado_nome[e2], Especificacoes_da_Carta.cidades[e2][c2], Especificacoes_da_Carta.PIB[e2][c2]);
                    printf("Resultado: %s\n", Especificacoes_da_Carta.PIB[e1][c1] > Especificacoes_da_Carta.PIB[e2][c2] ? "Carta 1 é a vencedora!" : (Especificacoes_da_Carta.PIB[e1][c1] < Especificacoes_da_Carta.PIB[e2][c2] ? "Carta 2 é a vencedora!" : "Empate"));
                    break;

                    case 4: // Densidade populacional
                    printf("Carta %s - Estado: %s, Cidade: %s, Densidade populacional: %.2f\n", carta_1, Especificacoes_da_Carta.Estado_nome[e1], Especificacoes_da_Carta.cidades[e1][c1], Especificacoes_da_Carta.Densidade_populacional[e1][c1]);
                    printf("Carta %s - Estado: %s, Cidade: %s, Densidade populacional: %.2f\n", carta_2, Especificacoes_da_Carta.Estado_nome[e2], Especificacoes_da_Carta.cidades[e2][c2], Especificacoes_da_Carta.Densidade_populacional[e2][c2]);
                    printf("Resultado: %s\n", Especificacoes_da_Carta.Densidade_populacional[e1][c1] > Especificacoes_da_Carta.Densidade_populacional[e2][c2] ? "Carta 2 é a vencedora!" : (Especificacoes_da_Carta.Densidade_populacional[e1][c1] < Especificacoes_da_Carta.Densidade_populacional[e2][c2] ? "Carta 1 é a vencedora!" : "Empate"));
                    break;

                    case 5: // PIB per capita
                    printf("Carta %s - Estado: %s, Cidade: %s, PIB per capita: %.2f\n", carta_1, Especificacoes_da_Carta.Estado_nome[e1], Especificacoes_da_Carta.cidades[e1][c1], Especificacoes_da_Carta.PIB_per_capita[e1][c1]);
                    printf("Carta %s - Estado: %s, Cidade: %s, PIB per capita: %.2f\n", carta_2, Especificacoes_da_Carta.Estado_nome[e2], Especificacoes_da_Carta.cidades[e2][c2], Especificacoes_da_Carta.PIB_per_capita[e2][c2]);
                    printf("Resultado: %s\n", Especificacoes_da_Carta.PIB_per_capita[e1][c1] > Especificacoes_da_Carta.PIB_per_capita[e2][c2] ? "Carta 1 é a vencedora!" : (Especificacoes_da_Carta.PIB_per_capita[e1][c1] < Especificacoes_da_Carta.PIB_per_capita[e2][c2] ? "Carta 2 é a vencedora!" : "Empate"));
                    break;

                default:
                    printf("OPÇÃO INVÁLIDA.\n");
                    break;
            }
        }

    }while (categoria_cartas != 2);
    
    return 0;
}
