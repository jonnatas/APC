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

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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
int exibirLegenda(Legenda *legenda, int tamanho);
int exibirLegendalavaJato(Legenda *legenda, int tamanho);
void validarNumero(char numeroLegenda[10], Legenda *legenda, int posicao);
void validarNome(Legenda *legenda, int posicao);
void validarSigla(Legenda *legenda, int posicao);
void verificarSiglaVazio(Legenda *legenda, int posicao);
int validarSituacao(int lavaJato);
void zerarNumeros(Legenda *legenda);
int inicializarLegenda(Legenda *legenda);
int apagarArquivo();
void removerPulaLinha(char *palavra);

//Variavel global para setar as repetições e evitar um laço para verificar as mesmas o(n) na busca
int numero_repeticoes[100];


int main(void)
{
	setlocale(LC_ALL, "Portuguese");
	// Declaracoes
	Legenda legenda[MAX_TAMANHO_LEGENDA];
	int tamanho, listar,numeroLegenda;
	int opcao;
	// Algoritimo

	(inicializarLegenda(legenda)>0) ? tamanho=inicializarLegenda(legenda) : tamanho=0;
		
	memset(numero_repeticoes, 0, 100);
	do{
		printf( ANSI_COLOR_MAGENTA " Menu de opções\n" ANSI_COLOR_RESET);
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
				exibirLegendalavaJato(legenda, tamanho);
				break;
			case 5:
				system("clear");
				apagarArquivo();
				break;
			case 0:
				break;
			default:
				system("clear");
				printf(ANSI_COLOR_RED "\n\tError valor invalido, insira novamente \n" ANSI_COLOR_RESET );
				break;
		}
	}while(opcao!=0);
	return 0;
}

//Objetivo: Inicializar a struct com os dados salvos no arquivo
//Entrada: Ponteiro para o arquivo e a legenda.
//Retorno: Total de itens lidos no arquivo.
int inicializarLegenda(Legenda *legenda){
	int c;
	int i=0;

	FILE *file;

	if(!(file=fopen("legenda.bin","r+"))){
		file=fopen("legenda.bin","w+");
		fclose(file);
		return 0;
	}
	if(file==NULL){
		printf(ANSI_COLOR_RED "\n\tError ao abrir o arquivo \n" ANSI_COLOR_RESET );
		fclose(file);
		return 0;
	}
	
	rewind(file);
	while(!feof(file)){
		fscanf(file,"%d\n", &i);
		fscanf(file,"%d\n", &legenda[i].candidato.numeroLegenda);
		fgets(legenda[i].candidato.nome , MAXTAMANHONOME, file);
		legenda[i].candidato.nome[strlen(legenda[i].candidato.nome)-1]='\0';
		fgets(legenda[i].sigla , MAX_TAMANHO_LEGENDA, file);
		legenda[i].sigla[strlen(legenda[i].sigla)-1]='\0';
		fscanf(file,"%d\n", &legenda[i].candidato.lavaJato);	
	}
	
	fclose(file);
	return (strlen(legenda[i].candidato.nome)==0)? 0 :i+1;
	
}

//Objetivo: Modificar dados de uma legenda  
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
int apagarArquivo(){
	FILE *file;
        file = fopen("legenda.bin", "w");
	if(file	== NULL){
		printf(ANSI_COLOR_RED "\n\tError ao apagar o arquivo!!!\n" ANSI_COLOR_RESET );
		return 1;
	}
	else{
		printf("\nArquivo apagado com sucesso, um novo arquivo foi criado!!!\n\n");
	}
	fclose(file);
	return 0;
}
//Objetivo: Modificar dados de uma legenda  
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
int modificar(Legenda *legenda, int tamanho){
	char lavaJato;
	int i, numeroLegenda, cancelar, continuarAlterando, opcaoModificar;

	getchar();
	printf("Cancelar e voltar? (Digite S): ");

	cancelar = getchar();
	if(cancelar=='S' || cancelar=='s')
		return 0;
	printf("Insira o numero da legenda do candidato: ");
	scanf("%d", &numeroLegenda);
	getchar();

	for(i=0; i<=tamanho; i++){
		if(legenda[i].candidato.numeroLegenda == numeroLegenda){
			//if your use windows, use sytem("cls");
			system("clear");
			
			printf( ANSI_COLOR_MAGENTA "\n Candidato %d\n" ANSI_COLOR_RESET, i+1);
			printf("\n Qual dado deseja alterar?\n");
			printf("\n [1] - Nome atual ( %s ), inserir novo", legenda[i].candidato.nome);
			printf("\n [2] - Sigla atual ( %s ), inserir nova", legenda[i].sigla);
			printf("\n [3] - Situação na lavaJato (%c), inserir nova\n", legenda[i].candidato.lavaJato);
			
			scanf("%d", &opcaoModificar);
			getchar();

			switch(opcaoModificar){
				case 1:
					printf("\nInserir novo nome: ", legenda[i].candidato.nome);
					fgets(legenda[i].candidato.nome, MAXTAMANHONOME, stdin);
					validarNome(legenda, i);
					break;
				case 2:
					printf("\nInserir nova sigla: ", legenda[i].sigla);
					printf("\tSigla atual ( %s ), inserir nova: ", legenda[i].sigla);
					fgets(legenda[i].sigla, MAXPARTIDO, stdin);
					validarSigla(legenda, i);
					break;
				case 3:
					printf("\tO candidato esta relacionado com a lavajato? (S-sim, N-não) : ", legenda[i].candidato.lavaJato);
					lavaJato=getchar();
					legenda[i].candidato.lavaJato = validarSituacao(lavaJato);
					break;
				default:
					printf("ERROR. Valor incorreto, digite novamente");
					printf(" Candidato %d\n", i+1);
					printf(" Qual dado deseja alterar?\n");
					printf("\t [1] - Nome atual ( %s ), inserir novo", legenda[i].candidato.nome);
					printf("\t [2] - Sigla atual ( %s ), inserir nova", legenda[i].sigla);
					printf("\t [3] - Situação na lavaJato (%c), inserir nova\n", legenda[i].candidato.lavaJato);
			}
			return 1;
		}
	}
	printf("\tNão encontrou-se a legenda %d ",numeroLegenda);
	return 0;
}


//Objetivo: Cadastrar todas as legendas  
//Entrada: legenda e posicao da legenda.
//Retorno: Total de itens exibidos, 0 caso falhe.
int cadastro(Legenda *legenda, int tamanho){
	int i;
	char encerrar, numeroLegenda[10], lavaJato;
	FILE *file = fopen("legenda.bin", "ab+");
	
	if(file	== NULL){
		printf(ANSI_COLOR_RED "\n\tError ao apagar o arquivo!!!\n" ANSI_COLOR_RESET );
		return 0;
	}

	for(i=tamanho; i<MAX_TAMANHO_LEGENDA; i++){
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

		printf("\tSituação na lavaJato (S-sim, N-Não): ");
		lavaJato=getchar();
		legenda[i].candidato.lavaJato = validarSituacao(lavaJato);

		fprintf(file,"%d\n", i);
		fprintf(file,"%d\n",legenda[i].candidato.numeroLegenda);
		fprintf(file,"%s\n", legenda[i].candidato.nome);
		fprintf(file,"%s\n",legenda[i].sigla);
		fprintf(file,"%d\n", legenda[i].candidato.lavaJato);

		printf("Encerrar (S-sim)");
		encerrar = getchar();
		if(encerrar=='S' || encerrar=='s')
			break;
	}
	i++;
	
	fclose(file);
	return i;
}

//Objetivo: Exibir candidatos com problemas na Lava Jato 
//Entrada: legenda e posicao da legenda.
//Retorno: total de itens exibidos corretamente, 0 caso nenhum dado encontrado.
int exibirLegendalavaJato(Legenda *legenda, int tamanho){
	int i;
	if(strlen(legenda[0].candidato.nome)==0){
		printf(ANSI_COLOR_RED "\n\tNenhum dado encontrado\n" ANSI_COLOR_RESET );
		return 0;
	}
	printf(ANSI_COLOR_YELLOW "Nº\tNúmero da legenda \tNome Completo \tSigla da Legenda \tSituação na lavajato\n" ANSI_COLOR_RESET);
	
	for(i=0; i<tamanho; i++){
		if(legenda[i].candidato.lavaJato=='S')
		{
			printf("%d", i);
			printf("\t\t%d",legenda[i].candidato.numeroLegenda);
			printf("\t\t%s", legenda[i].candidato.nome);
			printf("\t\t%s", legenda[i].sigla);
			printf("\t\tLava Jato\n");
		}
	}

	return i;
}


//Objetivo: Exibir todas as legendas  
//Entrada: legenda e posicao da legenda.
//Retorno: total de itens exibidos corretamente, 0 caso nenhum dado encontrado.
int exibirLegenda(Legenda *legenda, int tamanho){
	int i;
	if(strlen(legenda[0].candidato.nome)==0){
		printf(ANSI_COLOR_RED "\n\tNenhum dado encontrado\n" ANSI_COLOR_RESET );
		return 0;
	}
	printf(ANSI_COLOR_YELLOW "Nº\tNúmero da legenda \tNome Completo \tSigla da Legenda \tSituação na lavajato\n" ANSI_COLOR_RESET);
	
	for(i=0; i<tamanho; i++){
		printf("%d", i);
		printf("\t\t%d",legenda[i].candidato.numeroLegenda);
		printf("\t\t%s", legenda[i].candidato.nome);
		printf("\t\t%s", legenda[i].sigla);
		if(legenda[i].candidato.lavaJato=='S')
			printf("\t\tLava Jato", legenda[i].candidato.lavaJato);
		else
			printf("\t\tFicha Limpa", legenda[i].candidato.lavaJato);
		printf("\n");
	}
	return i;
}

//Objetivo: Validar o nome do usuário 
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
void validarNome(Legenda *legenda, int posicao){
	removerPulaLinha(legenda[posicao].candidato.nome);
	
	while(strlen(legenda[posicao].candidato.nome)<=0  || legenda[posicao].candidato.nome[0]=='\n' || legenda[posicao].candidato.nome[0]==' '){
		printf(ANSI_COLOR_RED "\tError. Nome Vazio, insira novamente: " ANSI_COLOR_RESET );
		fgets(legenda[posicao].candidato.nome, MAXTAMANHONOME, stdin);
		removerPulaLinha(legenda[posicao].candidato.nome);
	}
}

//Objetivo: Verificar ocorrencias de espaços em branco 
//Entrada: legenda e posicao da legenda.
//Retorno: nenhum.
void verificarSiglaVazio(Legenda *legenda, int posicao){
	removerPulaLinha(legenda[posicao].sigla);
	while(strlen(legenda[posicao].sigla)<=0  || legenda[posicao].sigla[0]=='\n' || legenda[posicao].sigla[0]==' '){
		printf(ANSI_COLOR_RED "\tError. Sigla Vazio, insira novamente: " ANSI_COLOR_RESET );
		fgets(legenda[posicao].sigla, MAXPARTIDO, stdin);
		removerPulaLinha(legenda[posicao].sigla);
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
				printf(ANSI_COLOR_RED "\tError valor existente insira novamente: " ANSI_COLOR_RESET );
				fgets(legenda[posicao].sigla, MAXPARTIDO, stdin);
				verificarSiglaVazio(legenda, posicao);
			}
		}
	}
}

//Objetivo: Remover pula linha
//Entrada: Uma string qualquer
//Retorno: String sem pula linha
void removerPulaLinha(char *palavra){
	int tamanho = strlen(palavra);
	palavra[tamanho-1]='\0';
}

//Objetivo: validar situação na lavaJato 
//Entrada: situação
//Retorno: situação devidamente validada
int validarSituacao(int lavaJato){
	
	while((lavaJato != 'S' && lavaJato != 'N')){
		int i;
		printf(ANSI_COLOR_RED "\tError, valor incorreto, insira (S-Sim ou N-Não): " ANSI_COLOR_RESET );
		lavaJato = getchar();
	}
	getchar();
	return lavaJato;
}

//Objetivo: validar numero da legenda
//Entrada: numero da legenda
//Retorno: sem retorno
void validarNumero(char numeroLegenda[10], Legenda *legenda, int posicao){
	int i;
	int numeroLegendaConvertido = atoi(numeroLegenda);

	while(numeroLegendaConvertido<10 || numeroLegendaConvertido>100 || numero_repeticoes[numeroLegendaConvertido]){
		printf(ANSI_COLOR_RED "\tError. Valor errado. insira novamente: " ANSI_COLOR_RESET );
		fgets(numeroLegenda, 10, stdin);
		numeroLegendaConvertido = atoi(numeroLegenda);
	}
	++numero_repeticoes[numeroLegendaConvertido];
	legenda[posicao].candidato.numeroLegenda = numeroLegendaConvertido;
}
