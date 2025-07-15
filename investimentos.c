#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "investimentos.h"

Acao* carregarAcoes(int* totalAcoes) {
    int quantidadeAcoes = contarAcoes();
    if (quantidadeAcoes <= 0){
        return NULL;
    }
    if (quantidadeAcoes > MAX_ACOES){ 
        quantidadeAcoes = MAX_ACOES;
    }  

    Acao* vetorAcoes = malloc(quantidadeAcoes * sizeof(Acao));
    if (vetorAcoes == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    char linha[100];
    int lendo = 0; //flag
    int index = 0;
    FILE* arquivo;
    arquivo = fopen("desafios\\iniciante.txt", "r"); 
    if (arquivo == NULL) {
        free(vetorAcoes); 
        return NULL;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "ACOES:") != NULL) {
            lendo = 1;
            continue;
        }

        if (lendo && index < quantidadeAcoes) {
            char codigoAcao[2];
            float custo, retorno;

            if (sscanf(linha, "%s %f %f", codigoAcao, &custo, &retorno) == 3) {
                strcpy(vetorAcoes[index].id, codigoAcao);
                vetorAcoes[index].custo = custo;
                vetorAcoes[index].retorno = retorno;
                vetorAcoes[index].rendimento = retorno / custo;
                index++;
            } 
        }
    }

    fclose(arquivo);
    *totalAcoes = index; 
    return vetorAcoes;
}

int compararRendimento(const void* primeiraAcao, const void* segundaAcao) {
    Acao acaoA = *(const Acao*)primeiraAcao;
    Acao acaoB = *(const Acao*)segundaAcao;

   if (acaoA.rendimento < acaoB.rendimento){
    return 1; 
   } else if (acaoA.rendimento> acaoB.rendimento){
    return -1; 
   }else{
    return 0; 
   }
   }



Acao* ordenarPorRendimento(Acao* vetorOriginal, int tamanho) {
    Acao* copiaOrdenada = malloc(tamanho * sizeof(Acao));
    if (copiaOrdenada == NULL) {  
        printf("Erro ao alocar memória para ordenação.\n");
        return NULL;
    }

    for (int i = 0; i < tamanho; i++) {
        copiaOrdenada[i] = vetorOriginal[i];
        copiaOrdenada[i].rendimento = copiaOrdenada[i].retorno / copiaOrdenada[i].custo;
    }

    qsort(copiaOrdenada, tamanho, sizeof(Acao), compararRendimento);
    return copiaOrdenada;
}



void selecionarAcoes(Acao* vetorOrdenado, int quantidade_acoes, float capital, int i, Acao* escolhidas, int* totalEscolhidas, float* somaCustos, float* somaRetornos) {
    if (i >= quantidade_acoes || capital <= 0) {
        return;
    }
    if (vetorOrdenado[i].custo <= capital) {
        escolhidas[*totalEscolhidas] = vetorOrdenado[i];
        *totalEscolhidas += 1;
        *somaCustos += vetorOrdenado[i].custo;
        *somaRetornos += vetorOrdenado[i].retorno;
        capital -= vetorOrdenado[i].custo;
    }
    selecionarAcoes(vetorOrdenado, quantidade_acoes, capital, i + 1, escolhidas, totalEscolhidas, somaCustos, somaRetornos);
}