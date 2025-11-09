// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO (Nível novato)
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, e manipulação de strings.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.
struct territorio {
char nome[30];
char cor[10];
int tropa;
};

// Variáveis globais
int count = 0;
struct territorio mapa_mundi[5];

// Função pra pedir pro usuario criar os territórios com caracteristicas que ele vai decidir
void inicializarTerritorios(){
    do {
        printf("Digite o nome do território: ");
        scanf("%s", mapa_mundi[count].nome);

        printf("Digite a cor do território: ");
        scanf("%s", mapa_mundi[count].cor);

        printf("Digite o numero de tropas do território: ");
        scanf("%d", &mapa_mundi[count].tropa);
        printf("\n");
        count++;
    } while ( count < 5 );
}

// Função pra exibir todos os territórios no terminal
void exibirMapa(){
    printf ("Mapa: ");
    printf("\n");

    for (int i = 0 ; i < count; i++) {
        printf ("%d° territorio: \n",i+1);
        printf ("Nome: %s\n", mapa_mundi[i].nome);
        printf ("Cor: %s\n", mapa_mundi[i].cor);
        printf ("Tropas: %d\n", mapa_mundi[i].tropa);
        printf("\n");
    }
}

int main() {

    // Seta o idioma pra portugues pra exibir caracteres como "ç" por exemplo
    setlocale(LC_ALL, "pt_BR.UTF-8");

    //Chamando as funções
    inicializarTerritorios();
    exibirMapa();

    return 0;
}
