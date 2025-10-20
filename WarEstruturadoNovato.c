#include <stdio.h>
#include <string.h>

#define QTD_TERRITORIOS 5

// Estrutura representando um território
typedef struct {
    char nome[50];
    char corExercito[30];
    int numeroTropas;
} Territorio;

int main() {
    Territorio mapa[QTD_TERRITORIOS];

    printf("==========================================\n");
    printf("     🗺️  DESAFIO WAR ESTRUTURADO - NÍVEL NOVATO\n");
    printf("==========================================\n\n");

    printf(">>> Cadastro Inicial dos Territórios <<<\n\n");

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("=== Território %d ===\n", i + 1);

        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove o \n

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].numeroTropas);
        getchar(); // limpa o ENTER do buffer

        printf("\n");
    }

    printf("==========================================\n");
    printf("       🌍 ESTADO ATUAL DO MAPA DE GUERRA\n");
    printf("==========================================\n\n");

    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("🛡️  Território %d\n", i + 1);
        printf("    Nome: %s\n", mapa[i].nome);
        printf("    Cor do Exército: %s\n", mapa[i].corExercito);
        printf("    Tropas em campo: %d\n", mapa[i].numeroTropas);
        printf("------------------------------------------\n");
    }

    printf("🧭 Fim do cadastro. Os territórios estão prontos para a batalha!\n");

    return 0;
}

