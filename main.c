#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"
#include "investimentos.h" //para manipular as ações (carregar, ordenar, selecionar)

int main() {
    //lê o valor do capital disponível no arquivo
    float capital = lerCapitalDisponivel();
    if (capital <= 0) { //verifica se o valor lido é válido
        printf("Capital invalido.\n");
        return 1;
    }

    int quantidadeTotalDeAcoes = 0;
    Acao* acoes = carregarAcoes(&quantidadeTotalDeAcoes); //lê e carrega as ações
    if (acoes == NULL) { //verifica se deu erro ao carregar
        printf("Erro ao carregar acoes.\n"); 
        return 1;
    }

    Acao* ordenadas = ordenarPorRendimento(acoes, quantidadeTotalDeAcoes);
    if (ordenadas == NULL) {
        printf("Erro ao ordenar ações.\n"); //verifica se deu erro na ordenação
        free(acoes); //libera o que já foi alocado
        return 1;
    }
    
    //prepara espaço para armazenar as ações escolhidas
    Acao* acoes_escolhidas = malloc(quantidadeTotalDeAcoes * sizeof(Acao));
    if (acoes_escolhidas == NULL) {
        printf("Erro ao alocar memória para escolhidas.\n");
        free(acoes);
        free(ordenadas);
        return 1;
    }
    //inicializa variáveis que vão guardar os resultados finais
    int totalEscolhidas = 0;
    float somaCustos = 0;
    float somaRetornos = 0;

    //executa a seleção das melhores ações que cabem no capital
    selecionarAcoes(ordenadas, quantidadeTotalDeAcoes, capital, 0, acoes_escolhidas, &totalEscolhidas, &somaCustos, &somaRetornos);
    printf("Capital Disponivel: R$ %.2f\n\n", capital); //mostra o capital disponível
    
    //lista as ações selecionadas para compra
    printf("Acoes a Comprar:\n");
    for (int i = 0; i < totalEscolhidas; i++) {
        printf("- Acao %s (Custo: R$ %.2f, Retorno: %.2f%%)\n", acoes_escolhidas[i].id, acoes_escolhidas[i].custo, acoes_escolhidas[i].retorno);
        
    }

    //mostra o resumo da carteira montada
    printf("\nResumo da Carteira:\n");
    printf("Custo Total: R$ %.2f\n", somaCustos);
    printf("Retorno Maximo Esperado: %.2f%%\n", somaRetornos);

    free(acoes);   //libera vetor original
    free(ordenadas);     //libera vetor ordenado
    free(acoes_escolhidas); //libera vetor de ações escolhidas

    return 0;
}