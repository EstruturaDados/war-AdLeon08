/*
-------------------------------------------------------------
DESAFIO WAR ESTRUTURADO - NÍVEL AVENTUREIRO
Aluno: Aderlon Barbosa Pessoa
Matéria: Estrutura de Dados
Descrição:
Neste código eu continuei o projeto do nível Novato,
mas agora evoluí ele para o Nível Aventureiro.

As novidades aqui são:
- Uso de alocação dinâmica de memória com calloc
- Uso de ponteiros
- Uma função que simula ataques entre territórios
- Uso de números aleatórios (rand) para representar os dados da batalha

A ideia é o jogador escolher dois territórios:
um que ataca e outro que defende.
Depois, os dados são sorteados e vemos quem vence o combate.
-------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>  // biblioteca necessária pro calloc e rand
#include <string.h>  // usada pra tirar o \n do fgets
#include <time.h>    // usada pra gerar números aleatórios diferentes

// quantidade de territórios (ainda 5, como antes)
#define QTD_TERRITORIOS 5

// mesma struct do nível novato, que representa um território
typedef struct {
    char nome[50];
    char corExercito[30];
    int numeroTropas;
} Territorio;

/*
-------------------------------------------------------------
Função: simularBatalha
Descrição:
Essa função faz a simulação de um ataque entre dois territórios.
Ela recebe os ponteiros do atacante e do defensor e sorteia
dados de ataque e defesa com rand().
-------------------------------------------------------------
*/
void simularBatalha(Territorio *atacante, Territorio *defensor) {
    printf("\n  BATALHA ENTRE %s (Atacante) E %s (Defensor)\n", atacante->nome, defensor->nome);

    // sorteia os dados (valores entre 1 e 6)
    int dadoAtaque = (rand() % 6) + 1;
    int dadoDefesa = (rand() % 6) + 1;

    // mostra os valores sorteados
    printf(" Dado do ataque: %d\n", dadoAtaque);
    printf(" Dado da defesa: %d\n", dadoDefesa);

    // verifica quem venceu a rodada
    if (dadoAtaque > dadoDefesa) {
        // atacante vence — defensor perde uma tropa
        defensor->numeroTropas--;

        printf(" O ataque foi bem-sucedido! O defensor perdeu 1 tropa.\n");

        // se o defensor perder todas as tropas, o território é conquistado
        if (defensor->numeroTropas <= 0) {
            defensor->numeroTropas = 0;
            printf(" O território %s foi conquistado por %s!\n",
                   defensor->nome, atacante->corExercito);

            // o defensor muda de cor (conquistado)
            strcpy(defensor->corExercito, atacante->corExercito);
        }
    } else {
        // empate ou defesa vence — atacante é favorecido
        atacante->numeroTropas--;
        if (atacante->numeroTropas < 0) atacante->numeroTropas = 0;
        printf(" A defesa resistiu! O atacante perdeu 1 tropa.\n");
    }

    printf("------------------------------------------\n");
}

/*
-------------------------------------------------------------
Função: mostrarMapa
Descrição:
Mostra o estado atual de todos os territórios.
-------------------------------------------------------------
*/
void mostrarMapa(Territorio *mapa, int tamanho) {
    printf("\n==========================================\n");
    printf("        ESTADO ATUAL DO MAPA DE GUERRA\n");
    printf("==========================================\n\n");

    for (int i = 0; i < tamanho; i++) {
        printf("  Território %d\n", i + 1);
        printf("    Nome: %s\n", mapa[i].nome);
        printf("    Cor do Exército: %s\n", mapa[i].corExercito);
        printf("    Tropas em campo: %d\n", mapa[i].numeroTropas);
        printf("------------------------------------------\n");
    }
}

/*
-------------------------------------------------------------
Função principal: main
Descrição:
Aqui o programa começa. Cadastra os territórios usando calloc
e depois entra num loop para o jogador simular ataques.
-------------------------------------------------------------
*/
int main() {
    // usa srand(time(NULL)) pra mudar os números aleatórios a cada execução
    srand(time(NULL));

    printf("==========================================\n");
    printf("      DESAFIO WAR ESTRUTURADO - NÍVEL AVENTUREIRO\n");
    printf("==========================================\n\n");

    printf(">>> Cadastro Inicial dos Territórios <<<\n\n");

    // agora o vetor é dinâmico, criado com calloc
    // calloc zera toda a memória, o que ajuda a evitar lixo de memória
    Territorio *mapa = (Territorio *) calloc(QTD_TERRITORIOS, sizeof(Territorio));

    // verifica se deu certo a alocação
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // cadastro dos territórios (igual ao nível novato)
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("=== Território %d ===\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].numeroTropas);
        getchar();

        printf("\n");
    }

    // mostra o mapa inicial
    mostrarMapa(mapa, QTD_TERRITORIOS);

    int opcao = 1;

    // laço interativo para as batalhas
    while (opcao != 0) {
        printf("\n=== FASE DE ATAQUE ===\n");
        printf("Digite o número do território atacante (1 a 5): ");
        int atacante, defensor;
        scanf("%d", &atacante);

        printf("Digite o número do território defensor (1 a 5): ");
        scanf("%d", &defensor);
        getchar();

        // verifica se os números são válidos e diferentes
        if (atacante < 1 || atacante > QTD_TERRITORIOS ||
            defensor < 1 || defensor > QTD_TERRITORIOS ||
            atacante == defensor) {
            printf(" Escolha inválida! Tente novamente.\n");
            continue;
        }

        // chama a função de batalha (passando os ponteiros)
        simularBatalha(&mapa[atacante - 1], &mapa[defensor - 1]);

        // mostra o novo estado do mapa
        mostrarMapa(mapa, QTD_TERRITORIOS);

        // pergunta se o jogador quer continuar
        printf("Deseja realizar outro ataque? (1 = sim / 0 = não): ");
        scanf("%d", &opcao);
        getchar();
    }

    // libera a memória alocada com calloc
    free(mapa);

    printf("\n Fim das batalhas! O mapa final foi exibido acima.\n");
    return 0;
}

