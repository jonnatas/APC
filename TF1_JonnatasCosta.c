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

#define MAXSIGLA 10
#define MAXTAMANHONOME 50
#define MAX_TAMANHO_LEGENDA 90

typedef struct Candidato{
	char nome[MAXTAMANHONOME];
	int lavaJato;
}Candidato;

typedef struct Legenda{
	Candidato candidato;
	char sigla[MAXSIGLA];
	int numero;

}Legenda;

int cadastro(Legenda *legenda);
void exibirLegenda(Legenda *legenda, int tamanho);
void validarNumero(Legenda *legenda, int posicao);
void validarNome(Legenda *legenda, int posicao);
void validarSigla(Legenda *legenda, int posicao);

int main(void)
{
	setlocale(LC_ALL, "Portuguese");
	// Declaracoes
	Legenda legenda[MAX_TAMANHO_LEGENDA];
	int tamanho;

	// Algoritimo
	tamanho = cadastro(legenda);
	exibirLegenda(legenda, tamanho);
}

int cadastro(Legenda *legenda){
	int i;
	char encerrar;
	printf("Insira os dados dos canditados: \n");

	for(i=0; i<MAX_TAMANHO_LEGENDA; i++){
		//if your use windows, use sytem("cls");
		system("clear");
		printf("Candidato %d\n", i+1);

		printf("Número: ");
		scanf("%d", &legenda[i].numero);
		validarNumero(legenda, i);

		getchar();
		printf("Nome completo: ");
		fgets(legenda[i].candidato.nome, MAXTAMANHONOME, stdin);
		validarNome(legenda, i);

		printf("Sigla do partido: ");
		fgets(legenda[i].sigla, MAXSIGLA, stdin);
		validarSigla(legenda, i);

		printf("Situação na lavajato: ");
		legenda[i].candidato.lavaJato = getchar();
		getchar();


		printf("Encerrar (S-sim)");
		encerrar = getchar();
		if(encerrar=='S')
			break;
	}
	return i;
}

void exibirLegenda(Legenda *legenda, int tamanho){
	int i;
	for(i=0; i<=tamanho; i++){
		printf("Candidato %d\n", i+1);
		printf("\tNunero: %d\n",legenda[i].numero);
		printf("\tNome: %s\n", legenda[i].candidato.nome);
		printf("\tSigla: %s\n", legenda[i].sigla);
		printf("\tlava Jato: %c\n", legenda[i].candidato.lavaJato);
	}
}

void validarNome(Legenda *legenda, int posicao){
	legenda[posicao].candidato.nome[strlen(legenda[posicao].candidato.nome) -1] = '\0' ;
	while(strlen(legenda[posicao].candidato.nome)<=0  || legenda[posicao].candidato.nome[0]=='\n' || legenda[posicao].candidato.nome[0]==' '){
		printf("Error. Nome Vazio, insira novamente: ");
		fgets(legenda[posicao].candidato.nome, MAXTAMANHONOME, stdin);
		legenda[posicao].candidato.nome[strlen(legenda[posicao].candidato.nome) -1] = '\0' ;
	}
}

void verificarSiglaVazio(Legenda *legenda, int posicao){
	legenda[posicao].sigla[strlen(legenda[posicao].sigla) -1] = '\0' ;
	while(strlen(legenda[posicao].sigla)<=0  || legenda[posicao].sigla[0]=='\n' || legenda[posicao].sigla[0]==' '){
		printf("Error. Sigla Vazio, insira novamente: ");
		fgets(legenda[posicao].sigla, MAXSIGLA, stdin);
		legenda[posicao].sigla[strlen(legenda[posicao].sigla) -1] = '\0' ;
	}
}

void validarSigla(Legenda *legenda, int posicao){
	int i;
	verificarSiglaVazio(legenda, posicao);
	if(posicao>0){
		for(i=0; i<posicao; i++){
			while(strcmp(legenda[posicao].sigla,legenda[i].sigla)==0){
				i=0;
				printf("Error valor existente insira novamente: ");
				fgets(legenda[posicao].sigla, MAXSIGLA, stdin);
				verificarSiglaVazio(legenda, posicao);
			}
		}
	}
}

void validarNumero(Legenda *legenda, int posicao){
	while(legenda[posicao].numero<10 || legenda[posicao].numero>100){
		printf("Valor errado. insira novamente: ");
		scanf("%d", &legenda[posicao].numero);

	}
}


