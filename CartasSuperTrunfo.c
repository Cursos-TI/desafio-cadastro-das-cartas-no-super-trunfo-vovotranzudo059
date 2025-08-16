#include <stdio.h>
#include <stdio.h>

int main() {
    // Definição das variáveis da carta 1
    int populacao1, pontosTuristicos1;
    float area1, pib1;

    // Definição das variáveis da carta 2
    int populacao2, pontosTuristicos2;
    float area2, pib2;

    // Entrada dos dados da carta 1
    printf("Cadastro da Carta 1\n");
    printf("Populacao: ");
    scanf("%d", &populacao1);

    printf("Area: ");
    scanf("%f", &area1);

    printf("PIB: ");
    scanf("%f", &pib1);

    printf("Numero de pontos turisticos: ");
    scanf("%d", &pontosTuristicos1);

    // Entrada dos dados da carta 2
    printf("\nCadastro da Carta 2\n");
    printf("Populacao: ");
    scanf("%d", &populacao2);

    printf("Area: ");
    scanf("%f", &area2);

    printf("PIB: ");
    scanf("%f", &pib2);

    printf("Numero de pontos turisticos: ");
    scanf("%d", &pontosTuristicos2);

    // Exibição dos dados da carta 1
    printf("\n--- Carta 1 ---\n");
    printf("Populacao: %d\n", populacao1);
    printf("Area: %.2f\n", area1);
    printf("PIB: %.2f\n", pib1);
    printf("Pontos turisticos: %d\n", pontosTuristicos1);

    // Exibição dos dados da carta 2
    printf("\n--- Carta 2 ---\n");
    printf("Populacao: %d\n", populacao2);
    printf("Area: %.2f\n", area2);
    printf("PIB: %.2f\n", pib2);
    printf("Pontos turisticos: %d\n", pontosTuristicos2);

    return 0;
}


