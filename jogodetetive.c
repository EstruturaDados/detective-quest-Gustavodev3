#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ESTRUTURA DE DADOS


// Estrutura que representa uma sala (nó da árvore binária)
typedef struct Sala {
    char nome[50];            // Nome da sala
    struct Sala *esquerda;    // Caminho à esquerda
    struct Sala *direita;     // Caminho à direita
} Sala;


// FUNÇÕES PRINCIPAIS


/*
 * Função: criarSala
 * -----------------
 * Cria dinamicamente uma sala com o nome informado.
 * 
 * nome: string com o nome do cômodo
 * 
 * retorna: ponteiro para a nova sala
 */
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*) malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória para a sala!\n");
        exit(1);
    }

    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;

    return novaSala;
}

/*
 * Função: explorarSalas
 * Permite que o jogador explore a mansão interativamente,
 * escolhendo caminhos à esquerda e ou à direita d,
 * até chegar a um cômodo sem saídas
 * 
 * salaAtual: ponteiro para a sala onde o jogador está no momento
 */
void explorarSalas(Sala* salaAtual) {
    char escolha;

    while (1) {
        printf("\nVocê está na %s.\n", salaAtual->nome);

        // Se não há caminhos disponíveis, termina a exploração
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("Você chegou ao fim da exploração! Esta sala não possui saídas.\n");
            break;
        }

        printf("Escolha um caminho:\n");
        if (salaAtual->esquerda != NULL)
            printf("  (e) Ir para a sala à esquerda: %s\n", salaAtual->esquerda->nome);
        if (salaAtual->direita != NULL)
            printf("  (d) Ir para a sala à direita: %s\n", salaAtual->direita->nome);
        printf("  (s) Sair da exploração\n");

        printf("Sua escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL)
                salaAtual = salaAtual->esquerda;
            else
                printf("Não há caminho à esquerda!\n");
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL)
                salaAtual = salaAtual->direita;
            else
                printf("Não há caminho à direita!\n");
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf("Saindo da mansão...\n");
            break;
        } 
        else {
            printf("Opção inválida! Tente novamente.\n");
        }
    }
}

/*
 * Função: liberarArvore
 * ---------------------
 * Libera a memória alocada para todas as salas (nós da árvore).
 */
void liberarArvore(Sala* raiz) {
    if (raiz == NULL)
        return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

/*
 * Função: main
 * ------------
 * Cria a estrutura da mansão (árvore binária),
 * define suas conexões e inicia a exploração.
 */
int main() {
    // ===============================
    // Construindo a estrutura da mansão
    // ===============================
    Sala* hallEntrada = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* jardim = criarSala("Jardim");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* escritorio = criarSala("Escritório");
    Sala* quarto = criarSala("Quarto Principal");
    Sala* porao = criarSala("Porão");

    // Estrutura da mansão (árvore binária):
    // Hall de Entrada
    // Sala de Estar       Cozinha
    // Jardim   Biblioteca  Escritório  Quarto
    //  Porão

    hallEntrada->esquerda = salaEstar;
    hallEntrada->direita = cozinha;

    salaEstar->esquerda = jardim;
    salaEstar->direita = biblioteca;

    cozinha->esquerda = escritorio;
    cozinha->direita = quarto;

    biblioteca->direita = porao;


    // Início da exploração

    printf("Bem-vindo à Mansão Misteriosa!\n");
    printf("--------------------------------\n");

    explorarSalas(hallEntrada);


    // Liberação de memória

    liberarArvore(hallEntrada);

    printf("\nExploração encerrada. Até a próxima!\n");
    return 0;
}
