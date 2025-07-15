#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"

float lerCapitalDisponivel() {
    FILE *arquivo;
    char linha[100];
    float capital = 0.0; 

    arquivo = fopen("desafios\\iniciante.txt", "r");
    if (arquivo == NULL) {
        printf(" Erro ao abrir o arquivo.\n");
        return -1;
    }

    
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "CAPITAL_DISPONIVEL_R$: %f", &capital) == 1){
            break;
        }
    }

    fclose(arquivo);
    return capital;
}

int contarAcoes() { 
    FILE* arquivo; 
    char linha[100];
    int contador = 0;
    int lendoAcoes = 0;
    arquivo = fopen("desafios\\iniciante.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "ACOES:") != NULL) {
            lendoAcoes = 1; 
            continue;
        }
        if (lendoAcoes) { 
            char codigoAcao[2];
            float custo, retorno;
            if (sscanf(linha, "%s %f %f", codigoAcao, &custo, &retorno) == 3) {
                contador++;
            } 
        }
    }
    fclose(arquivo);
    return contador;
}
