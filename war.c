// NÍVEL MESTRE DO DESAFIO

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

// Vetor de missões do jogo
char *missoes[] = {
    "Conquistar 3 territórios.",
    "Eliminar exército vermelho.",
    "Conquistar 5 territórios.",
    "Eliminar exército azul.",
    "Conquistar 2 territórios."
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
        // Defensor perde 1 tropa
        defensor->tropas--;
        printf("O território defensor perdeu 1 tropa.\n");
        // Verifica se o território foi conquistado
        if (defensor->tropas <= 0) {
            printf("\nO território foi conquistado!\n");
            // Troca a cor do território
            strcpy(defensor->cor, atacante->cor);
            // Calcula metade das tropas do atacante
            int tropas_transferidas = atacante->tropas / 2;
            // Garante pelo menos 1 tropa
            if (tropas_transferidas < 1) {
                tropas_transferidas = 1;
            }
            // Move tropas para o território conquistado
            defensor->tropas = tropas_transferidas;
            // Remove tropas do atacante
            atacante->tropas -= tropas_transferidas;
            printf("O território agora pertence ao exército %s.\n", defensor->cor);
        }

    // Defensor venceu
    } else if (resultado_ataque < resultado_defesa) {
        printf("\nO defensor venceu a batalha!\n");
        // Atacante perde 1 tropa
        atacante->tropas--;
        printf("O território atacante perdeu 1 tropa.\n");
    } else {
        printf("\nEmpate! Nenhuma tropa foi perdida.\n");
    }
}

// Sorteia uma missão para o jogador
void atribuirMissao(char *destino, char* listaMissoes[], int totalMissoes) {
    int sorteio = rand() % totalMissoes;
    strcpy(destino, listaMissoes[sorteio]);
}

// Exibe a missão do jogador
void exibirMissao(char *missao) {
    printf("\n===== SUA MISSÃO =====\n");
    printf("%s\n", missao);
}

// Verifica se a missão foi cumprida
int verificarMissao(char *missao, struct Territorio *mapa, int tamanho) {
    int contadorAzul = 0;
    int contadorVermelho = 0;
    int totalTerritorios = 0;

    // Percorre todos os territórios
    for (int i = 0; i < tamanho; i++) {
        // Conta territórios AZUIS
        if (strcmp(mapa[i].cor, "AZUL") == 0) {
            contadorAzul++;
        }
        // Conta territórios VERMELHOS
        if (strcmp(mapa[i].cor, "VERMELHO") == 0) {
            contadorVermelho++;
        }
        // Conta territórios do jogador AZUL
        if (strcmp(mapa[i].cor, "AZUL") == 0) {
            totalTerritorios++;
        }
    }
    // Missão: conquistar 2 territórios
    if (strcmp(missao, "Conquistar 2 territórios.") == 0) {
        if (totalTerritorios >= 2) {
            return 1;
        }
    }
    // Missão: conquistar 3 territórios
    if (strcmp(missao, "Conquistar 3 territórios.") == 0) {
        if (totalTerritorios >= 3) {
            return 1;
        }
    }
    // Missão: conquistar 5 territórios
    if (strcmp(missao, "Conquistar 5 territórios.") == 0) {
        if (totalTerritorios >= 5) {
            return 1;
        }
    }
    // Missão: eliminar exército vermelho
    if (strcmp(missao, "Eliminar exército vermelho.") == 0) {
        if (contadorVermelho == 0) {
            return 1;
        }
    }
    // Missão: eliminar exército azul
    if (strcmp(missao, "Eliminar exército azul.") == 0) {
        if (contadorAzul == 0) {
            return 1;
        }
    }
    return 0;
}

// Exibe o mapa atualizado
void exibirMapa(struct Territorio *territorios, int numero_territorios) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < numero_territorios; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }
}

// Libera memória alocada dinamicamente
void liberarMemoria(struct Territorio *territorios, char *missaoJogador) {
    free(territorios);
    free(missaoJogador);
}

int main() {
    srand((unsigned int)time(NULL));
    int numero_territorios;
    int total_territorios = 0;
    int opcao_ataque;
    int opcao_defesa;
    
    printf("-- Bem vindo ao jogo War! --\n");
    // Quantidade de territórios
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &numero_territorios);

    // Alocação dinâmica dos territórios
    struct Territorio *territorios;
    territorios = malloc((size_t)numero_territorios * sizeof(struct Territorio));

    // Verifica erro no malloc
    if (territorios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Alocação dinâmica da missão
    char *missaoJogador;
    missaoJogador = malloc(100 * sizeof(char));

    // Verifica erro no malloc
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória.\n");
        free(territorios);
        return 1;
    }

    // Sorteia missão
    atribuirMissao(missaoJogador, missoes, 5);

    // Exibe missão apenas uma vez
    exibirMissao(missaoJogador);

    // Cadastro dos territórios
    while (total_territorios < numero_territorios) {
        printf("\n-- Território %d --\n", total_territorios + 1);
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
        // Exibe mapa atualizado
        exibirMapa(territorios, numero_territorios);

        // Escolha do atacante
        printf("\nDigite o território atacante (0 para sair): ");
        scanf("%d", &opcao_ataque);

        // Encerrar jogo
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
        if (opcao_ataque < 0 || opcao_ataque >= numero_territorios || opcao_defesa < 0 || opcao_defesa >= numero_territorios) {
            printf("\nTerritório inválido!\n");
            continue;
        }

        // Impede atacar a si mesmo
        if (opcao_ataque == opcao_defesa) {
            printf("\nUm território não pode atacar ele mesmo!\n");
            continue;
        }

        // Impede ataque aliado
        if (strcmp(territorios[opcao_ataque].cor, territorios[opcao_defesa].cor) == 0) {
            printf("\nVocê não pode atacar um território aliado!\n");
            continue;
        }

        // Verifica tropas suficientes
        if (territorios[opcao_ataque].tropas <= 1) {
            printf("\nO atacante precisa ter mais de 1 tropa!\n");
            continue;
        }

        // Realiza ataque
        Atacar(&territorios[opcao_ataque], &territorios[opcao_defesa]);

        // Verifica missão
        if (verificarMissao(missaoJogador, territorios, numero_territorios)) {
            printf("\n===== MISSÃO CUMPRIDA =====\n");
            printf("Você venceu o jogo!\n");
            break;
        }
    }

    // Libera memória
    liberarMemoria(territorios, missaoJogador);

    return 0;
}