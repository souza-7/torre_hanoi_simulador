#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>   
#include "pilha.h"       
#include "torre_hanoi.h" 
#include "historico.h"  

// --- Protótipos de funções locais do main.c ---
void exibirMenuPrincipal();
void exibirMenuHistorico(); // <-- Novo protótipo para a função local

int main() {
    // Carrega o histórico ao iniciar o programa
    carregarHistoricoArquivo();

    int escolha;
    do {
        exibirMenuPrincipal(); // Chama a função para exibir o menu principal
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        // Limpa o buffer do teclado após ler um inteiro para evitar problemas com leituras futuras de string
        while (getchar() != '\n'); 

        switch (escolha) {
            case 1: { // Iniciar Novo Jogo
                char nomeJogador[50];
                int numDiscos;

                limparTela();
                printf("--- Iniciar Novo Jogo ---\n");
                printf("Digite seu nome (max 49 caracteres): ");
                // Usa fgets para ler o nome do jogador, incluindo espaços
                fgets(nomeJogador, sizeof(nomeJogador), stdin);
                // Remove o '\n' que fgets pode adicionar no final
                nomeJogador[strcspn(nomeJogador, "\n")] = 0; 

                do {
                    printf("Digite o numero de discos (3 a 10): ");
                    scanf("%d", &numDiscos);
                    // Limpa o buffer do teclado
                    while (getchar() != '\n'); 
                } while (numDiscos < 3 || numDiscos > 10);
                
                numDiscosGlobal = numDiscos; // Define o número global de discos

                // Inicia o jogo da Torre de Hanói
                int movimentosFeitos = jogarTorreHanoi(nomeJogador);

                // No final do jogo, adicione ao histórico
                HistoricoPartida novaPartida;
                strcpy(novaPartida.nomeJogador, nomeJogador);
                novaPartida.modoJogo = numDiscos; // 'modoJogo' agora representa o número de discos
                novaPartida.numeroMovimentos = movimentosFeitos;

                // Captura a data e hora atual
                time_t t = time(NULL);
                struct tm *tm_info = localtime(&t);
                strftime(novaPartida.dataHoraEncerramento, sizeof(novaPartida.dataHoraEncerramento), "%Y-%m-%d %H:%M:%S", tm_info);

                adicionarHistorico(novaPartida);
                printf("\nPartida adicionada ao historico!\n");
                printf("Pressione Enter para continuar...");
                getchar(); // Aguarda o usuário pressionar Enter
                break;
            }
            case 2: // Ver Historico de Partidas
                exibirMenuHistorico(); // Chama o menu específico para o histórico
                break;
            case 3:
                printf("Saindo do jogo. Salvando historico...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar(); // Aguarda o usuário pressionar Enter
                break;
        }
    } while (escolha != 3);

    // Salva o histórico no arquivo ao sair do programa
    salvarHistoricoArquivo();
    // Libera a memória alocada para a lista encadeada do histórico
    liberarHistorico();       

    return 0;
}

// --- Implementação das funções de menu ---

void exibirMenuPrincipal() {
    limparTela();
    printf("--- Simulador da Torre de Hanoi ---\n");
    printf("1. Iniciar Novo Jogo\n");
    printf("2. Ver Historico de Partidas\n");
    printf("3. Sair\n");
    printf("-----------------------------------\n");
}

void exibirMenuHistorico() {
    int escolha_historico;
    do {
        limparTela();
        printf("\n--- Menu do Historico ---\n");
        printf("1. Exibir todo o Historico\n");
        printf("2. Buscar Historico por Nome de Jogador\n");
        printf("3. Buscar Historico por Data\n");
        printf("4. Voltar ao Menu Principal\n");
        printf("--------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha_historico);
        // Limpa o buffer do teclado
        while (getchar() != '\n'); 

        switch (escolha_historico) {
            case 1:
                exibirHistorico(); // Função de historico.c
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 2:
                buscarHistoricoPorUsuario(); // Função de historico.c
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 3:
                buscarHistoricoPorData(); // Função de historico.c
                printf("\nPressione Enter para continuar...");
                getchar();
                break;
            case 4:
                // Voltar ao menu principal (sair do loop)
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                printf("Pressione Enter para continuar...");
                getchar();
                break;
        }
    } while (escolha_historico != 4);
}
