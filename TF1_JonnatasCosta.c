//Nome: Jônnatas Lennon Lima Costa

/*
   Sintese
Objetivo: Cadastrar os canditados para uma possivel eleição. 
Entrada: Nome, numero da legenda, sigla do partido.
Saida: candidatos cadastrados.
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h>
#include <regex.h>

#define MAXPARTIDO 10
#define MAXTAMANHONOME 50
#define MAX_TAMANHO_LEGENDA 90

typedef struct Candidato{
	char nome[MAXTAMANHONOME];
	int lavaJato;
	int numeroLegenda;
}Candidato;

typedef struct Legenda{
	Candidato candidato;
	char sigla[MAXPARTIDO];
}Legenda;

int modificar(Legenda *legenda, int tamanho);
int cadastro(Legenda *legenda, int tamanho);
void exibirLegenda(Legenda *legenda, int tamanho);
void exibirLegendaLavajato(Legenda *legenda, int tamanho);
void validarNumero(char numeroLegenda[10], Legenda *legenda, int posicao);
void validarNome(Legenda *legenda, int posicao);
void validarSigla(Legenda *legenda, int posicao);
void verificarSiglaVazio(Legenda *legenda, int posicao);
int validarSituacao(int lavaJato);
void zerarNumeros(Legenda *legenda);
int inicializarLegenda(Legenda *legenda);

//Variavel global para setar as repetições e evitar um laço para verificar as mesmas o(n) na busca
int numero_repeticoes[100];


int main(void)
{
	setlocale(LC_ALL, "Portuguese");
	// Declaracoes
	Legenda legenda[MAX_TAMANHO_LEGENDA];
	int tamanho, listar,numeroLegenda, opcao;
	// Algoritimo

	//tamanho = inicializarLegenda(legenda);

	memset(numero_repeticoes, 0, 100);
	do{
		printf("\tOpções\n");
		printf("\n 1. Cadastrar novo candidato");
		printf("\n 2. Modificar dados do candidato");
		printf("\n 3. Listar todos os candidatos cadastrados");
		printf("\n 4. Selecionar os candidatos cadastrados que estão envolvidos com a Lava Jato");
		printf("\n 5. Apagar arquivo com cadastros de todos candidatos");
		printf("\n 0. Sair do programa\n");
		scanf("%d", &opcao);
		switch(opcao)
		{
			case 1:
				system("clear");
				getchar();
				tamanho = cadastro(legenda, tamanho);
				break;
			case 2:
				system("clear");
				modificar(legenda, tamanho);
				break;
			case 3:
				system("clear");
				exibirLegenda(legenda, tamanho);
				break;
			case 4:
				system("clear");
				exibirLegendaLavajato(legenda, tamanho);

				break;
		}
	}while(opcao!=0);
	return 0;
}
//Objetivo: Inicializar a struct com os dados salvos no arquivo
//Entrada: Ponteiro para o arquivo e a legenda.
//Retorno: nenhum.
int inicializarLegenda(Legenda *legenda){
	int c;
	int i=0;

	FILE *arquivo;
	if(!(arquivo=fopen("legenda.bin", "r")))
		arquivo=fopen("legenda.bin", "w+");
	if(arquivo==NULL){
		printf("Error ao abrir o arquivo");
		return 1;
	}
	while(!feof(arquivo)){
		printf("%d --> \n", i);
		fgets(legenda[i].candidato.nome, MAXTAMANHONOME, arquivo);
		fscanf(arquivo, "%d", &legenda[i].candidato.numeroLegenda);
		fgets(legenda[i].sigla, MAX_TAMANHO_LEGENDA, arquivo);
		fscanf(arquivo , "%c", &legenda[i].candidato.lavaJato);
		++i;
	}

	fclose(arquivo);
	return i+1;
}

//Objetivo: Modificar dados de uma legenda  
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
int modificar(Legenda *legenda, int tamanho){
	int i;
	int numeroLegenda;
	getchar();
	printf("Insira o numero da legenda do candidato");
	scanf("%d", &numeroLegenda);
	getchar();
	for(i=0; i<=tamanho; i++){
		if(legenda[i].candidato.numeroLegenda == numeroLegenda){
			//if your use windows, use sytem("cls");
			system("clear");
			printf("\tInsira os dados: \n");
			printf("\tCandidato %d\n", i+1);

			printf("\tNome atual ( %s ), inserir novo: ", legenda[i].candidato.nome);
			fgets(legenda[i].candidato.nome, MAXTAMANHONOME, stdin);
			validarNome(legenda, i);

			printf("\tSigla atual ( %s ), inserir nova: ", legenda[i].sigla);
			fgets(legenda[i].sigla, MAXPARTIDO, stdin);
			validarSigla(legenda, i);

			printf("\tSituação na lavajato (%c), inserir nova: ", legenda[i].candidato.lavaJato);
			legenda[i].candidato.lavaJato = getchar();
			validarSituacao(legenda[i].candidato.lavaJato);
			return 1;
		}
	}
	printf("\tNão encontrou-se a legenda %d ",numeroLegenda);
	return 0;
}


//Objetivo: Cadastrar todas as legendas  
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
int cadastro(Legenda *legenda, int tamanho){
	int i=0;
	char encerrar;
	char numeroLegenda[10];
	FILE *file = fopen("legenda.bin", "ab+");

	printf("Insira os dados dos canditados: \n");

	if(tamanho>0){
		i=tamanho+1;
	}
	else{
		i=tamanho;
	}
	for(i; i<MAX_TAMANHO_LEGENDA; i++){
		//if your use windows, use sytem("cls");
		system("clear");
		printf("\tCandidato %d\n", i+1);

		printf("\tNúmero: ");
		fgets(numeroLegenda, 10, stdin);
		validarNumero(numeroLegenda, legenda, i);

		printf("\tNome completo: ");
		fgets(legenda[i].candidato.nome, MAXTAMANHONOME, stdin);
		validarNome(legenda, i);

		printf("\tSigla do partido: ");
		fgets(legenda[i].sigla, MAXPARTIDO, stdin);
		validarSigla(legenda, i);

		printf("\tSituação na lavajato: ");
		legenda[i].candidato.lavaJato = getchar();
		validarSituacao(legenda[i].candidato.lavaJato);

		//fwrite(&legenda[i], sizeof(legenda[i]), 1, file);

		//fprintf(file,"%d\n", i);
		fprintf(file,"%d\n", legenda[i].candidato.numeroLegenda);
		fprintf(file,"%s\n", legenda[i].candidato.nome);
		fprintf(file,"%s\n", legenda[i].sigla);
		fprintf(file,"%c\n", legenda[i].candidato.lavaJato);

		getchar();
		printf("Encerrar (S-sim)");
		encerrar = getchar();
		if(encerrar=='S' || encerrar=='s')
			break;
	}
	fclose(file);
	if(tamanho==0)
		++i;
	return i;
}

//Objetivo: Exibir candidatos com problemas na Lava Jato 
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
void exibirLegendaLavajato(Legenda *legenda, int tamanho){
	int i;
	for(i=0; i<=tamanho; i++){
		if(legenda[i].candidato.lavaJato == 'S'){
			printf("Candidato %d\n", i+1);
			printf("\tNunero: %d\n",legenda[i].candidato.numeroLegenda);
			printf("\tNome: %s\n", legenda[i].candidato.nome);
			printf("\tSigla: %s\n", legenda[i].sigla);
			printf("\tlava Jato: %c\n", legenda[i].candidato.lavaJato);
		}
	}
}


//Objetivo: Exibir todas as legendas  
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
void exibirLegenda(Legenda *legenda, int tamanho){
	int i;
	for(i=0; i<=tamanho; i++){
		printf("Candidato %d\n", i+1);
		printf("\tNunero: %d\n",legenda[i].candidato.numeroLegenda);
		printf("\tNome: %s\n", legenda[i].candidato.nome);
		printf("\tSigla: %s\n", legenda[i].sigla);
		printf("\tlava Jato: %c\n", legenda[i].candidato.lavaJato);
	}
}

//Objetivo: Validar o nome do usuário 
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
void validarNome(Legenda *legenda, int posicao){
	legenda[posicao].candidato.nome[strlen(legenda[posicao].candidato.nome) -1] = '\0' ;
	while(strlen(legenda[posicao].candidato.nome)<=0  || legenda[posicao].candidato.nome[0]=='\n' || legenda[posicao].candidato.nome[0]==' '){
		printf("Error. Nome Vazio, insira novamente: ");
		fgets(legenda[posicao].candidato.nome, MAXTAMANHONOME, stdin);
		legenda[posicao].candidato.nome[strlen(legenda[posicao].candidato.nome) -1] = '\0' ;
	}
}

//Objetivo: Verificar ocorrencias de espaços em branco 
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
void verificarSiglaVazio(Legenda *legenda, int posicao){
	legenda[posicao].sigla[strlen(legenda[posicao].sigla) -1] = '\0' ;
	while(strlen(legenda[posicao].sigla)<=0  || legenda[posicao].sigla[0]=='\n' || legenda[posicao].sigla[0]==' '){
		printf("Error. Sigla Vazio, insira novamente: ");
		fgets(legenda[posicao].sigla, MAXPARTIDO, stdin);
		legenda[posicao].sigla[strlen(legenda[posicao].sigla) -1] = '\0' ;
	}
}

//Objetivo: validar sigla 
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
void validarSigla(Legenda *legenda, int posicao){
	int i;
	verificarSiglaVazio(legenda, posicao);
	if(posicao>0){
		for(i=0; i<posicao; i++){
			while(strcmp(legenda[posicao].sigla,legenda[i].sigla)==0){
				i=0;
				printf("Error valor existente insira novamente: ");
				fgets(legenda[posicao].sigla, MAXPARTIDO, stdin);
				verificarSiglaVazio(legenda, posicao);
			}
		}
	}
}

//Objetivo: validar situação na lavajato 
//Entrada: situação
//Retorno: situação devidamente validada
int validarSituacao(int lavajato){

	while(lavajato != 'S' && lavajato != 'N'){
		printf("Error, valor incorreto, insira (S-Sim ou N-Não): ");
		lavajato = getchar();	
	}

	return lavajato;
}

//Objetivo: validar numero da legenda
//Entrada: numero da legenda
//Retorno: sem retorno
void validarNumero(char numeroLegenda[10], Legenda *legenda, int posicao){
	int i;
	int numeroLegendaConvertido = atoi(numeroLegenda);

	while(numeroLegendaConvertido<10 || numeroLegendaConvertido>100 || numero_repeticoes[numeroLegendaConvertido]){
		printf("Valor errado. insira novamente: ");
		fgets(numeroLegenda, 10, stdin);
		numeroLegendaConvertido = atoi(numeroLegenda);
	}
	++numero_repeticoes[numeroLegendaConvertido];
	legenda[posicao].candidato.numeroLegenda = numeroLegendaConvertido;
}
