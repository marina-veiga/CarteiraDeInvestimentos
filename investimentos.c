#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "investimentos.h" //arquivo de cabeçalho com declarações e estrutura Acao

Acao* carregarAcoes(int* totalAcoes) {
    int quantidadeAcoes = contarAcoes(); //conta quantas ações existem no arquivo
    if (quantidadeAcoes <= 0){
        return NULL;
    }
    //grante que não passe do limite máximo de ações
    if (quantidadeAcoes > MAX_ACOES){ 
        quantidadeAcoes = MAX_ACOES;
    }  

    //aloca memória para guardar todas as ações
    Acao* vetorAcoes = malloc(quantidadeAcoes * sizeof(Acao));
    if (vetorAcoes == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    char linha[100];  // buffer para cada linha do arquivo
    int lendo = 0; //flag para começar a ler as ações só depois da linha "ACOES:"
    int index = 0; //indice do vetor de ações

    FILE* arquivo;
    arquivo = fopen("desafios\\iniciante.txt", "r"); 
    if (arquivo == NULL) {
        free(vetorAcoes); 
        return NULL;
    }

    //lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "ACOES:") != NULL) {
            lendo = 1; //começa a ler as ações depois dessa linha
            continue;
        }

        //lê o código, custo e retorno da ação
        if (lendo && index < quantidadeAcoes) {
            char codigoAcao[2];
            float custo, retorno;

            if (sscanf(linha, "%s %f %f", codigoAcao, &custo, &retorno) == 3) {
                strcpy(vetorAcoes[index].id, codigoAcao); //copia o ID
                vetorAcoes[index].custo = custo;   //define custo
                vetorAcoes[index].retorno = retorno; //define retorno
                vetorAcoes[index].rendimento = retorno / custo; //calcula o rendimento
                index++;
            } 
        }
    }

    fclose(arquivo);
    *totalAcoes = index;  //retorna a quantidade de ações carregadas
    return vetorAcoes;   //retorna o vetor com as ações
}

int compararRendimento(const void* primeiraAcao, const void* segundaAcao) {
    Acao acaoA = *(const Acao*)primeiraAcao;
    Acao acaoB = *(const Acao*)segundaAcao;

    //compara os rendimentos para ordenar do maior para o menor
   if (acaoA.rendimento < acaoB.rendimento){
    return 1;  //se A tem rendimento menor que B, A vai depois de B
   } else if (acaoA.rendimento> acaoB.rendimento){
    return -1;  //se A tem rendimento maior que B, A vai antes de B
   }else{ 
    return 0;  //são iguais, mantém a ordem
   }
   }



Acao* ordenarPorRendimento(Acao* vetorOriginal, int tamanho) {
    //cria uma nova cópia do vetor original para não alterar ele
    Acao* copiaOrdenada = malloc(tamanho * sizeof(Acao));
    if (copiaOrdenada == NULL) {  
        printf("Erro ao alocar memória para ordenação.\n");
        return NULL;
    }
    //copia os dados um por um e recalcula o rendimento
    for (int i = 0; i < tamanho; i++) {
        copiaOrdenada[i] = vetorOriginal[i];
        copiaOrdenada[i].rendimento = copiaOrdenada[i].retorno / copiaOrdenada[i].custo;
    }
    //usa a função qsort do C para ordenar pelo rendimento
    qsort(copiaOrdenada, tamanho, sizeof(Acao), compararRendimento);
    return copiaOrdenada; //retorna o vetor ordenado
}



void selecionarAcoes(Acao* vetorOrdenado, int quantidade_acoes, float capital, int i, Acao* escolhidas, int* totalEscolhidas, float* somaCustos, float* somaRetornos) {
    //caso base da recursão: já passou do final ou acabou o capital
    if (i >= quantidade_acoes || capital <= 0) {
        return;
    }
    //se a ação atual cabe no capital disponível
    if (vetorOrdenado[i].custo <= capital) {
        escolhidas[*totalEscolhidas] = vetorOrdenado[i]; //adiciona ao vetor de escolhidas
        *totalEscolhidas += 1; //atualiza total escolhidas
        *somaCustos += vetorOrdenado[i].custo; //soma o custo
        *somaRetornos += vetorOrdenado[i].retorno;  //soma o retorno
        capital -= vetorOrdenado[i].custo; //diminui o capital
    }

    //chama a função de novo para a próxima ação
    selecionarAcoes(vetorOrdenado, quantidade_acoes, capital, i + 1, escolhidas, totalEscolhidas, somaCustos, somaRetornos);
}