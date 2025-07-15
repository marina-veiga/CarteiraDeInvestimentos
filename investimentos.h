#ifndef INVESTIMENTOS_H
#define INVESTIMENTOS_H
#include "leitura.h"

#define MAX_ACOES 1000

typedef struct {
    char id[2];       
    float custo;       
    float retorno;     
    float rendimento;  
} Acao;

Acao* carregarAcoes(int* totalAcoes);
Acao* ordenarPorRendimento(Acao* vetorOriginal, int tamanho);
void selecionarAcoes(Acao* vetorOrdenado, int quantidade_acoes, float capital, int i, Acao* escolhidas, int* totalEscolhidas, float* somaCustos, float* somaRetornos);

#endif