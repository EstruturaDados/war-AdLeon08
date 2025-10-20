// DESAFIO WAR ESTRUTURADO - NÍVEL MESTRE
// Autor: [Seu Nome]
// Objetivo: Criar um jogo simplificado de WAR com modularização, ataques e sistema de missão.
// Esse código é a evolução do nível Aventureiro, agora com funções separadas e um menu principal.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===== Estrutura do Território =====
typedef struct {
    char nome[50];          // Nome do território
    char corExercito[30];   // Cor do exército
    int tropas;             // Quantidade de tropas no território
    int conquistado;        // Indica se o território foi conquistado (1 = sim, 0 = não)
} Territorio;

// ===== Prototipação das Funções =====
void inicializarTerritorios(Territorio *mapa, const int n);
void exibirMapa(const Territorio *mapa, const int n);
void atacar(Territorio *mapa, const int n);
void verificarMissao(Territorio *mapa, const int n, int missao);
int sorteiaMissao();
int todosTerritoriosConquistados(Territorio *mapa, const int n, const char *cor);

// ===== Função Principal =====
int main() {
    srand(time(NULL));  // Inicializa a semente para gerar números aleatórios

    const int qtd = 5;  // Quantidade de territórios
    Territorio *mapa = (Territorio*) calloc(qtd, sizeof(Territorio));  // Alocação dinâmica

    int opcao;
    int missao = sorteiaMissao();  // Missão aleatória

    inicializarTerritorios(mapa, qtd);  // Preenche os territórios automaticamente

    printf("\n Bem-vindo ao WAR ESTRUTURADO - Nível Mestre!\n");
    printf("Sua missão secreta foi atribuída!\n");

    // ===== Loop principal do jogo =====
    do {
        printf("\n======= MENU PRINCIPAL =======\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missão\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch(opcao) {
            case 1:
                atacar(mapa, qtd);
                break;
            case 2:
                verificarMissao(mapa, qtd, missao);
                break;
            case 0:
                printf("\nEncerrando o jogo... Obrigado por jogar!\n");
                break;
            default:
                printf("Opção inválida, tente novamente!\n");
        }

    } while(opcao != 0);

    free(mapa);  // Libera a memória usada
    return 0;
}

// ===== Função: inicializa os territórios =====
void inicializarTerritorios(Territorio *mapa, const int n) {
    // Criação automática de territórios (sem entrada manual)
    const char *nomes[] = {"Brasil", "Argentina", "Canadá", "Japão", "Egito"};
    const char *cores[] = {"Vermelho", "Azul", "Verde", "Amarelo", "Preto"};

    for(int i = 0; i < n; i++) {
        strcpy(mapa[i].nome, nomes[i]);
        strcpy(mapa[i].corExercito, cores[i]);
        mapa[i].tropas = rand() % 10 + 3;  // Tropas entre 3 e 12
        mapa[i].conquistado = 0;
    }
}

// ===== Função: exibe o estado atual do mapa =====
void exibirMapa(const Territorio *mapa, const int n) {
    printf("\n======= ESTADO DO MAPA =======\n");
    for(int i = 0; i < n; i++) {
        printf("%d. %-10s | Exército: %-8s | Tropas: %2d\n",
               i + 1, mapa[i].nome, mapa[i].corExercito, mapa[i].tropas);
    }
}

// ===== Função: simula uma batalha entre dois territórios =====
void atacar(Territorio *mapa, const int n) {
    int atq, def;
    exibirMapa(mapa, n);

    printf("\nEscolha o território ATACANTE (1 a %d): ", n);
    scanf("%d", &atq);
    printf("Escolha o território DEFENSOR (1 a %d): ", n);
    scanf("%d", &def);

    // Ajusta para índice do vetor
    atq--;
    def--;

    // Verifica se os índices são válidos
    if(atq < 0 || def < 0 || atq >= n || def >= n) {
        printf("Escolhas inválidas!\n");
        return;
    }

    // Verifica se o atacante tem tropas suficientes
    if(mapa[atq].tropas <= 1) {
        printf("\n%s não tem tropas suficientes para atacar!\n", mapa[atq].nome);
        return;
    }

    printf("\n BATALHA ENTRE %s (Atacante) e %s (Defensor)\n",
           mapa[atq].nome, mapa[def].nome);

    int dadoAtq = rand() % 6 + 1;  // Valor entre 1 e 6
    int dadoDef = rand() % 6 + 1;

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtq, dadoDef);

    if(dadoAtq >= dadoDef) {
        // Atacante vence
        mapa[def].tropas--;

        printf("%s venceu a rodada!\n", mapa[atq].nome);

        // Se o defensor perdeu todas as tropas
        if(mapa[def].tropas <= 0) {
            printf("%s conquistou o território %s!\n", mapa[atq].nome, mapa[def].nome);
            strcpy(mapa[def].corExercito, mapa[atq].corExercito);
            mapa[def].tropas = 1;
            mapa[atq].tropas--;  // Move uma tropa para o novo território
            mapa[def].conquistado = 1;
        }
    } else {
        // Defensor vence
        mapa[atq].tropas--;
        printf("%s resistiu ao ataque!\n", mapa[def].nome);
    }

    exibirMapa(mapa, n);
}

// ===== Função: sorteia missão aleatória =====
int sorteiaMissao() {
    // Retorna 1 ou 2, que correspondem às duas missões possíveis
    return rand() % 2 + 1;
}

// ===== Função: verifica o progresso da missão =====
void verificarMissao(Territorio *mapa, const int n, int missao) {
    printf("\n===== MISSÃO ATUAL =====\n");

    if(missao == 1) {
        printf("Missão: Destruir o exército VERDE!\n");

        // Verifica se ainda existe algum território verde
        if(todosTerritoriosConquistados(mapa, n, "Verde")) {
            printf("Você cumpriu sua missão! Exército verde eliminado!\n");
        } else {
            printf("Ainda há territórios verdes resistindo...\n");
        }

    } else if(missao == 2) {
        printf("Missão: Conquistar 3 territórios!\n");

        int conquistados = 0;
        for(int i = 0; i < n; i++) {
            if(mapa[i].conquistado == 1) conquistados++;
        }

        if(conquistados >= 3) {
            printf("Parabéns! Você conquistou 3 territórios e venceu!\n");
        } else {
            printf("Progresso: %d/3 territórios conquistados.\n", conquistados);
        }
    }
}

// ===== Função: verifica se todos territórios de uma cor foram conquistados =====
int todosTerritoriosConquistados(Territorio *mapa, const int n, const char *cor) {
    for(int i = 0; i < n; i++) {
        if(strcmp(mapa[i].corExercito, cor) == 0)
            return 0; // Ainda existe território dessa cor
    }
    return 1; // Nenhum território dessa cor sobrou
}

