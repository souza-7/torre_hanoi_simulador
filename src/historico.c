#include <stdio.h>    // Para operações de arquivo (FILE, fopen, fclose, fprintf, fscanf, fgets)
#include <stdlib.h>   // Para alocação de memória (malloc, free)
#include <string.h>   // Para manipulação de strings (strcpy, strcmp, strncmp)
#include <time.h>     // Para time, localtime, strftime

// --- Inclua os cabeçalhos do seu projeto AQUI ---
// A ordem é importante para as dependências
#include "historico.h"   // Este DEVE ser o primeiro cabeçalho do seu projeto a ser incluído
#include "torre_hanoi.h" // Inclui para usar limparTela()

// Variável global que aponta para o primeiro nó da lista encadeada do histórico.
// É 'extern' em historico.h e definida aqui para que seja acessível por outras funções.
NoHistorico *historicoCabeca = NULL;

// Implementação da função para adicionar um novo registro ao histórico (lista encadeada).
void adicionarHistorico(HistoricoPartida novaPartida) {
    // Aloca memória para um novo nó da lista
    NoHistorico *novoNo = (NoHistorico *) malloc(sizeof(NoHistorico));
    if (novoNo == NULL) {
        printf("Erro: Falha na alocacao de memoria para o historico!\n");
        return;
    }

    // Copia os dados da nova partida para o novo nó
    novoNo->dados = novaPartida; // Copia a struct completa
    novoNo->proximo = NULL;      // O novo nó é sempre adicionado ao final, então seu próximo é NULL

    // Se a lista estiver vazia, o novo nó se torna a cabeça
    if (historicoCabeca == NULL) {
        historicoCabeca = novoNo;
    } else {
        // Percorre a lista até o último nó
        NoHistorico *atual = historicoCabeca;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        // Adiciona o novo nó ao final da lista
        atual->proximo = novoNo;
    }
}

// Implementação da função para salvar o histórico atual em memória para um arquivo de texto.
void salvarHistoricoArquivo() {
    // Abre o arquivo em modo de escrita ('w') para sobrescrever o conteúdo existente.
    FILE *arquivo = fopen("historico_hanoi.txt", "w");
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo de historico para escrita!\n");
        return;
    }

    NoHistorico *atual = historicoCabeca;
    // Percorre a lista encadeada e escreve cada registro no arquivo
    while (atual != NULL) {
        fprintf(arquivo, "%s,%d,%d,%s\n",
                atual->dados.nomeJogador,
                atual->dados.modoJogo,
                atual->dados.numeroMovimentos,
                atual->dados.dataHoraEncerramento);
        atual = atual->proximo;
    }
    fclose(arquivo); // Fecha o arquivo
}

// Implementação da função para carregar o histórico do arquivo para a memória (lista encadeada).
void carregarHistoricoArquivo() {
    // Libera qualquer histórico existente na memória antes de carregar um novo.
    liberarHistorico(); // Chama a função para limpar a lista existente

    // Abre o arquivo em modo de leitura ('r').
    FILE *arquivo = fopen("historico_hanoi.txt", "r");
    if (arquivo == NULL) {
        // Se o arquivo não existe ou não pode ser aberto, é a primeira execução, então apenas retorna.
        return;
    }

    char linha[256]; // Buffer para ler cada linha do arquivo
    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        HistoricoPartida partida;
        // Tenta analisar a linha no formato esperado: nome,discos,movimentos,data_hora
        if (sscanf(linha, "%49[^,],%d,%d,%19[^\n]",
                   partida.nomeJogador, &partida.modoJogo,
                   &partida.numeroMovimentos, partida.dataHoraEncerramento) == 4) {
            // Se a linha foi analisada com sucesso, adiciona a partida ao histórico em memória
            adicionarHistorico(partida);
        } else {
            // Pode haver linhas mal formatadas, ignore-as ou adicione log de erro
            fprintf(stderr, "Aviso: Linha mal formatada no historico.txt: %s\n", linha);
        }
    }
    fclose(arquivo); // Fecha o arquivo
}

// Implementação da função para exibir todos os registros do histórico no terminal.
void exibirHistorico() {
    limparTela(); // Limpa a tela antes de exibir (função de torre_hanoi.h)
    printf("\n--- Historico de Partidas ---\n");
    if (historicoCabeca == NULL) {
        printf("Nenhum historico disponivel.\n");
    } else {
        NoHistorico *atual = historicoCabeca;
        int i = 1;
        // Percorre a lista e imprime os dados de cada partida
        while (atual != NULL) {
            printf("%d. Jogador: %s, Discos: %d, Movimentos: %d, Data: %s\n",
                   i++,
                   atual->dados.nomeJogador,
                   atual->dados.modoJogo,
                   atual->dados.numeroMovimentos,
                   atual->dados.dataHoraEncerramento);
            atual = atual->proximo;
        }
    }
    printf("--------------------------\n");
}

// Implementação da função para buscar registros do histórico por nome de jogador.
void buscarHistoricoPorUsuario() {
    char nomeBusca[50];
    printf("Digite o nome do jogador para buscar: ");
    scanf("%49[^\n]%*c", nomeBusca); // Lê a linha inteira até o newline e consome ele

    limparTela();
    printf("\n--- Resultados da Busca para '%s' ---\n", nomeBusca);
    int encontrado = 0;
    NoHistorico *atual = historicoCabeca;
    // Percorre a lista, comparando o nome do jogador (case-sensitive)
    while (atual != NULL) {
        if (strcmp(atual->dados.nomeJogador, nomeBusca) == 0) { // strcmp retorna 0 se as strings forem iguais
            printf("Jogador: %s, Discos: %d, Movimentos: %d, Data: %s\n",
                   atual->dados.nomeJogador,
                   atual->dados.modoJogo,
                   atual->dados.numeroMovimentos,
                   atual->dados.dataHoraEncerramento);
            encontrado = 1; // Marca que pelo menos um registro foi encontrado
        }
        atual = atual->proximo;
    }
    if (!encontrado) {
        printf("Nenhuma partida encontrada para '%s'.\n", nomeBusca);
    }
    printf("-----------------------------------\n");
}

// Implementação da função para buscar registros do histórico por data (AAAA-MM-DD).
void buscarHistoricoPorData() {
    char dataBusca[11]; // AAAA-MM-DD + '\0' = 11 caracteres
    printf("Digite a data (AAAA-MM-DD) para buscar: ");
    scanf("%10s", dataBusca); // Lê a data a ser buscada (limita para evitar overflow)
    // Limpa o buffer do teclado
    while (getchar() != '\n'); 

    limparTela();
    printf("\n--- Resultados da Busca para '%s' ---\n", dataBusca);
    int encontrado = 0;
    NoHistorico *atual = historicoCabeca;
    // Percorre a lista, comparando os primeiros 10 caracteres da data e hora
    while (atual != NULL) {
        // strncmp compara um número específico de caracteres (a parte da data)
        if (strncmp(atual->dados.dataHoraEncerramento, dataBusca, 10) == 0) {
            printf("Jogador: %s, Discos: %d, Movimentos: %d, Data: %s\n",
                   atual->dados.nomeJogador,
                   atual->dados.modoJogo,
                   atual->dados.numeroMovimentos,
                   atual->dados.dataHoraEncerramento);
            encontrado = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrado) {
        printf("Nenhuma partida encontrada para '%s'.\n", dataBusca);
    }
    printf("-----------------------------------\n");
}

// Implementação da função para liberar a memória alocada para a lista encadeada do histórico.
void liberarHistorico() {
    NoHistorico *atual = historicoCabeca;
    NoHistorico *temp; // Ponteiro temporário para o nó a ser liberado
    // Percorre a lista, liberando cada nó um por um
    while (atual != NULL) {
        temp = atual;           // Armazena o nó atual
        atual = atual->proximo; // Move para o próximo nó antes de liberar o atual
        free(temp);             // Libera a memória do nó armazenado em temp
    }
    historicoCabeca = NULL; // Define a cabeça como NULL para indicar que a lista está vazia
}