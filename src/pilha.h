#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h> 
#include <stdio.h>  

// Estrutura para representar a Pilha
typedef struct {
    int *discos; // Ponteiro para o array que armazenará os discos
    int topo;    // Índice do topo da pilha (-1 se vazia)
    int capacidade; // Capacidade máxima da pilha
} Pilha;

// Protótipos das funções da Pilha
void inicializarPilha(Pilha *p, int capacidade); // <-- Adicionado 'capacidade' aqui!
void push(Pilha *p, int disco);
int pop(Pilha *p);
int peek(Pilha *p);
int isPilhaVazia(Pilha *p);     // <-- Garanta que este protótipo está aqui!
int isPilhaCheia(Pilha *p);

#endif
