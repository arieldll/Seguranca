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

int ContaValido(char c){
	//65 90 97 122
	if((c>=65 && c<=90) || (c>=97 && c<=122) || (c==' ')) return 1;
	return 0;
}

long int retornaClassificacao(char *str){
	int i = 0, conta = 0;
	for(i = 0; i<strlen(str); i++){
		conta += ContaValido(str[i]);
	}
	return conta;
}

int main(){
	int chave = 0;
	FILE *arq, *arqw, *arqo;
	arq = fopen("entrada-cesar.txt", "r");
	arqw = fopen("saida-cesar.txt", "w");
	if(arq == NULL) printf("Não abriu");
	if(arqw == NULL) printf("Não abriu 'w'");
	char dados[10000];
	fgets(dados, 10000, arq);
	if(dados == NULL) printf("Não leu fgets");
	int i = 0, maiorchave = 0, local_conta = 0, indice = 0;

	for(i=0; i<256; i++){
		char *frase = sdecodifica(dados, i);
		local_conta = retornaClassificacao(frase); 
		if(local_conta > maiorchave){
			maiorchave = local_conta;
			indice = i;
		}
	}
	printf("---------------\nChave aparentemente é: %d\n--------------------\n", indice);
	fclose(arqw);
	return 0; 
}
