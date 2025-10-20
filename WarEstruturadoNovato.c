/*
-------------------------------------------------------------
DESAFIO WAR ESTRUTURADO - NÍVEL NOVATO
Aluno: Aderlon Barbosa Pessoa
Matéria: Estrutura de Dados
Descrição:
Neste código estou criando o começo do jogo WAR Estruturado.
Aqui o objetivo é só cadastrar os territórios, guardando o nome,
a cor do exército e o número de tropas em cada território.

Eu usei uma struct para representar um território e um vetor
para guardar vários deles. Depois, mostro tudo na tela.
-------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h> // usei para conseguir tirar o '\n' do fgets

// quantidade de territórios que vamos cadastrar
#define QTD_TERRITORIOS 5

// Aqui criei a estrutura (struct) para representar um território
typedef struct {
    char nome[50];        // nome do território
    char corExercito[30]; // cor do exército
    int numeroTropas;     // quantidade de tropas
} Territorio;

int main() {
    // vetor de 5 territórios (fixo, como o exercício pediu)
    Territorio mapa[QTD_TERRITORIOS];

    // mensagens iniciais só pra deixar mais bonito
    printf("==========================================\n");
    printf("     DESAFIO WAR ESTRUTURADO - NÍVEL NOVATO\n");
    printf("==========================================\n\n");

    printf(">>> Cadastro Inicial dos Territórios <<<\n\n");

    // aqui uso um laço pra repetir o cadastro 5 vezes (um pra cada território)
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("=== Território %d ===\n", i + 1);

        // uso fgets pra ler o nome porque ele aceita espaços (ex: "Vale da Lua")
        printf("Nome do território: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // tiro o '\n' do final

        // mesma coisa pra cor do exército
        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, sizeof(mapa[i].corExercito), stdin);
        mapa[i].corExercito[strcspn(mapa[i].corExercito, "\n")] = '\0';

        // agora leio o número de tropas com scanf
        printf("Número de tropas: ");
        scanf("%d", &mapa[i].numeroTropas);

        // getchar serve pra limpar o "Enter" que o scanf deixa pra trás
        getchar();

        printf("\n");
    }

    // depois que terminou o cadastro, mostro tudo que foi digitado
    printf("==========================================\n");
    printf("       ESTADO ATUAL DO MAPA DE GUERRA\n");
    printf("==========================================\n\n");

    // laço pra mostrar cada território e suas informações
    for (int i = 0; i < QTD_TERRITORIOS; i++) {
        printf("  Território %d\n", i + 1);
        printf("    Nome: %s\n", mapa[i].nome);
        printf("    Cor do Exército: %s\n", mapa[i].corExercito);
        printf("    Tropas em campo: %d\n", mapa[i].numeroTropas);
        printf("------------------------------------------\n");
    }

    // mensagem final pra encerrar
    printf(" Fim do cadastro. Os territórios estão prontos para a batalha!\n");

    return 0; // fim do programa
}
