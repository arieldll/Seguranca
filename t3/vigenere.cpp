#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include <cctype>
#include <map>
#include <stack>
#include <cstdlib>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>
#include <utility>


using namespace std;

std::map <string, int> dicionario;

vector<string> explode( const string &delimiter, const string &str)
{
    vector<string> arr;
 
    int strleng = str.length();
    int delleng = delimiter.length();
    if (delleng==0)
        return arr;//no change
 
    int i=0;
    int k=0;
    while( i<strleng )
    {
        int j=0;
        while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
        if (j==delleng)//found delimiter
        {
            arr.push_back(  str.substr(k, i-k) );
            i+=delleng;
            k=i;
        }
        else
        {
            i++;
        }
    }
    arr.push_back(  str.substr(k, i-k) );
    return arr;
}

void carrega_dicionario(){
	//std::ifstream t;
	//t.open("palavras.txt", "r");
	std::string dados = "casa;verde";
	//dados << t;
	vector<string> arr = explode(";", dados);
	for(int i=0; i<arr.size(); i++){
		dicionario[arr[i]] = 1;
	}
}


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

long int retornaClassificacao(char *str, int max){
	int i = 0, conta = 0;
	string strx = str;
	if(dicionario[strx]==1) conta++;
	/*for(i = 0; i<max; i++){
		conta += ContaValido(str[i]);
	} */
	return conta;
}

int main(){
	char chave[] = "";
	FILE *arq, *arqo, *arqw;
	arq = fopen("entrada-vigenere.txt", "r");
	arqw = fopen("saida-vigenere.txt", "w");
	
	carrega_dicionario(); //carrega palavras para o map
	
	if(arq == NULL) printf("Não abriu");
	char dados[10000], dados1[10000];
	fgets(dados, 10000, arq);
	
	int i, j, k, maiorchave = 0, classif = 0;
	char matrix[strlen(dados)][256];
	
	for(i=0; i<strlen(dados); i++){
		for(j=0; j<256; j++){
			int kdec = decodificar(dados[i], j);
			if(ContaValido(kdec)){
				matrix[i][j] = kdec;
			}else{
				matrix[i][j] = ' ';
			}
		}
		printf("\n");
	}
	
	char string_descoberta[10000];
	//procurar strings do dicionario
	char indice[strlen(dados)];
	for(i=0; i<strlen(dados); i++) indice[i] = '\0';
	for(i=0; i<256; i++){
		char *istring = (char *) malloc(sizeof(char)*strlen(dados));
		for(j=0; j<strlen(dados); j++){
			if(matrix[j][i] != ' '){
				istring[j] = matrix[j][i];
			}			
		}
		classif = retornaClassificacao(istring, strlen(dados));
		if(classif > maiorchave){
			maiorchave = classif;
			strcpy(string_descoberta, istring);
		}
	}
	
	//cálculo da chave
	for(i=0; i<strlen(string_descoberta) && i<strlen(dados); i++){
		int original = dados[i];
		int descrip = string_descoberta[i];
		int chave = original - descrip;
		indice[i] = chave;
	}
	printf("---------------\nChave aparentemente é: [%s]\n--------------------\n", indice);
	fclose(arqw);
	return 0; 
}
