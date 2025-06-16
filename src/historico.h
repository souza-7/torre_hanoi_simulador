#ifndef HISTORICO_H
#define HISTORICO_H

#include <stdio.h>   // Para FILE, fopen, fclose, fprintf, fscanf, fgets
#include <stdlib.h>  // Para malloc, free
#include <string.h>  // Para strcpy, strcmp, strncmp

// --- Estruturas de Dados para o Histórico ---

// Estrutura para os dados de uma partida
typedef struct {
    char nomeJogador[50];          // Nome do jogador
    int modoJogo;                // Número de discos
    int numeroMovimentos;        // Número de movimentos
    char dataHoraEncerramento[20]; // Data e hora do encerramento (AAAA-MM-DD HH:MM:SS)
} HistoricoPartida;

// Nó da lista encadeada para o histórico
typedef struct NoHistorico {
    HistoricoPartida dados;
    struct NoHistorico *proximo;
} NoHistorico;

// --- Protótipos das Funções do Histórico ---

// Adiciona um novo registro de partida ao histórico (lista encadeada).
void adicionarHistorico(HistoricoPartida novaPartida);

// Salva o histórico atual em memória para um arquivo de texto.
void salvarHistoricoArquivo();

// Carrega o histórico do arquivo para a memória (lista encadeada).
void carregarHistoricoArquivo();

// Exibe todos os registros do histórico no terminal.
void exibirHistorico();

// Busca registros do histórico por nome de jogador.
void buscarHistoricoPorUsuario();

// Busca registros do histórico por data (AAAA-MM-DD).
void buscarHistoricoPorData();

// Libera a memória alocada para a lista encadeada do histórico.
void liberarHistorico();

// Variável global para a cabeça da lista do histórico (declarada como extern aqui)
extern NoHistorico *historicoCabeca;

#endif