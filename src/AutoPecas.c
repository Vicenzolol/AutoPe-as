/*
 ============================================================================
 Name        : AutoPecas.c
 Author      : Jefferson
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

/**
 * DEFINIÇÕES DE ESTRUTURAS E VARIAVEIS GLOBAIS
 */
int qtdPecasCadastradas, maxName;
char nomeArquivo[30] = "AutoPecas.txt";


struct Peca {
	int id;
	char nome[40];
	float preco;
};
struct Space {
	int id;
	char n[40];
	char p[10];
};
struct Peca pecas[40];
struct Space spaces[40];
// Testando
struct Lista {
	int maxName;
	int qtd;
	struct Peca pecas[40];
	int itens[40];
	struct Space spaces[40];
};
// NOME DA VARIAVEL ASK=PECA
struct Peca ask;
struct Lista list;
/**
 * DEFINIÇÕES DE METODOS
 **/
void limpar();
void limparOrcamento();
void parar();
void menu();
void exibirPecas();
void exibirPecasOrcamento();
void adicionaPeca();
void fecharArquivo(FILE *arquivo);
void inserirPeca(struct Peca *p);
void carregaLista();
void orcamento();
void gerarSpaces();
/**
 * DEFINIÇÕES DE FUNÇÕES
 **/
float pesquisaPrecoPeca(int id);
int getNewId();
FILE *abrirArquivo(char modo, char *caminho);
struct Peca buscaPeca(int id);

/**
 * MAIN = CODIGO PRINCIAPAL
 */
int main(void) {
	/**
	 * iniciando o sistema
	 * carregando os dados...
	 */
	setlocale(LC_ALL, "Portuguese");
	puts("CARREGANDO...");
	int opcao, a;
	float preco = 0.0;
	/**
	 * CARREGANDO ARQUIVO
	 */
	carregaLista();
	do {
		limpar();
		menu();
		puts("                 DIGITE UMA OPCAO");
		printf("                       ");
		scanf("%d",&opcao);
		switch(opcao){
		case 1:
			limpar();
			adicionaPeca();
			break;
		case 2:
			limpar();
			if(qtdPecasCadastradas > 0){
				puts("");
				puts("");
				puts(" Digite o codigo da peca!");
				printf("          : ");
				scanf("%d",&a);
				preco = pesquisaPrecoPeca(a);
				if(preco == -1){
					puts("Codigo nao encontrado!");
				} else {
					printf("PRECO: %.2f", preco);
				}
			} else {
				puts("Nao existe produtos cadastrados!");
			}
			break;
		case 3:
			limpar();
			if(qtdPecasCadastradas > 0){
				puts("");
				puts("");
				orcamento();
			} else {
				puts("Nao existe produtos cadastrados!");
			}
			break;
		case 4:
			limpar();
			exibirPecas();
			break;
		}
		if(opcao != 0){
			parar();
		}
	} while( opcao != 0);
	return EXIT_SUCCESS;
}
/**
 * IMPLEMENTAÇÃO DOS METODOS
 **/
void orcamento(){
	int qtd = 0, id = 0, i;
	carregaLista();
	limparOrcamento();
	do {
		limpar();
		puts("");
		exibirPecasOrcamento();
		puts("");
		puts("");
		puts(" Digite o codigo da peca! Ou Zero 0 pra sair.");
		printf("          ID : ");
		scanf("%d",&id);
		ask = buscaPeca(id);
		if(ask.id == 0){
			puts("Saindo do Orcamento!");
		} else {
			printf("  Quantidade : ");
			scanf("%d",&qtd);
			/**
			 * VIREFICANDO se o Item ja existe
			 */
			if(qtd > 0){
				for(i = 0; i < list.qtd; i++){
					if(list.pecas[i].id == ask.id){
						list.itens[i] += qtd;
						break;
					}
				}
				/**
				 * Se nao existir add nova peca no orcamento
				 */
				if((i) == list.qtd){
					list.pecas[i] = ask;
					list.itens[i] = qtd;
					list.qtd += 1;
				}
			}
		}
	} while (id != 0);
}
void carregaLista(){
	int x = 0, i, cont = 0, max = 0, j, y;
	float preco;
	struct Peca p;
	struct Space space;
	FILE *arquivo;
	arquivo = abrirArquivo('r', nomeArquivo);
	if(arquivo != NULL){
		while(!feof(arquivo)){
			fscanf(arquivo, "%d", &p.id);
			fscanf(arquivo, ";%[^;]s", p.nome);
			fscanf(arquivo, ";%f ", &p.preco);
			pecas[cont] = p;
			cont++;
			x = strlen(p.nome);
			if(max < x){
				max = x;
			}
		}
	}
	fecharArquivo(arquivo);
	maxName = max;
	qtdPecasCadastradas = cont;

	for(i = 0; i <= cont; i++){

		strcpy(space.n, "");
		strcpy(space.p, "");
		y = strlen(pecas[i].nome);
		preco = pecas[i].preco;
		x = max - y;
		// RECEBE CODIGO
		space.id = pecas[i].id;
		// PREENCHE O ESPACO DO NOME
		for(j = 0; j < x ; j++){
			strcat(space.n, " ");
		}
		// CALCULA O TAMANHO DO PRECO
		y = 0;
		if(preco > 9.99){
			if(preco > 99.99){
				if(preco > 999.99){
					if(preco > 9999.99) {
						y = 1;
					} else {
						y = 2;
					}
				} else {
					y = 3;
				}
			} else {
				y = 4;
			}
		} else {
			y = 5;
		}
		// PREENCHE O ESPACO DO PRECO
		for(j = 0; j < y ; j++){
			strcat(space.p, " ");
		}
		spaces[i] = space;
	}
}

void inserirPeca(struct Peca *p){
	FILE *arquivo;
	arquivo = abrirArquivo('a', nomeArquivo);
	fprintf(arquivo, "%d;%s;%f \n", (*p).id, (*p).nome, (*p).preco);
	fecharArquivo(arquivo);
}

void adicionaPeca(){
	printf("Adicionando os dados da peca!\n");
	ask.id = getNewId();
	printf("CODIGO: %d \n", ask.id);
	printf("NOME  : ");
	getchar();
	scanf("%[^\n]s", ask.nome);
	printf("VALOR : ");
	scanf("%f", &ask.preco);
	inserirPeca(&ask);
	limpar();
	puts("Peca cadastrada com sucesso!");
}

FILE *abrirArquivo(char modo, char *caminho){
	FILE *arquivo;
	switch (modo) {
	case 'a':
		arquivo = fopen(caminho, "a");
		break;
	case 'r':
		arquivo = fopen(caminho, "rt");
		break;
	case 'w':
		arquivo = fopen(caminho, "wt");
		break;
	}
	return arquivo;
}

void fecharArquivo(FILE *arquivo){
	fclose(arquivo);
}
void parar(){
	puts("");
	system("pause");
}
void limpar(){
	system("cls");
}
void menu(){
	puts("####################################################");
	puts("#               SISTEMA DE PECAS                   #");
	puts("####################################################");
	puts("#                                                  #");
	puts("#           1 - ADICIONAR PECA                     #");
	puts("#           2 - PESQUISA DE PRECO                  #");
	puts("#           3 - CALCULAR ORCAMENTO                 #");
	puts("#           4 - EXIBIR PECAS                       #");
	puts("#           0 - SAIR                               #");
	puts("#                                                  #");
	puts("####################################################");
}

float pesquisaPrecoPeca(int id){
	int i;
	for(i = 0; i <= qtdPecasCadastradas ; i++){
		if( i == (id - 1)){
			return pecas[i].preco;
		}
	}
	return -1;
}
struct Peca buscaPeca(int id){
	int i;
	for(i = 0; i <= qtdPecasCadastradas ; i++){
		if( i == (id - 1)){
			return pecas[i];
		}
	}
	ask.id = 0;
	return ask;
}

void exibirPecas(){
	int i, x = 0;
	char s[40] = "";
	char linha[40];
	carregaLista();
	// PREPARA O TITULO (4 - TAMANHO do NOME no TITULO)
	x = maxName - 4;
	for(i = 0; i < x ; i++){
		strcat(s, " ");
		strcat(linha,"-");
	}
	printf("  ID  |  NOME %s |      PRECO\n", s);
	printf("------+-------%s-+-----------\n",linha);
	for(i = 0; i < qtdPecasCadastradas ; i++){
		if(i <= 8){
			printf("   ");
		} else {
			printf("  ");
		}
		printf("%i  |  %s %s |  %s%.2f\n", pecas[i].id, pecas[i].nome, spaces[i].n, spaces[i].p, pecas[i].preco);
	}

}
void exibirPecasOrcamento(){
	int i, x = 0;
	char s[40] = "";
	char linha[40] = "";
	float total = 0;

	gerarSpaces();
	// PREPARA O TITULO (4 - TAMANHO do NOME no TITULO)
	x = list.maxName - 4;
	for(i = 0; i < x ; i++){
		strcat(s, " ");
		strcat(linha,"-");
	}
	printf(".------.-------%s-.-----.------------.\n",linha);
	printf("|  ID  |  NOME %s | QTD |      PRECO |\n", s);
	printf("|------+-------%s-+-----+------------|\n",linha);
	for(i = 0; i < list.qtd ; i++){
		if(list.pecas[i].id <= 9){
			printf("|   ");
		} else {
			printf("|  ");
		}
		printf("%i  |  %s %s | ", list.pecas[i].id, list.pecas[i].nome, list.spaces[i].n);
		if(list.itens[i] < 100){
			if(list.itens[i] < 10){
				printf("  ");
			} else {
				printf(" ");
			}
		}
		printf("%d |  %s%.2f |\n", list.itens[i], list.spaces[i].p, list.pecas[i].preco);

		total += list.itens[i] * list.pecas[i].preco;
	}
	printf("'------'-------%s-'-----'------------'\n\n",linha);
	printf("    %s     ITENS: %d     TOTAL: %.2f", s, list.qtd, total);
}
int getNewId(){
	qtdPecasCadastradas += 1;
	return qtdPecasCadastradas;
}
void gerarSpaces(){
	int i, j;
	for(i = 0; i < list.qtd; i++){
		for(j = 0; j < qtdPecasCadastradas ; j++){
			if(list.pecas[i].id == pecas[j].id){
				list.spaces[i] = spaces[j];
				break;
			}
		}
	}
}
void limparOrcamento(){
	list.qtd = 0;
	list.maxName = maxName;
}
