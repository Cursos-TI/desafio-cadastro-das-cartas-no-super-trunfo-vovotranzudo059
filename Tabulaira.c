#include <stdio.h>

#define ROWS 10
#define COLS 10

// Valores do tabuleiro
// 0 = Água
// 3 = Navio
// Na exibição: 5 = Área afetada (sobrepõe visualmente; priorizamos mostrar área afetada)
void imprimirTabuleiro(int board[ROWS][COLS], int affected[ROWS][COLS]) {
    // Impressão com prioridade: affected -> 5 ; else board value (3 ou 0)
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (affected[r][c] == 1) {
                printf("%d ", 5); // área afetada
            } else {
                printf("%d ", board[r][c]);
            }
        }
        printf("\n");
    }
}

// Função para sobrepor uma matriz de habilidade (skill) ao tabuleiro
// skill: matriz de 0/1 de tamanho skillSize x skillSize
// centerR, centerC -> coordenadas no tabuleiro onde o centro da skill será aplicado
// affected: matriz (ROWS x COLS) usada para marcar as células afetadas (1 = afetada)
void sobreporSkillNoTabuleiro(int board[ROWS][COLS], int affected[ROWS][COLS],
                              int skill[][7], int skillSize,
                              int centerR, int centerC) {
    // calc offset para alinhar centro da skill com (centerR, centerC)
    int half = skillSize / 2;

    // loops aninhados para percorrer a skill matrix e aplicar ao tabuleiro
    for (int sr = 0; sr < skillSize; sr++) {
        for (int sc = 0; sc < skillSize; sc++) {
            if (skill[sr][sc] == 1) {
                int boardR = centerR + (sr - half);
                int boardC = centerC + (sc - half);

                // valida limite do tabuleiro (condicional)
                if (boardR >= 0 && boardR < ROWS && boardC >= 0 && boardC < COLS) {
                    affected[boardR][boardC] = 1; // marcar como área afetada
                }
            }
        }
    }
}

// Constrói dinamicamente a matriz 'cone' (apontando para baixo) de tamanho n x n
// Regras: topo (linha 0) tem 1 no centro; a cada linha descendo a "base" expande.
// Ex: para n=5:
// 0 0 1 0 0
// 0 1 1 1 0
// 1 1 1 1 1
void construirCone(int cone[][7], int n) {
    int center = n / 2;

    // para cada linha r (0..n-1), definimos largura do cone na linha
    for (int r = 0; r < n; r++) {
        // calculamos quantas colunas à esquerda e direita do centro serão 1
        // à medida que r cresce, a largura aumenta (simula cone apontando para baixo)
        int halfWidth = r; // 0 na primeira linha, etc. (ajuste conforme desejado)
        for (int c = 0; c < n; c++) {
            // condição: se coluna c estiver dentro do intervalo [center-halfWidth, center+halfWidth]
            if (c >= center - halfWidth && c <= center + halfWidth) {
                cone[r][c] = 1;
            } else {
                cone[r][c] = 0;
            }
        }
    }
}

// Constrói dinamicamente a matriz 'cruz' (cross) n x n
// Regras: linha central e coluna central são 1
void construirCruz(int cruz[][7], int n) {
    int center = n / 2;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (r == center || c == center) {
                cruz[r][c] = 1;
            } else {
                cruz[r][c] = 0;
            }
        }
    }
}

// Constrói dinamicamente a matriz 'octaedro' (vista frontal -> losango/diamante) n x n
// Regras: abs(dr) + abs(dc) <= radius  (manter formato losango)
// Exemplo para n=5 (center=2, radius=2):
// 0 0 1 0 0
// 0 1 1 1 0
// 1 1 1 1 1
// 0 1 1 1 0
// 0 0 1 0 0
void construirOctaedro(int octa[][7], int n) {
    int center = n / 2;
    int radius = center; // para n impar, radius = center
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            int dr = r - center;
            int dc = c - center;
            if ((abs(dr) + abs(dc)) <= radius) {
                octa[r][c] = 1;
            } else {
                octa[r][c] = 0;
            }
        }
    }
}

int main() {
    // --- 1) Inicializa o tabuleiro 10x10 com água (0)
    int board[ROWS][COLS];
    int affected[ROWS][COLS]; // 1 = afetada pela habilidade, 0 = não afetada

    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            board[r][c] = 0;
            affected[r][c] = 0;
        }
    }

    // --- 2) Exemplo: posiciona alguns navios (valor 3) no tabuleiro
    // (posições definidas diretamente no código conforme simplificação)
    board[2][4] = 3;
    board[2][5] = 3;
    board[3][4] = 3;
    board[6][7] = 3;
    board[7][7] = 3;

    // --- 3) Define tamanhos e declara matrizes de habilidade (max 7x7)
    // Escolhi 5x5 para ficar legível, mas código suporta até 7x7 por declaração.
    const int skillSize = 5;
    int cone[7][7];  // usaremos apenas skillSize x skillSize
    int cruz[7][7];
    int octaedro[7][7];

    // --- 4) Construir as matrizes dinamicamente usando loops aninhados + condicionais
    construirCone(cone, skillSize);
    construirCruz(cruz, skillSize);
    construirOctaedro(octaedro, skillSize);

    // --- 5) Definir pontos de origem (centro) para cada habilidade no tabuleiro
    // Valores fixos conforme simplificação
    int origemConeR = 1, origemConeC = 4;   // perto do topo (cone apontando para baixo)
    int origemCruzR = 5, origemCruzC = 2;   // centro para cruz
    int origemOctaR = 7, origemOctaC = 7;   // centro para octaedro (losango)

    // --- 6) Sobrepor as habilidades ao tabuleiro (centro alinhado)
    // Observação: usamos a matriz 'affected' para marcar afetados; assim preservamos board[]
    sobreporSkillNoTabuleiro(board, affected, cone, skillSize, origemConeR, origemConeC);
    sobreporSkillNoTabuleiro(board, affected, cruz, skillSize, origemCruzR, origemCruzC);
    sobreporSkillNoTabuleiro(board, affected, octaedro, skillSize, origemOctaR, origemOctaC);

    // --- 7) Exibir resultados
    printf("Tabuleiro (0=agua, 3=navio, 5=area afetada) \n\n");
    imprimirTabuleiro(board, affected);

    // Para debugging/visualização: também mostramos as matrizes de habilidade construídas
    printf("\nMatriz Cone (1=afetado, 0=nao afetado):\n");
    for (int r = 0; r < skillSize; r++) {
        for (int c = 0; c < skillSize; c++) {
            printf("%d ", cone[r][c]);
        }
        printf("\n");
    }

    printf("\nMatriz Cruz (1=afetado, 0=nao afetado):\n");
    for (int r = 0; r < skillSize; r++) {
        for (int c = 0; c < skillSize; c++) {
            printf("%d ", cruz[r][c]);
        }
        printf("\n");
    }

    printf("\nMatriz Octaedro (1=afetado, 0=nao afetado):\n");
    for (int r = 0; r < skillSize; r++) {
        for (int c = 0; c < skillSize; c++) {
            printf("%d ", octaedro[r][c]);
        }
        printf("\n");
    }

    return 0;
}
