#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "investimentos.h"

int main() {
    float capital = lerCapitalDisponivel();
    if (capital <= 0) {
        printf("Capital invalido.\n");
        return 1;
    }

    int quantidadeTotalDeAcoes = 0;
    Acao* acoes = carregarAcoes(&quantidadeTotalDeAcoes);
    if (acoes == NULL) {
        printf("Erro ao carregar acoes.\n");
        return 1;
    }

    Acao* ordenadas = ordenarPorRendimento(acoes, quantidadeTotalDeAcoes);
    if (ordenadas == NULL) {
        printf("Erro ao ordenar ações.\n");
        free(acoes);
        return 1;
    }

    Acao* acoes_escolhidas = malloc(quantidadeTotalDeAcoes * sizeof(Acao));
    if (acoes_escolhidas == NULL) {
        printf("Erro ao alocar memória para escolhidas.\n");
        free(acoes);
        free(ordenadas);
        return 1;
    }

    int totalEscolhidas = 0;
    float somaCustos = 0;
    float somaRetornos = 0;

    
    selecionarAcoes(ordenadas, quantidadeTotalDeAcoes, capital, 0, acoes_escolhidas, &totalEscolhidas, &somaCustos, &somaRetornos);

    printf("\nMelhor combinacao encontrada:\n");
    printf("Acoes Selecionadas: {");

    int i;
    for (i = 0; i < totalEscolhidas; i = i + 1) {
        printf("%s", acoes_escolhidas[i].id);
        if (i < totalEscolhidas - 1) {
            printf(", ");
        }
    }
    printf("}\n");
    printf("Custo Total: R$ %.2f\n", somaCustos);
    printf("Retorno Total: %.2f%%\n", somaRetornos);

    free(acoes);
    free(ordenadas);   
    free(acoes_escolhidas);

    return 0;
}