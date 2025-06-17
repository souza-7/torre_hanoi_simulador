#include "pilha.h" 


void inicializarPilha(Pilha *p, int capacidade) { // <-- Recebe 'capacidade' agora!
    p->capacidade = capacidade;
    p->discos = (int *) malloc(sizeof(int) * p->capacidade);
    if (p->discos == NULL) {
        // Tratar erro de alocação de memória
        fprintf(stderr, "Erro: Falha na alocacao de memoria para a pilha.\n");
        exit(EXIT_FAILURE); // Encerrar o programa em caso de erro grave
    }
    p->topo = -1; // Pilha vazia
}

int isPilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int isPilhaCheia(Pilha *p) {
    return p->topo == p->capacidade - 1;
}

void push(Pilha *p, int disco) {
    if (isPilhaCheia(p)) {
        fprintf(stderr, "Erro: Pilha cheia, nao eh possivel adicionar mais discos.\n");
        return;
    }
    p->discos[++(p->topo)] = disco;
}

int pop(Pilha *p) {
    if (isPilhaVazia(p)) {
        fprintf(stderr, "Erro: Pilha vazia, nao ha discos para remover.\n");
        return -1; // Retorno de erro
    }
    return p->discos[(p->topo)--];
}

int peek(Pilha *p) {
    if (isPilhaVazia(p)) {
        // fprintf(stderr, "Erro: Pilha vazia, nao ha discos para visualizar.\n");
        return 0; // Retorna 0 ou outro valor para indicar pilha vazia sem erro crítico
    }
    return p->discos[p->topo];
}
