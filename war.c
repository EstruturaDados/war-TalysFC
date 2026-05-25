//NÍVEL INICIANTE DO DESAFIO

#include <stdio.h>
#include <string.h>

// Define a quantidade máxima de territórios
#define MAX_TERRITORIOS 5

// Struct que armazena as informações de cada território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {

    // Variável que controla a quantidade de territórios cadastrados
    int total_territorios = 0;

    // Vetor de structs para armazenar os territórios
    struct Territorio territorios[MAX_TERRITORIOS];


    printf("-- Bem vindo ao jogo War! --\n");
    printf("Vamos começar criando seus territórios:\n");

    // Enquanto ainda houver espaço para cadastrar territórios
    while (total_territorios < MAX_TERRITORIOS) {

        printf("\n-- Território %d --\n", total_territorios + 1);

        // Entrada do nome do território
        printf("Digite o nome do território: ");
        scanf("%s", territorios[total_territorios].nome);

        // Entrada da cor do território
        printf("Digite a cor do território: ");
        scanf("%s", territorios[total_territorios].cor);

        // Entrada da quantidade de tropas
        printf("Digite o número de tropas do território: ");
        scanf("%d", &territorios[total_territorios].tropas);

        // Incrementa a quantidade de territórios cadastrados
        total_territorios++;
    }

    // Exibição dos territórios cadastrados
    printf("\n=== TERRITÓRIOS CADASTRADOS ===\n");

    for (int i = 0; i < total_territorios; i++) {

        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}

