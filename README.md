Simulador da Torre de Hanói em C
Este projeto é um simulador interativo do clássico quebra-cabeça Torre de Hanói, implementado em linguagem C. Ele permite aos jogadores configurar o número de discos, jogar a partida, e gerencia um histórico de todas as jogadas, salvando-o em um arquivo para persistência.

Funcionalidades
Configuração de Jogo: Defina o número de discos (de 3 a 10) para personalizar a dificuldade.
Interface de Console Interativa: Jogue a Torre de Hanói diretamente no terminal, com uma representação visual das torres e discos.
Contador de Movimentos: Acompanhe o número de movimentos realizados durante a partida.
Histórico de Partidas:
Salva automaticamente os dados das partidas (nome do jogador, número de discos, movimentos e data/hora de encerramento).
Carrega o histórico salvo ao iniciar o programa.
Exibe todas as partidas jogadas.
Permite buscar partidas por nome de jogador ou por data.
Validação de Movimentos: Garante que os movimentos sigam as regras da Torre de Hanói (disco maior não pode ser colocado sobre um menor).
Como Compilar e Rodar
Para compilar e executar este projeto, você precisará de um compilador C (como o GCC) instalado em seu sistema.

Clone ou Baixe o Repositório:

Bash

git clone https://github.com/seu-usuario/seu-repositorio.git
cd seu-repositorio
(Se você não estiver usando Git, apenas baixe os arquivos e navegue até a pasta raiz do projeto).

Crie a Pasta de Saída:
O executável será gerado em uma pasta bin. Certifique-se de que ela exista:

Bash

mkdir bin
Compile o Projeto:
Navegue até a raiz do projeto no seu terminal e use o seguinte comando GCC:

Bash

gcc -g src/main.c src/pilha.c src/torre_hanoi.c src/historico.c -o bin/torre_hanoi -Wall -Wextra -std=c11 -lm
-g: Inclui informações de depuração.
src/*.c: Inclui todos os arquivos fonte C.
-o bin/torre_hanoi: Define o nome do executável e a pasta de saída.
-Wall -Wextra: Ativa avisos adicionais do compilador para boas práticas.
-std=c11: Compila usando o padrão C11.
-lm: Linka a biblioteca matemática (pode ser necessária para algumas funções).
Execute o Simulador:
Após a compilação bem-sucedida, execute o programa:

Windows:
Bash

.\bin\torre_hanoi.exe
ou
Bash

bin\torre_hanoi.exe
Linux / macOS:
Bash

./bin/torre_hanoi
Estrutura do Projeto
src/: Contém todos os arquivos de código-fonte (.c e .h).
main.c: Contém a função main e a lógica do menu principal.
pilha.h, pilha.c: Implementação da estrutura de dados de Pilha, fundamental para as torres.
torre_hanoi.h, torre_hanoi.c: Lógica do jogo da Torre de Hanói, incluindo funções de exibição e movimento.
historico.h, historico.c: Gerenciamento do histórico de partidas, incluindo salvar, carregar, exibir e buscar.
bin/: Diretório onde o executável compilado será colocado.
Como Jogar
Ao iniciar, digite seu nome e o número de discos (de 3 a 10).
Para mover um disco, digite a letra da torre de origem (A, B ou C) e a letra da torre de destino (A, B ou C) quando solicitado.
As regras são:
Apenas um disco pode ser movido por vez.
Um disco maior nunca pode ser colocado sobre um disco menor.
O objetivo é mover todos os discos da Torre A para a Torre C.
Digite S ou s a qualquer momento para sair da partida em andamento.
O histórico de partidas é salvo automaticamente ao sair do programa.