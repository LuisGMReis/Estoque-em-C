#include <stdio.h>
#include <string.h>


struct Produto {
    char nome[50];
    int quantidade;
};


void adicionarProduto(struct Produto *estoque, const char *nome, int quantidade, int *numProdutos) {
    strcpy(estoque[*numProdutos].nome, nome);
    estoque[*numProdutos].quantidade = quantidade;
    (*numProdutos)++;
}


void retirarProduto(struct Produto *estoque, const char *nome, int quantidade, int *numProdutos) {
    for (int i = 0; i < *numProdutos; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            if (estoque[i].quantidade >= quantidade) {
                estoque[i].quantidade -= quantidade;
                printf("Retirada de %d unidades de %s do estoque.\n", quantidade, nome);
            } else {
                printf("Erro: Estoque insuficiente para retirada de %d unidades de %s.\n", quantidade, nome);
            }
            return;
        }
    }
    printf("Erro: Produto %s não encontrado no estoque.\n", nome);
}


void inserirProduto(struct Produto *estoque, const char *nome, int quantidade, int *numProdutos) {
    for (int i = 0; i < *numProdutos; i++) {
        if (strcmp(estoque[i].nome, nome) == 0) {
            estoque[i].quantidade += quantidade;
            printf("Inserção de %d unidades de %s no estoque.\n", quantidade, nome);
            return;
        }
    }


    adicionarProduto(estoque, nome, quantidade, numProdutos);
}


void atualizarCSV(const char *nomeArquivo, struct Produto *estoque, int numProdutos) {
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", nomeArquivo);
        return;
    }


    fprintf(arquivo, "Produto,Quantidade\n");

    
    for (int i = 0; i < numProdutos; i++) {
        fprintf(arquivo, "%s,%d\n", estoque[i].nome, estoque[i].quantidade);
    }

    fclose(arquivo);
}


void lerCSV(const char *nomeArquivo, struct Produto *estoque, int *numProdutos) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para leitura.\n", nomeArquivo);
        return;
    }

   
    fscanf(arquivo, "%*[^\n]\n");

   
    while (fscanf(arquivo, "%49[^,],%d\n", estoque[*numProdutos].nome, &estoque[*numProdutos].quantidade) == 2) {
        (*numProdutos)++;
    }

    fclose(arquivo);
}

int main() {
    struct Produto estoque[5];
    int numProdutos = 0;

    
    lerCSV("estoque.csv", estoque, &numProdutos);

    
    int opcao;
    
    printf("1. Retirar produto do estoque\n");
    printf("2. Inserir produto no estoque\n");
    printf("Escolha uma operacao:\n");
    scanf("%d", &opcao);

    char nomeProduto[50];
    int quantidadeOperacao;

    printf("Informe o nome do produto: ");
    scanf("%s", nomeProduto);

    printf("Informe a quantidade: ");
    scanf("%d", &quantidadeOperacao);

	while (opcao =! 4) {
		
    switch (opcao) {
    	
        case 1:
            retirarProduto(estoque, nomeProduto, quantidadeOperacao, &numProdutos);
            return opcao;
        case 2:
            inserirProduto(estoque, nomeProduto, quantidadeOperacao, &numProdutos);
            return opcao;
        default:
            printf("Opcao invalida.\n");
            break;
            
            atualizarCSV("estoque.csv", estoque, numProdutos);
    
 }     
    return 0;   
}
    
}
