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
	char chave[] = "";
	FILE *arq, *arqo, *arqw;
	arq = fopen("entrada-vigenere.txt", "r");
	arqo = fopen("texto-original.txt", "r");
	arqw = fopen("saida-vigenere.txt", "w");
	
	if(arq == NULL) printf("Não abriu");
	char dados[10000], dados1[10000];
	fgets(dados, 10000, arq);
	fgets(dados1, 10000, arqo);
	
	int i, j;
	char *ichave = (char *)malloc(sizeof(char)*strlen(dados));
	for(i=0; i<strlen(dados); i++){
		char carac_original = dados1[i];
		for(j=0; j<256; j++){
			int kdec = decodificar(dados[i], j);
			if(carac_original == kdec){
				ichave[i] = j;
			}
		}
	}
	printf("---------------\nChave descoberta: %s\n--------------------\n", ichave);
	fclose(arqw);
	return 0; 
}
