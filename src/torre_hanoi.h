#ifndef TORRE_HANOI_H
#define TORRE_HANOI_H

#include "pilha.h" 

extern Pilha torreA, torreB, torreC;
extern int numDiscosGlobal;   // Número de discos na partida atual
extern int movimentosGlobais; // Contador de movimentos

// Protótipos das funções do jogo
void limparTela(); // Para limpar o console
void configurarJogo();
void exibirTorres();
int moverDisco(Pilha *origem, Pilha *destino);
int jogarTorreHanoi(char *nomeJogador);

// --- FUNÇÕES DE DESENHO/EXIBIÇÃO ---
void desenharLinhaDiscos(int altura_linha, Pilha *torre, int max_discos);

#endif
