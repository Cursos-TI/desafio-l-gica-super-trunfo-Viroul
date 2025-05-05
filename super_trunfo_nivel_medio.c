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
    char Estado_nome[8][50];            // Nome do estado (máximo de 8 estados)
    char cidades[8][4][50];             // Até 4 cidades por estado
    int populacao[8][4];                // População de cada cidade
    float area[8][4];                   // Área de cada cidade
    float Densidade_populacional[8][4]; // Densidade populacional de cada cidade
    float PIB_per_capita[8][4];         // PIB per capita de cada cidade
    double PIB[8][4];                   // PIB da cidade
    int pontos_turisticos[8][4];        // Pontos turísticos da cidade

};

// Gera o código para um estado e uma cidade
void gerar_codigo(char *codigo, int estado_index, int cidade_index) {
    sprintf(codigo, "%c%02d", 'A' + estado_index, cidade_index + 1);
}

// Exibe todas as cartas cadastradas com seus códigos
void listar_cartas(struct Carta *informacoes) {
    printf("\n--------Cartas Cadastradas--------\n");
    for (int i = 0; i < informacoes->num_estados; i++) {
        printf("\nEstado %c:\n", 'A' + i);
        for (int j = 0; j < informacoes->cidades_por_estado[i]; j++) {
            char codigo[4];
            gerar_codigo(codigo, i, j);
            printf("Código da carta: %s\n", codigo);
        }
    }
    // Exibe o total de cartas cadastradas
    printf("\nTotal de cartas cadastradas: %d\n", informacoes->num_cartas);
    printf("----------------------------------");
}

// Verificar se a carta existe
int verificar_carta_existente(struct Carta *dados, const char *codigo) {
    int estado_index = codigo[0] - 'A';      // Converte a letra em um indice do estado
    int cidade_index = (codigo[1] - '0') * 10 + (codigo[2] - '0') - 1; // Converte os digitos da cidade

    // Verifica se o código esta entre 01 e 04
    if (cidade_index < 0 || cidade_index >= 4) {
        printf("\nCódigo de cidade inválido. O código deve ser de 01 a 04.\n");
        return 0; // Carta não encontrada
    }

    if (estado_index >= 0 && estado_index < dados->num_estados &&
        cidade_index >= 0 && cidade_index < dados->cidades_por_estado[estado_index]) {
        return 1; // Carta encontrada
    } else {
        return 0; // Carta não encontrada
    }
}

// Verifica se o estado já existe
int estado_existente(struct Carta *verificar_estado, const char *estado_nome) {
    // Verifica se o estado já foi cadastrado
    for (int i = 0; i < verificar_estado->num_estados; i++) {
        if (strcmp(verificar_estado->Estado_nome[i], estado_nome) == 0) {
            verificar_estado->estado_atual = i;  // Define o índice do estado existente como o atual
            return 1;  // Estado encontrado
        }
    }
    return 0;  // Estado não encontrado
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

// Cadastro de um estado
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

// Cadastro de uma cidade
void adicionar_cidade(struct Carta *Dados_da_cidade) {
    if (Dados_da_cidade->cidades_por_estado[Dados_da_cidade->estado_atual] >= 4) {
        printf("Limite de cidades para este estado atingido.\n");
        return;
    }
    char cidade_nome[50]; //variavel
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
    strcpy(Dados_da_cidade->cidades[Dados_da_cidade->estado_atual][cidade_index], cidade_nome);
    Dados_da_cidade->cidades_por_estado[Dados_da_cidade->estado_atual]++;
    
    // Solicita os dados adicionais da cidade

    // Solicitando a População com verificação
    printf("Digite a População (exemplo: 12324): ");
    while(scanf(" %d", &Dados_da_cidade->populacao[Dados_da_cidade->estado_atual][cidade_index]) != 1) {
        printf("\nEntrada INVÁLIDA! Por favor, digite um número válido\n\n");
        while (getchar() != '\n');  // Limpa o buffer de entrada
        printf("Digite a População (exemplo: 12324): ");
    }

    // Solicita a área com verificação
    printf("Digite a Área em km2 (exemplo: 1000.25): ");
    while(scanf(" %f", &Dados_da_cidade->area[Dados_da_cidade->estado_atual][cidade_index]) != 1) {
        printf("\nEntrada INVÁLIDA! Por favor, digite um número válido para a área\n\n");
        while (getchar() != '\n');  // Limpa o buffer de entrada
        printf("Digite a Área em km2 (exemplo: 1000.25): ");
    }

    // Solicita o PIB com verificação
    printf("Digite o PIB (exemplo: 214453.00): ");
    while(scanf(" %lf", &Dados_da_cidade->PIB[Dados_da_cidade->estado_atual][cidade_index]) != 1) {
        printf("\nEntrada INVÁLIDA! Por favor, digite um número válido para o PIB\n\n");
        while (getchar() != '\n');  // Limpa o buffer de entrada
        printf("Digite o PIB (exemplo: 214453.00): ");
    }

    // Solicita os pontos turísticos com verificação
    printf("Digite quantos Pontos turísticos tem a cidade (exemplo: 5): ");
    while(scanf(" %d", &Dados_da_cidade->pontos_turisticos[Dados_da_cidade->estado_atual][cidade_index]) != 1) {
        printf("\nEntrada INVÁLIDA! Por favor, digite um número válido para os pontos turísticos\n\n");
        while (getchar() != '\n');  // Limpa o buffer de entrada
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

    //CARTA CADASTRADA
    // Incrementa o contador de cartas
    Dados_da_cidade->num_cartas++;
    
    // Mostrar os detalhes da carta cadastrada
    char codigo[4];
    gerar_codigo(codigo, Dados_da_cidade->estado_atual, cidade_index);

    printf("\n=======Detalhes da carta cadastrada=======\n");
    printf("\nCódigo da carta: %s\n", codigo);
    printf("  Estado: %s\n", Dados_da_cidade->Estado_nome[Dados_da_cidade->estado_atual]);
    printf("  Cidade: %s\n", Dados_da_cidade->cidades[Dados_da_cidade->estado_atual][cidade_index]);
    printf("  População: %d\n", Dados_da_cidade->populacao[Dados_da_cidade->estado_atual][cidade_index]);
    printf("  Área: %.2f km2\n", Dados_da_cidade->area[Dados_da_cidade->estado_atual][cidade_index]);
    printf("  Densidade populacional: %.2f pessoas por km2\n", Dados_da_cidade->Densidade_populacional[Dados_da_cidade->estado_atual][cidade_index]);
    printf("  PIB: %.2lf\n", Dados_da_cidade->PIB[Dados_da_cidade->estado_atual][cidade_index]);
    printf("  PIB per capita: %.2f reais\n", Dados_da_cidade->PIB_per_capita[Dados_da_cidade->estado_atual][cidade_index]);
    printf("  Pontos turísticos: %d\n", Dados_da_cidade->pontos_turisticos[Dados_da_cidade->estado_atual][cidade_index]);
    printf("\n      Carta cadastrada com sucesso!\n");
    printf("\n===========================================\n");
    
    

}

// Buscar carta por código e verificação de código da cidade
void buscar_carta_por_codigo(struct Carta *dados, const char *codigo) {
    
    int carta_encontrada = 0;

    do {
        if (verificar_carta_existente(dados, codigo)) {
        // exibe os detalhes
        int estado_index = codigo[0] - 'A';      // Converte a letra em índice do estado
        int cidade_index = (codigo[1] - '0') * 10 + (codigo[2] - '0') - 1; // Converte os dígitos da cidade

        printf("\n=======Carta encontrada=======\n"); // ADICIONAR DENSIDADE E PIB PER CAPITA CONSERTAAAAAAAAAAAAAAAAAAAAAAAA
        printf("Código da carta: %s\n", codigo);
        printf("  Estado: %s\n", dados->Estado_nome[estado_index]);
        printf("  Cidade: %s\n", dados->cidades[estado_index][cidade_index]);
        printf("  População: %d\n", dados->populacao[estado_index][cidade_index]);
        printf("  Área: %.2f km2\n", dados->area[estado_index][cidade_index]);
        printf("  Densidade populacional: %.2f pessoas por km2\n", dados->Densidade_populacional[estado_index][cidade_index]);
        printf("  PIB: %.2lf\n", dados->PIB[estado_index][cidade_index]);
        printf("  PIB per capita: %.2f reais\n", dados->PIB_per_capita[estado_index][cidade_index]);
        printf("  Pontos turísticos: %d\n", dados->pontos_turisticos[estado_index][cidade_index]);
        printf("=============================\n");
        
        carta_encontrada = 1;
        
    } else {
        printf("\nCódigo inválido ou carta não encontrada.\n");
    } 
} while (!carta_encontrada);
}

// Seleciona as cartas para o supertrunfo
int selecionar_carta(struct Carta *cartas, char *carta, int posicao) {
    if (verificar_carta_existente(cartas, carta)) {
        int estado_index = carta[0] - 'A';  // Converte letra para índice do estado
        int cidade_index = (carta[1] - '0') * 10 + (carta[2] - '0') - 1;  // Converte os dígitos da cidade

        // Armazena a carta na posição correspondente (0 para a primeira, 1 para a segunda)
        cartas->cartas_selecionadas[posicao][0] = estado_index;
        cartas->cartas_selecionadas[posicao][1] = cidade_index;

        buscar_carta_por_codigo(cartas, carta);
        return 1;  // Retorna 1 indicando sucesso
    } else {
        printf("\nCarta não encontrada. TENTE NOVAMENTE.\n");
        return 0;  // Retorna 0 indicando falha
    }
}

int main() {
    struct Carta Especificacoes_da_Carta = {0}; // Inicializando a struct com valores padrão
    int categoria_cadastro, opcao_estado;
    int categoria_cartas, opcao_de_comparacao;
   
    do {// Cadastro de cartas
        // Exibicao do menu
        printf("\n******* MENU PARA CADASTRO DE CARTAS *******\n\n");
        printf("1. Cadastrar Estado\n");
        printf("2. Cadastrar Cidade\n");
        printf("3. Finalizar Cadastros e Começar o jogo\n");
        printf("\nDigite uma opção: ");
         // Verifica se a entrada é um numero
        while (scanf(" %d", &categoria_cadastro) != 1) {

            // Se não for um numero, mostra uma mensagem de erro e limpa a entrada
            printf("Entrada INVÁLIDA! Por favor, digite um número válido\n");

            printf("\nMenu para cadastro de cartas\n");
            printf("1. Cadastrar Estado\n");
            printf("2. Cadastrar Cidade\n");
            printf("3. Finalizar Cadastros e Começar o jogo\n");
            printf("\nDigite uma opção: ");
            while (getchar() != '\n'); // Limpa o buffer de entrada
        }

        switch (categoria_cadastro) {
        case 1: // 1. Cadastrar estado
            adicionar_estado(&Especificacoes_da_Carta);

            // Escolhe se criará uma cidade no estado que esta sendo cadastrado
            printf("\n1. Cadastrar uma cidade neste estado\n");  
            printf("2. voltar para o menu\n");
            printf("\nDigite uma opção: ");
            while (scanf(" %d", &opcao_estado) != 1){
                
                // Se não for um numero, mostra uma mensagem de erro e limpa a entrada
                printf("Entrada INVÁLIDA! Por favor, digite um número válido\n");
                
                printf("\n1. Cadastrar uma cidade neste estado\n");  
                printf("2. voltar para o menu\n");
                printf("\nDigite uma opção: ");
                while (getchar() != '\n');
            }

            switch (opcao_estado){ // ADICIONA UMA CIDADE
                case 1: // 1. cadastrar uma cidade no estado atual
                    adicionar_cidade(&Especificacoes_da_Carta);
                    break;  // Evita que continue para o próximo 'case'
                    
                case 2: // 2. Voltar para o menu principal
                    break;
                default:
                    printf("OPÇÃO INVÁLIDA.\n");
            }
            break; // ESTADO CADASTRADO COM SUCESSO

        case 2: // 2. cadastrar cidade
            if (Especificacoes_da_Carta.num_estados == 0) { // Verifica se há estado cadastrado 
                printf("\nNenhum estado cadastrado.\n");
                break;
            } else { // Escolhe o estado para cadastrar a cidade
                printf("\nESCOLHA UM ESTADO PARA CADASTRAR A CIDADE\n\nCADASTRADOS:\n");
                for (int i = 0; i < Especificacoes_da_Carta.num_estados; i++) {
                    printf("Estado %c\n\n", 'A' + i);
                    }
                char letra;
                printf("\nDigite uma opção: ");
                scanf(" %c", &letra);  // Leitura da escolha do estado

                letra = toupper(letra); // Converter para maiúscula

                // Verificar se é uma letra válida antes de converter para índice
                if (letra < 'A' || letra >= 'A' + Especificacoes_da_Carta.num_estados) {
                    printf("OPÇÃO INVÁLIDA! Escolha entre A e %c.\n", 'A' + Especificacoes_da_Carta.num_estados - 1);
                
                } else {
                    int indice = letra - 'A';  // Converter a letra para índice numérico
                    Especificacoes_da_Carta.estado_atual = indice;
                    adicionar_cidade(&Especificacoes_da_Carta);
                }
            }
            break;

        case 3: //finaliza os cadastros
            if (Especificacoes_da_Carta.num_cartas < 2) {
                // Verifica se o número de estados é insuficiente (mínimo de 2)
                printf("CARTAS INSUFICIENTES PARA COMEÇAR O JOGO (MÍNIMO 2 CARTAS)\n");
                //retorna ao cadastro
            } else{
                printf("cadastro finalizado.\n");
                // Finaliza o cadastro e sai do loop
                categoria_cadastro = 5;
                break;
            }
            break;

        default:
            printf("OPÇÃO INVÁLIDA. TENTE NOVAMENTE.\n");
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
                    carta_1[0] = toupper(carta_1[0]);
                    carta_valida = selecionar_carta(&Especificacoes_da_Carta, carta_1, 0); //posicao [0]
                }

                // Solicita o código da carta 2
                char carta_2[4];
                carta_valida = 0;
                while (!carta_valida) {
                    listar_cartas(&Especificacoes_da_Carta);
                    printf("\nDigite o codigo da SEGUNDA carta (ex: A02): ");
                    scanf(" %3s", carta_2);
                    carta_2[0] = toupper(carta_2[0]);
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
