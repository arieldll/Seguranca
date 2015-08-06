#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int chave = 200;
	FILE *arq, *arqo, *arqw;
	arq = fopen("entrada-substituicao.txt", "r");
	arqo = fopen("texto-original.txt", "r");
	arqw = fopen("saida-transposicao.txt", "w");
	
	if(arq == NULL) printf("Não abriu");
	
	char dados[10000], dados1[10000];
	fgets(dados, 10000, arq);
	fgets(dados1, 10000, arqo);
	
	if(dados == NULL) printf("Não leu fgets");
	int i = 0;
	int p[256];
	for(i=0; i<256; i++){
		p[i] = -1;
	}
	for(i=0; i<strlen(dados); i++){
		p[dados[i]] = dados1[i];
	}
	for(i=0; i<256; i++){
		if(p[dados[i]]!=-1){
			printf("(%c) => (%c)\n", dados[i], p[dados[i]]);
		}
	}
	return 0; 
}
