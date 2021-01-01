#include <iostream>
#include <string>
#include <sstream>
using namespace std;
static int qtd_arquivos_g = 0;

void recebe_qtd_arquivos(int qtd_entradas);

std::string * retorna_nome_arquivos();

void retorna_valor_digitado();

int main (){
	//chama a funcao e armazena seu valor em uma nova variavel.
	std::string* rec_retorna_nome_arquivos = retorna_nome_arquivos();

	//retorna_valor_digitado(rec_retorna_nome_arquivos);
	string valor_digitado;
	cout << "\nDigite: ";
	cin >> valor_digitado;

	std::string arquivo_escolhido;

	for(int i = 0; i < qtd_arquivos_g; i++){
		int procura_espaco = rec_retorna_nome_arquivos[i].find(" ");
		string primeira_posicao = rec_retorna_nome_arquivos[i].substr(0,procura_espaco);
		if(valor_digitado == primeira_posicao){
			arquivo_escolhido = rec_retorna_nome_arquivos[i];
			break;
		}
	}
	cout << "resultado: " << arquivo_escolhido;
}

void recebe_qtd_arquivos(int qtd_entradas){

}

std::string * retorna_nome_arquivos(){
	std::string palavras[] = {"oie", "eae mano", "beleza?", "bao?", "teste"};

	int qtd_arquivos = sizeof(palavras)/sizeof(palavras[0]);

	recebe_qtd_arquivos(qtd_arquivos);

	std::string i_para_string;
	std::string palavras_concat[120];

	for(int i = 0; i < qtd_arquivos_g; i++){
		std::stringstream aux_string;
		aux_string << i+1;
		i_para_string = aux_string.str();
		palavras_concat[i] = i_para_string + " - " + palavras[i];
		cout << palavras_concat[i] << endl;
	}
	return palavras_concat;
}

void retorna_valor_digitado(std::string* palavras_concat){

}
