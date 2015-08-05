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

int main(){
	char chave[] = "abcabc";
	FILE *arq;
	arq = fopen("entrada.txt", "r");
	if(arq == NULL) printf("Não abriu");
	char dados[10000];
	fgets(dados, 10000, arq);
	if(dados == NULL) printf("Não leu fgets");
	int i = 0, pk = 0, rchave=0;
	for(i=0; i<strlen(dados); i++){
		int k = (int)dados[i];
		int kchave = (int)chave[rchave];
		int gerado = codificar(k, kchave);
		int decodificado = decodificar(gerado, kchave);
		printf(">%c - chave: [%c]- %c\n", gerado, kchave, decodificado); //se for uma quebra de linha ele não vai aparecer
		rchave++;
		if(rchave>=strlen(chave)) rchave = 0;
	}
	return 0; 
}
