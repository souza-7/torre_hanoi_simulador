#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> 
#include "pilha.h"
#include "torre_hanoi.h" 
#include "historico.h"   

Pilha torreA, torreB, torreC;
int numDiscosGlobal;
int movimentosGlobais;

// --- Implementação das funções ---

// Função para limpar a tela do console, compatível com Windows e Unix-like
void limparTela() {
    #ifdef _WIN32
        system("cls"); // Comando para Windows
    #else
        system("clear"); // Comando para sistemas Unix-like (Linux, macOS)
    #endif
}

// Inicializa as torres para um novo jogo
void configurarJogo() {
    // Inicializa todas as pilhas como vazias
    inicializarPilha(&torreA, numDiscosGlobal);
    inicializarPilha(&torreB, numDiscosGlobal);
    inicializarPilha(&torreC, numDiscosGlobal);

    // Adiciona os discos à Torre A em ordem decrescente (maior embaixo)
    for (int i = numDiscosGlobal; i >= 1; i--) {
        push(&torreA, i);
    }
    movimentosGlobais = 0; // Reseta o contador de movimentos
}

// Exibe o estado atual das torres no console
void exibirTorres() {
    limparTela(); // Limpa a tela antes de cada atualização
    printf("\n--- Torre de Hanoi ---\n");
    printf("Numero de Discos: %d | Movimentos: %d\n", numDiscosGlobal, movimentosGlobais);
    printf("-------------------------\n");

    // Imprime os discos de cima para baixo
    for (int i = numDiscosGlobal - 1; i >= 0; i--) {
        // desenharLinhaDiscos exibe o disco na altura 'i' para cada torre
        desenharLinhaDiscos(i, &torreA, numDiscosGlobal);
        desenharLinhaDiscos(i, &torreB, numDiscosGlobal);
        desenharLinhaDiscos(i, &torreC, numDiscosGlobal);
        printf("\n"); // Nova linha após cada "nível" de discos
    }
    printf("---A-------B-------C---\n"); // Rótulos das torres
}

// Desenha uma linha de discos para uma torre específica
// altura_linha: a posição vertical do disco (0 para base, numDiscos-1 para topo)
// torre: o ponteiro para a pilha (torre) a ser desenhada
// max_discos: o número total de discos no jogo (usado para centralização)
void desenharLinhaDiscos(int altura_linha, Pilha *torre, int max_discos) {
    int disco_val = 0;
    // Verifica se a altura_linha está dentro dos limites da pilha
    if (altura_linha < torre->topo + 1) {
        disco_val = torre->discos[altura_linha]; // Obtém o valor do disco
    }

    // Calcula o preenchimento para centralizar o disco
    int padding = max_discos - disco_val; // Maior padding para discos menores
    
    // Imprime espaços de preenchimento
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    // Imprime o disco ou o "poste"
    if (disco_val > 0) {
        for (int i = 0; i < disco_val; i++) {
            printf("#");
        }
        printf("%d", disco_val); // Opcional: mostrar o número do disco
        for (int i = 0; i < disco_val; i++) {
            printf("#");
        }
    } else {
        printf("|"); // Poste vazio
    }

    // Imprime mais espaços de preenchimento
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf(" "); // Espaço entre as torres
}


// Tenta mover um disco de uma torre para outra
// Retorna 1 se o movimento foi bem-sucedido, 0 caso contrário
int moverDisco(Pilha *origem, Pilha *destino) {
    if (isPilhaVazia(origem)) {
        printf("Erro: Torre de origem vazia!\n");
        return 0;
    }

    int disco = peek(origem); // Pega o disco do topo da origem

    if (!isPilhaVazia(destino) && disco > peek(destino)) {
        printf("Erro: Nao pode colocar um disco maior sobre um menor!\n");
        return 0;
    }

    pop(origem);    // Remove o disco da origem
    push(destino, disco); // Adiciona o disco ao destino
    movimentosGlobais++; // Incrementa o contador de movimentos
    return 1;
}

// Lógica principal do jogo da Torre de Hanói
// Retorna o número total de movimentos feitos
int jogarTorreHanoi(char *nomeJogador) {
    configurarJogo(); // Configura as torres para um novo jogo
    char origemChar, destinoChar;
    Pilha *origem, *destino;
    int movimentosValidos = 0;

    exibirTorres();
    printf("\nBem-vindo(a), %s! Mova os discos de A para C.\n", nomeJogador);
    printf("Digite 'S' ou 's' a qualquer momento para sair do jogo.\n");
    
    // O jogo continua até que todos os discos estejam na torre C
    while (torreC.topo != numDiscosGlobal - 1) {
        printf("\nMover disco de (A, B, C) ou Sair (S): ");
        scanf(" %c", &origemChar); // O espaço antes de %c consome qualquer newline pendente
        
        if (origemChar == 'S' || origemChar == 's') {
            printf("Saindo do jogo atual.\n");
            break; // Sai do loop do jogo
        }

        printf("Para (A, B, C): ");
        scanf(" %c", &destinoChar);
        while (getchar() != '\n'); // Limpa o buffer do teclado

        // Converte os caracteres para ponteiros de pilha
        origem = NULL; destino = NULL;

        if (origemChar == 'A' || origemChar == 'a') origem = &torreA;
        else if (origemChar == 'B' || origemChar == 'b') origem = &torreB;
        else if (origemChar == 'C' || origemChar == 'c') origem = &torreC;

        if (destinoChar == 'A' || destinoChar == 'a') destino = &torreA;
        else if (destinoChar == 'B' || destinoChar == 'b') destino = &torreB;
        else if (destinoChar == 'C' || destinoChar == 'c') destino = &torreC;

        if (origem == NULL || destino == NULL || origem == destino) {
            printf("Entrada invalida. As torres devem ser A, B ou C e diferentes.\n");
        } else {
            if (moverDisco(origem, destino)) { // Tenta mover o disco
                movimentosValidos++; // Incrementa contador de movimentos válidos
            }
        }
        exibirTorres(); // Atualiza a exibição após cada tentativa de movimento
        // Opcional: pequena pausa para visualização
        // #ifndef _WIN32
        //    usleep(200000); // 200 milissegundos (Linux/macOS)
        // #endif
    }

    if (torreC.topo == numDiscosGlobal - 1) {
        printf("\nPARABENS, %s! Voce concluiu a Torre de Hanoi em %d movimentos!\n", nomeJogador, movimentosGlobais);
        printf("O numero minimo de movimentos para %d discos eh %d.\n", numDiscosGlobal, (1 << numDiscosGlobal) - 1);
    }

    // Libera a memória das pilhas
    free(torreA.discos);
    free(torreB.discos);
    free(torreC.discos);
    
    return movimentosGlobais; // Retorna o total de movimentos feitos
}
