#include <locale.h>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

void sleepcp(int milliseconds);

int lista_pasta();

char lista_conteudo_arquivo(int qtdArq);

int main() {
	setlocale (LC_ALL,"");

	int qtd_arq = lista_pasta();

	lista_conteudo_arquivo(qtd_arq);
}

void sleepcp(int milliseconds){
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end){}
}

int lista_pasta() {
	//colocar a vari�vel abaixo na fun��o, se quiser chamar pelo main.
	const char *caminho = "./files";

	struct dirent *entrada;
	DIR *dir = opendir(caminho);

	if (dir == NULL) {
		return 0;
	}

	cout << "Arquivos encontrados na pasta atual: " << endl;

	int arq_escolha = 0;

	while ((entrada = readdir(dir)) != NULL) {
		string tipo = entrada->d_name;
		int procura = tipo.find(".");
		string extensao = tipo.substr(procura + 1);
		//cout << extensao << endl;
		if(extensao == "txt"){
			//sleepcp(250);
			cout << arq_escolha + 1 << " - ";
			arq_escolha += 1;
			cout << entrada->d_name << endl;
		}
	}
	closedir(dir);

	return arq_escolha;
}

char lista_conteudo_arquivo(int qtdArq){
	char filename[1000];
	ifstream file;

	//sleepcp(1500);
	cout << "\nQual arquivo ser� aberto?" << endl;
	cin.getline(filename, 1000);
	char firstPosition = filename[0];

	/*if(firstPosition == filename[0]){
		std::cout << "Igual";
		file.open(filename);
	}*/
	file.open(filename);
	if(!file.is_open()){
		exit(EXIT_FAILURE);
	}

	char word[1000];
	string line;

	file >> word;
	while(file.good()){
		file >> word;
		cout << word;
	}
}
