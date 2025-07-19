#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"  //inclui o nosso próprio arquivo de cabeçalho, onde estão declaradas as funções

float lerCapitalDisponivel() {
    FILE *arquivo;
    char linha[100]; //buffer para armazenar cada linha lida do arquivo
    float capital = 0.0; //variável que vai guardar o valor do capital

    arquivo = fopen("desafios\\iniciante.txt", "r"); //abre o arquivo para leitura
    if (arquivo == NULL) {
        printf(" Erro ao abrir o arquivo.\n");
        return -1;
    }

     //lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), arquivo)) {
        //procura por uma linha que contenha a informação do capital
        if (sscanf(linha, "CAPITAL_DISPONIVEL_R$: %f", &capital) == 1){
            break;
        }
    }

    fclose(arquivo);
    return capital; //retorna o valor do capital encontrado
}

int contarAcoes() { 
    FILE* arquivo; 
    char linha[100];
    int contador = 0; //contador de ações
    int lendoAcoes = 0; //flag que controla quando começar a contar
    arquivo = fopen("desafios\\iniciante.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }
    //lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        //procura a parte do arquivo onde começam as ações
        if (strstr(linha, "ACOES:") != NULL) {
            lendoAcoes = 1; //a partir daqui, começa a contar
            continue;
        }
        if (lendoAcoes) { 
            char codigoAcao[2];  //armazena o código da ação
            float custo, retorno;  //armazena os valores da ação

            //tenta ler os dados da linha no formato esperado
            if (sscanf(linha, "%s %f %f", codigoAcao, &custo, &retorno) == 3) {
                contador++; //se a linha tiver os 3 dados certos, conta como uma ação
            } 
        }
    }
    fclose(arquivo);
    return contador; //retorna quantas ações foram contadas
}
