# Carteira De Investimentos
## Descrição
Este programa foi desenvolvido para avaliação da P3 da disciplina Linguagem de Programação I da Universidade Federal do Maranhão (UFMA), utilizando a linguagem de programação C. Ele tem como objetivo ler um arquivo que contém as ações disponíveis e o capital disponível, e a partir dessas informações, calcular a melhor combinação possível de ações que podem ser compradas com o capital informado. O objetivo é obter o maior rendimento total, sem ultrapassar o valor disponível.

## Como Executar
- **Compilador C** (ex: GCC ou MinGW)
- **Git** (para clonar o repositório)

1. Clone o repositório
```bash
git clone https://github.com/marina-veiga/CarteiraDeInvestimentos
cd CarteiraInvestimento
```

2. Compile o código:
```bash
gcc main.c leitura.c investimentos.c -o programa.exe
```
3. Execute o programa:

```bash
.\programa.exe
```
> A pasta `desafios` deve estar na mesma pasta do programa e conter arquivos como `iniciante.txt`, `moderado.txt`, etc.
---

## Estrutura do Código
- `main.c`: Contém a lógica principal do programa.
- `leitura.c`: Responsável por ler os arquivos.
- `investimentos.c`: Contém a lógica de seleção das ações.
- `desafios/`: Pasta com arquivos de entrada contendo as ações por perfil (iniciante, moderado, difícil, expert).

## Como funciona o programa
- O usuário escolhe um dos arquivos da pasta `desafios` (por exemplo, `iniciante.txt`).
- O programa lê as ações e o capital disponível desse arquivo.
- Calcula o rendimento de cada ação com a fórmula: **rendimento = retorno / custo**.
- Utiliza um algoritmo ganancioso (greedy) que seleciona as ações em ordem decrescente de rendimento, escolhendo a melhor opção que cabe no capital disponível.
- Exibe a melhor combinação de ações para comprar, mostrando o custo total e o retorno esperado.

---

## Struct Principal
O programa usa uma struct para guardar as informações de cada ação que lê do arquivo.  
```c
typedef struct {
    char id[2];           
    float custo;           
    float retorno;         
    float rendimento;      
} Acao;
```
## Funções Principais

#### `lerCapitalDisponivel()`
- Pega do arquivo quanto dinheiro tem pra investir.
  
#### `contarAcoes()`
- Conta quantas ações tem no arquivo.

#### `carregarAcoes()`
- Lê as ações do arquivo e guarda tudo em um array pra usar depois.

#### `comprarPorRendimento()`
- Escolhe as melhores ações pra comprar, olhando o rendimento delas.  
- Sempre pega as que têm o maior rendimento, sem passar do dinheiro disponível.

## Exemplo de Entrada do Arquivo

```plaintext
# Estratégia: Carteira Iniciante
# Formato: ID Custo_Acao(R$) Retorno_Anual(%) Ticker_Acao
CAPITAL_DISPONIVEL_R$: 1000.00
ACOES:
A 400.00 10.0 BIGCORP4
B 600.00 12.0 SAFETECH3
C 350.00 8.0 VALIOSA1
D 250.00 5.0 ESTAVEL5
```
## Exemplo de Saída no Terminal
```plaintext
Melhor combinação encontrada:
Ações Selecionadas: {A, C, D}
Custo Total: R$ 1000.00
Retorno Total: 23.00% 
```
## Autores
Este projeto foi desenvolvido por: **Diogo Costa** e **Marina Veiga**
