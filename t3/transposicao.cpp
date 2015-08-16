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
//LOVU C+++++++++++++++++++++++

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

int ranking_classificacao(char *str){
	/*std::size_t found = str.find(str2);
	if (found!=std::string::npos)
    std::cout << "first 'needle' found at: " << found << '\n';*/
    std::map<string, int>::iterator it;
    int contador = 0;
    string str_inteira = str;
	for(it = dicionario.begin(); it != dicionario.end(); it++)
	{
		string str_indice = it->first;
		std::size_t found = str_inteira.find(str_indice);
		if(found!=std::string::npos) contador++;
	}
	return contador;
}

int main(){	
	
	
	int chave = 0;	
	FILE *arq, *arqo, *arqw;
	
	arq = fopen("entrada-transposicao.txt", "r");
	arqw = fopen("saida-transposicao.txt", "w");
	
	carrega_dicionario();
	if(arq == NULL) printf("Não abriu");
	
	char dados[10000], dados1[10000];
	fgets(dados, 10000, arq);
	
	int i=0, t, j, ic; 
	
	if(dados == NULL) printf("Não leu fgets");
	
	int maiorchave = 0, classif = 0, indice = 0;
	for(t=1; t<strlen(dados); t++){
		char *chavx = (char *)malloc(sizeof(char)*strlen(dados));
		int tamanho_codificado = strlen(dados);
		int ldecod = trunc(tamanho_codificado / t); //quantidade de linhas
		int cdecod = trunc(tamanho_codificado / ldecod);
			
		int mdecod[cdecod][ldecod];
		ic = 0;
		int cc=0, cl=0;
		int max_linha = strlen(dados) / t; //t vai ser a chave agora
		int inc = 0;
		for(i=0; i<cdecod; i++){
			for(j=0; j<ldecod; j++){
				if(dados[inc]!=10){
					mdecod[i][j] = dados[inc++];
				}
			}
		}	
		
		inc = 0;
		for(i=0; i<ldecod; i++){
			for(j=0; j<cdecod; j++){
				chavx[inc++] = mdecod[j][i];
			}
		}
		int ehc = 0;
		for(i=strlen(chavx)-1; i>0; i--){
			if(chavx[i]!=' ') break;
			if(chavx[i]==' ') chavx[i] = '\0';
		}
		
		classif = ranking_classificacao(chavx);
		if(classif > maiorchave){
			classif = maiorchave;
			indice = t;
		}
		
		/*if(strcmp(chavx, dados1)==0){
			printf("---------------\nChave descoberta: %d\n--------------------\n", t);
			break;
		}else{
			//printf("chavx =>> [%s]==[%s]\n", chavx, dados1);
		} */
	}
	
	
	/*int i = 0, j = 0, tamanho_linhas = 0, icol = 0, ilinha = 0;
	tamanho_linhas = trunc(strlen(dados) / chave) + 1;
	int matrix[tamanho_linhas][chave];
	for(i=0; i<tamanho_linhas; i++){
		for(j=0; j<chave; j++){
			matrix[i][j] = ' '; //"Limpar" a matriz
		}
	}	
	for(i=0; i<strlen(dados); i++){
		int k = (int)dados[i];
		if(k!=10) matrix[ilinha][icol] = k; //ignorar a quebra de linha
		//int gerado = codificar(k, chave);
		//int decodificado = decodificar(gerado, chave);
		//printf(">%c - %c\n", gerado, decodificado);
		icol++;
		if(icol >= chave){
			icol = 0;
			ilinha++;
		}
	}
	
	printf("--------------%dx%d----------------\n", tamanho_linhas, chave);
	for(i=0; i<tamanho_linhas; i++){
		for(j=0; j<chave; j++){
			printf("%c", matrix[i][j]);
		}
		printf("\n");
	}
	printf("------------------------------\n");
	
	printf("Texto codificado: \n");
	char codificado[tamanho_linhas*chave];
	int ic = 0;
	for(i=0; i<chave; i++){
		for(j=0; j<tamanho_linhas; j++){
			printf("%c", matrix[j][i]);
			codificado[ic++] = matrix[j][i];
		}
	}
	printf("\n");
	printf("=================================\nTexto decodificado:\n");
	int tamanho_codificado = strlen(codificado);
	int ldecod = tamanho_codificado / chave; //quantidade de linhas
	int cdecod = tamanho_codificado / ldecod;
	int mdecod[cdecod][ldecod];
	ic = 0;
	int cc=0, cl=0;
	for(i=0; i<strlen(codificado); i++){
		mdecod[cc][cl] = codificado[i];
		cc++;
		if(cc>=chave){
			cc=0;
			cl++;
		}
	}
	for(i=0; i<ldecod; i++){
		for(j=0; j<cdecod; j++){
			printf("%c", matrix[i][j]);
		}
	}
	printf("\n========================================\n"); */
	printf("---------------\nChave aparentemente é: [%d]\n--------------------\n", indice);
	return 0; 
}
 
