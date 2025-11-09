
// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO (Nível novato)
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, e manipulação de strings.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct territorio {
    int id;
    char nome[30];
    char cor[10];
    int tropa;
};

// Variáveis globais
int inicio = 0;
int count = 0;
struct territorio* mapa_mundi = NULL;

// Protótipos
struct territorio* aloca_territorios_calloc(int tamanho);
void limpar_buffer(void);
void menu(void);
void inicializarTerritorios(void);
void exibirMapa(void);
void atacar(int atacante_idx, int defensor_idx);

// Função para alocar memória dinamicamente para um array de territórios usando calloc
struct territorio* aloca_territorios_calloc(int tamanho) {
    // Aloca (tamanho) blocos de memória, cada um do tamanho de Territorio,
    // e inicializa todos os bytes com 0.
    struct territorio* mapa = (struct territorio*) calloc(tamanho, sizeof(struct territorio));
    
    // Verifica se a alocação foi bem-sucedida
    if (mapa == NULL) {
        perror("Erro ao alocar memória com calloc");
    }
    
    return mapa;
}

// Função para limpar o buffer de entrada
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para chamar outras funções com base na escolha do usuario
void menu(void){
    int opcao;
    printf("=========== INICIANDO ===========\n");
    printf("1. Começar jogo\n");
    printf("2. Sair do jogo\n");
    if (inicio > 0) {
        printf("3. Voltar pro jogo\n");
    }
    printf("=================================\n");

    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1) {
        limpar_buffer();
        printf("Entrada inválida.\n");
        return;
    }

    printf("\n");

    switch (opcao) {
        case 1:
            inicio = 1;
            inicializarTerritorios();
            break;
        case 2:
            printf("Saindo do jogo...\n");
            break;
        case 3:
            if (inicio > 0) {
                exibirMapa();
            } else {
                printf("Opção inválida. Tente novamente.\n");
                menu();
            }
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            menu();
            break;
    }
}

// Função pra pedir pro usuario criar os territórios e alocar memporia dinamicamente
void inicializarTerritorios(void){
    int n_territorios;
    printf("Informe o número de territórios no jogo: ");
    if (scanf("%d", &n_territorios) != 1 || n_territorios <= 0) {
        limpar_buffer();
        printf("Entrada inválida.\n");
        return;
    }

    // libera memória anterior, se houver
    if (mapa_mundi != NULL) {
        free(mapa_mundi);
        mapa_mundi = NULL;
        count = 0;
    }

    mapa_mundi = aloca_territorios_calloc(n_territorios);

    if (mapa_mundi != NULL) {
        printf("\nMemória para %d territórios alocada com sucesso usando calloc.\n", n_territorios);
        printf("\n");
    } else {
        return;
    }

    limpar_buffer();

    while (count < n_territorios) {
        printf("Digite o nome do território: ");
        if (scanf("%29s", mapa_mundi[count].nome) != 1) {
            limpar_buffer();
            printf("Entrada inválida para nome.\n");
            continue;
        }

        printf("Digite a cor do território: ");
        if (scanf("%9s", mapa_mundi[count].cor) != 1) {
            limpar_buffer();
            printf("Entrada inválida para cor.\n");
            continue;
        }

        printf("Digite o numero de tropas do território: ");
        if (scanf("%d", &mapa_mundi[count].tropa) != 1) {
            limpar_buffer();
            printf("Entrada inválida para tropas.\n");
            continue;
        }
        printf("\n");

        mapa_mundi[count].id = count + 1;
        count++;
    }

    exibirMapa();
}

// Função pra exibir todos os territórios no terminal
void exibirMapa(void){
    if (count == 0 || mapa_mundi == NULL) {
        printf("Nenhum território cadastrado.\n");
        return;
    }

    printf("=================================\n");
    printf("       MAPA - ESTADO ATUAL       \n");
    printf("=================================\n");

    for (int i = 0 ; i < count; i++) {
        printf("%d. %s (Exército %s, Tropas: %d)\n", i+1, mapa_mundi[i].nome, mapa_mundi[i].cor, mapa_mundi[i].tropa);
    }
    printf("\n");

    int mesma_cor = 1;
    for (int i = 1; i < count; i++) {
        if (strcmp(mapa_mundi[0].cor, mapa_mundi[i].cor) != 0) {
            mesma_cor = 0;
            break;
        }
    }
    if (mesma_cor && count > 0) {
        printf("parabens, exercito %s você conquistou o mundo!\n", mapa_mundi[0].cor);
        menu();
        
    }

    int opcao;
    printf("========= MENU DE AÇÕES =========\n");
    printf("1. atacar\n");
    printf("2. voltar pro menu inicial\n");
    printf("3. sair do jogo\n");
    printf("=================================\n");

    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1) {
        limpar_buffer();
        printf("Entrada inválida.\n");
        return;
    }

    switch (opcao) {
        case 1: {
            int at, df;
            printf("Escolha o número do território atacante: ");
            if (scanf("%d", &at) != 1) { limpar_buffer(); printf("Entrada inválida.\n"); break; }
            printf("Escolha o número do território defensor: ");
            if (scanf("%d", &df) != 1) { limpar_buffer(); printf("Entrada inválida.\n"); break; }
            atacar(at - 1, df - 1);
            break;
        }
        case 2:
            menu();
            break;
        case 3:
            printf("Saindo do jogo...\n");
            break;
        default:
            printf("Opção inválida. Tente novamente.\n");
            exibirMapa();
            break;
    }
}

// Função para simular um ataque entre dois territórios
void atacar(int atacante_idx, int defensor_idx) {
    if (mapa_mundi == NULL) {
        printf("Mapa não inicializado.\n");
        return;
    }
    if (atacante_idx < 0 || atacante_idx >= count || defensor_idx < 0 || defensor_idx >= count) {
        printf("Índices inválidos de territórios.\n");
        return;
    }
    if (atacante_idx == defensor_idx) {
        printf("Um território não pode atacar a si mesmo.\n");
        return;
    }

    struct territorio *atacante = &mapa_mundi[atacante_idx];
    struct territorio *defensor = &mapa_mundi[defensor_idx];

    printf("\n--- Combate ---\n");
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;
    printf("%s rolou %d e %s rolou %d\n", atacante->nome, dado_atacante, defensor->nome, dado_defensor);

    // Compara os resultados e diminui as tropas conforme o resultado
    if (dado_atacante > dado_defensor) {
        printf("Ataque bem sucedido\n");
        // Reduz a força militar do defensor por causa da falha
        if (defensor->tropa > 0) {
            defensor->tropa -= 1;
            // Passa o território para o atacante se o defensor ficar sem tropas
            if (defensor->tropa <= 0) {
                defensor->tropa = 0;
                strncpy(defensor->cor, atacante->cor, sizeof(defensor->cor) - 1);
                defensor->cor[sizeof(defensor->cor)-1] = '\0';
                printf("%s conquistado por %s\n", defensor->nome, atacante->nome);
            }
        }
        } else {
            printf("%s se defendeu com sucesso!\n", defensor->nome);  
            }
    exibirMapa();
}

int main(void) {
    // Seta o idioma pra portugues pra exibir caracteres como "ç" por exemplo
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Semente para números aleatórios e inicialização dela
    static int seeded = 0;
    if (!seeded) {
        srand((unsigned int)time(NULL));
        seeded = 1;
    }

    //Função pra chamar outras funções
    menu();

    if (mapa_mundi != NULL) {
        free(mapa_mundi);
        mapa_mundi = NULL;
        printf("memória liberada com sucesso\n");
    } else {
        printf("Nenhuma memória para liberar.\n");
    }

    return 0;
}
