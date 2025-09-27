#include <stdio.h>

// ---------------- TORRE (recursiva) ----------------
// A Torre anda em linha reta (vertical ou horizontal).
void moverTorre(int casas, char direcao[]) {
    if (casas == 0) return; // caso base da recursão
    printf("%s\n", direcao);
    moverTorre(casas - 1, direcao); // chamada recursiva
}

// ---------------- BISPO (recursiva + loops aninhados) ----------------
// O Bispo anda em diagonal (um passo vertical + um horizontal por vez).
void moverBispo(int casas) {
    if (casas == 0) return; // caso base da recursão

    // Loops aninhados simulam o movimento diagonal
    for (int v = 0; v < 1; v++) {      // movimento vertical
        for (int h = 0; h < 1; h++) {  // movimento horizontal
            printf("Cima\n");
            printf("Direita\n");
        }
    }

    moverBispo(casas - 1); // chamada recursiva
}

// ---------------- RAINHA (recursiva) ----------------
// A Rainha pode andar como Torre ou Bispo.
// Aqui simulamos "Cima + Direita" repetidamente.
void moverRainha(int casas) {
    if (casas == 0) return; // caso base da recursão

    printf("Cima\n");
    printf("Direita\n");

    moverRainha(casas - 1); // chamada recursiva
}

// ---------------- CAVALO (loops complexos) ----------------
// O Cavalo anda em "L": duas casas para cima + uma para direita.
void moverCavalo() {
    int passosCima = 2;
    int passosDireita = 1;

    printf("\n=== Movimento do Cavalo ===\n");

    for (int i = 0; i < passosCima + passosDireita; i++) {
        if (i < passosCima) {
            printf("Cima\n");
            continue; // controla o fluxo, volta para o for
        }
        for (int j = 0; j < passosDireita; j++) {
            printf("Direita\n");
            break; // garante que só ande 1 vez para a direita
        }
    }
}

// ---------------- MAIN ----------------
int main() {
    printf("=== Movimento da Torre ===\n");
    moverTorre(3, "Cima");

    printf("\n=== Movimento do Bispo ===\n");
    moverBispo(3);

    printf("\n=== Movimento da Rainha ===\n");
    moverRainha(3);

    moverCavalo();

    return 0;
}
