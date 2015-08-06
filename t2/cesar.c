#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int codificar(int valor, int chave){
	int val = (int)valor + (int)chave;
	int x = val + (chave - chave % 256);
	return x;
}

int decodificar(int valor, int chave){
	int val = (int) valor - (int) chave;
	if(val<0){
		val = 256 + val;
	}
	return val;
}

char *sdecodifica(char *dados, int chave){
	char *ndados = (char *)malloc(sizeof(char)*strlen(dados));
	int i;
	for(i=0; i<strlen(dados); i++){
		ndados[i] = decodificar(dados[i], chave);
	}
	return ndados;
}

char *scodifica(char *dados, int chave){
	char *ndados = (char *)malloc(sizeof(char)*strlen(dados));
	int i;
	for(i=0; i<strlen(dados); i++){
		ndados[i] = codificar(dados[i], chave);
	}
	return ndados;
}

int main(){
	int chave = 0;
	FILE *arq, *arqw, *arqo;
	arq = fopen("entrada-cesar.txt", "r");
	arqo = fopen("texto-original.txt", "r");
	arqw = fopen("saida-cesar.txt", "w");
	if(arq == NULL) printf("Não abriu");
	if(arqo == NULL) printf("Não abriu 'o'");
	if(arqw == NULL) printf("Não abriu 'w'");
	char dados[10000], dados1[10000];
	fgets(dados, 10000, arq);
	fgets(dados1, 10000, arqo);
	if(dados == NULL) printf("Não leu fgets");
	if(dados == NULL) printf("Não leu fgets1");
	int i = 0;
	for(i=0; i<256; i++){
		if(strcmp(sdecodifica(dados, i), dados1)==0){
			printf("---------------\nChave descoberta: %d\n--------------------\n", i);			
		}
	}
	fclose(arqw);
	return 0; 
}
