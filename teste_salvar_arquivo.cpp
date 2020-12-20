#include <iostream>
#include <dirent.h>
#include <string.h>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <locale.h>
#include <ctime>
#include <string>

using namespace std;
void sleepcp(int milliseconds);

void sleepcp(int milliseconds){
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end){}
}

int list_dir() {
	//colocar a variável abaixo na função, se quiser chamar pelo main.
	const char *path = "./";
	
	struct dirent *entry;
	DIR *dir = opendir(path);
	
	if (dir == NULL) {
		return 0;
	}
	
	cout << "Arquivos encontrados na pasta atual: " << endl;
	
	int arq_escolha = 0;
	
	while ((entry = readdir(dir)) != NULL) {
		string tipo = entry->d_name;
		int procura = tipo.find(".");
		string extensao = tipo.substr(procura + 1);
		//cout << extensao << endl;
		if(extensao == "txt"){
			//sleepcp(250);
			cout << arq_escolha + 1 << " - ";
			arq_escolha += 1;
			cout << entry->d_name << endl;
		}
	}
	closedir(dir);
	
	return arq_escolha;
}

char list_file_content(int qtdArq){
	char filename[1000];
	ifstream file;
	
	//sleepcp(1500);
	cout << "\nQual arquivo será aberto?" << endl;
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

int main() {
	setlocale (LC_ALL,"");
	
	int qtd_arq = list_dir();

	list_file_content(qtd_arq);
}
