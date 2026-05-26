// NÍVEL AVENTUREIRO DO DESAFIO

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Struct que armazena as informações do território
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

// Função responsável pela batalha
void Atacar(struct Territorio *atacante, struct Territorio *defensor) {

    int resultado_ataque = rand() % 6 + 1;
    int resultado_defesa = rand() % 6 + 1;

    printf("\n-- RESULTADO DA BATALHA --\n");
    printf("Dado do atacante: %d\n", resultado_ataque);
    printf("Dado do defensor: %d\n", resultado_defesa);

    // Atacante venceu
    if (resultado_ataque > resultado_defesa) {

        printf("\nO atacante venceu a batalha!\n");

        // Defensor perde uma tropa
        defensor->tropas--;

        printf("O território defensor perdeu 1 tropa.\n");

        // Verifica se o defensor perdeu todas as tropas
        if (defensor->tropas <= 0) {

            printf("\nO território foi conquistado!\n");

            // Troca a cor do território
            strcpy(defensor->cor, atacante->cor);

            // Move uma tropa para o território conquistado
            defensor->tropas = 1;

            // Remove uma tropa do atacante
            atacante->tropas--;

            printf("O território agora pertence ao exército %s.\n",
                   defensor->cor);
        }

    // Defensor venceu
    } else if (resultado_ataque < resultado_defesa) {

        printf("\nO defensor venceu a batalha!\n");

        // Atacante perde uma tropa
        atacante->tropas--;

        printf("O território atacante perdeu 1 tropa.\n");

    } else {

        printf("\nEmpate! Nenhuma tropa foi perdida.\n");
    }
}

int main() {

    srand(time(NULL));

    int numero_territorios;
    int total_territorios = 0;

    int opcao_ataque;
    int opcao_defesa;

    printf("-- Bem vindo ao jogo War! --\n");

    // Quantidade de territórios
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &numero_territorios);

    // Alocação dinâmica
    struct Territorio *territorios;

    territorios = malloc(numero_territorios * sizeof(struct Territorio));

    // Verifica erro no malloc
    if (territorios == NULL) {

        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro dos territórios
    while (total_territorios < numero_territorios) {

        printf("\n-- Território %d --\n",
               total_territorios + 1);

        printf("Nome: ");
        scanf("%s", territorios[total_territorios].nome);

        printf("Cor: ");
        scanf("%s", territorios[total_territorios].cor);

        printf("Tropas: ");
        scanf("%d", &territorios[total_territorios].tropas);

        total_territorios++;
    }

    // LOOP PRINCIPAL DO JOGO
    while (1) {

        // Mostra os territórios atualizados
        printf("\n-- Mapa Atual: --\n");

        for (int i = 0; i < numero_territorios; i++) {

            printf("\n[%d] %s\n", i + 1,
                   territorios[i].nome);

            printf("Cor: %s\n",
                   territorios[i].cor);

            printf("Tropas: %d\n",
                   territorios[i].tropas);
        }

        // Escolha do atacante
        printf("\nDigite o território atacante (0 para sair): ");
        scanf("%d", &opcao_ataque);

        // Encerra o jogo
        if (opcao_ataque == 0) {

            printf("\nEncerrando o jogo...\n");
            break;
        }

        // Escolha do defensor
        printf("Digite o território defensor: ");
        scanf("%d", &opcao_defesa);

        // Ajusta para índice do vetor
        opcao_ataque--;
        opcao_defesa--;

        // Validação
        if (opcao_ataque < 0 ||
            opcao_ataque >= numero_territorios ||
            opcao_defesa < 0 ||
            opcao_defesa >= numero_territorios) {

            printf("\nTerritório inválido!\n");
            continue;
        }

        // Impede ataque ao próprio território
        if (opcao_ataque == opcao_defesa) {

            printf("\nUm território não pode atacar ele mesmo!\n");
            continue;
        }

        // Impede ataque aliado
        if (strcmp(territorios[opcao_ataque].cor,
                   territorios[opcao_defesa].cor) == 0) {

            printf("\nVocê não pode atacar um território aliado!\n");
            continue;
        }

        // Verifica tropas suficientes
        if (territorios[opcao_ataque].tropas <= 1) {

            printf("\nO atacante precisa ter mais de 1 tropa!\n");
            continue;
        }

        // Realiza o ataque
        Atacar(&territorios[opcao_ataque],
                &territorios[opcao_defesa]);
    }

    // Libera memória
    free(territorios);

    return 0;
}
