#ifndef INVESTIMENTOS_H
#define INVESTIMENTOS_H
#include "leitura.h" //inclui o arquivo de cabeçalho leitura.h, pois vai usar funções ou tipos de lá

#define MAX_ACOES 1000 //define um valor fixo: o número máximo de ações que o programa vai trabalhar

//define uma estrutura chamada Acao
typedef struct {
    char id[2];     //código da ação
    float custo;    //quanto custa essa ação
    float retorno;  //quanto ela retorna
    float rendimento;   //retorno dividido pelo custo 
} Acao;

//declara a função carregarAcoes que vai ler as ações do arquivo e retornar um vetor de Acao
Acao* carregarAcoes(int* totalAcoes);  //o parâmetro totalAcoes é um ponteiro usado para devolver quantas ações foram lidas

Acao* ordenarPorRendimento(Acao* vetorOriginal, int tamanho); //declara a função que vai ordenar as ações por rendimento (da maior para a menor)

//declara a função que vai selecionar as melhores ações com base no capital disponível
void selecionarAcoes(Acao* vetorOrdenado, int quantidade_acoes, float capital, int i, Acao* escolhidas, int* totalEscolhidas, float* somaCustos, float* somaRetornos);

#endif