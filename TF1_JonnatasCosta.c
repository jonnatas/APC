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

int cadastro(Legenda *legenda);
void exibirLegenda(Legenda *legenda, int tamanho);
void validarNumero(int numeroLegenda, Legenda *legenda, int posicao);
void validarNome(Legenda *legenda, int posicao);
void validarSigla(Legenda *legenda, int posicao);
void verificarSiglaVazio(Legenda *legenda, int posicao);
int validarSituacao(int lavaJato);
void zerarNumeros(Legenda *legenda);

//Variavel global para setar as repetições e evitar um laço para verificar as mesmas o(n) na busca
int numero_repeticoes[100];


int main(void)
{
	setlocale(LC_ALL, "Portuguese");
	// Declaracoes
	Legenda legenda[MAX_TAMANHO_LEGENDA];
	int tamanho;
	int listar;

	// Algoritimo
	memset(numero_repeticoes, 0, 100);
	tamanho = cadastro(legenda);

	system("clear");
	printf("Listar dados (S-sim): ");
	getchar();
	listar = getchar();
	if(listar=='S' || listar=='s')
		exibirLegenda(legenda, tamanho);
	return 0;
}

//Objetivo: Cadastrar todas as legendas  
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
int cadastro(Legenda *legenda){
	int i;
	char encerrar;
	int numeroLegenda;

	printf("Insira os dados dos canditados: \n");

	for(i=0; i<MAX_TAMANHO_LEGENDA; i++){
		//if your use windows, use sytem("cls");
		system("clear");
		printf("Candidato %d\n", i+1);

		printf("Nome completo: ");
		fgets(legenda[i].candidato.nome, MAXTAMANHONOME, stdin);
		validarNome(legenda, i);

		printf("Sigla do partido: ");
		fgets(legenda[i].sigla, MAXPARTIDO, stdin);
		validarSigla(legenda, i);

		printf("Número: ");
		scanf("%d", &numeroLegenda);
		validarNumero(numeroLegenda, legenda, i);

		getchar();
		printf("Situação na lavajato: ");
		legenda[i].candidato.lavaJato = getchar();
		validarSituacao(legenda[i].candidato.lavaJato);

		getchar();
		printf("Encerrar (S-sim)");
		encerrar = getchar();
		if(encerrar=='S' || encerrar=='s')
			break;
	}
	return i;
}

//Objetivo: Exibir todas as legendas  
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
void exibirLegenda(Legenda *legenda, int tamanho){
	int i;
	int numeroLegenda;
	for(i=0; i<=tamanho; i++){
		numeroLegenda=legenda[i].candidato.numeroLegenda;
		int numeroLegenda;
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
void validarNumero(int numeroLegenda, Legenda *legenda, int posicao){
	int i;
	while(numeroLegenda<10 || numeroLegenda>100 || numero_repeticoes[numeroLegenda] !=0){
		printf("Valor errado. insira novamente: ");
		scanf("%d", &numeroLegenda);
	}
	++numero_repeticoes[numeroLegenda];
	legenda[posicao].candidato.numeroLegenda = numeroLegenda;
}
