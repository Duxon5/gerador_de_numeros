#include <iostream>
#include <dirent.h>
#include <string.h>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <locale.h>
#include <ctime>

using namespace std;
void sleepcp(int milliseconds);

void sleepcp(int milliseconds){
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end){}
}
void list_dir(const char *path) {
	struct dirent *entry;
	DIR *dir = opendir(path);
	
	if (dir == NULL) {
		return;
	}
	
	cout << "Arquivos encontrados na pasta atual: " << endl;
	
	int arq_escolha = 1;
	
	while ((entry = readdir(dir)) != NULL) {
		string tipo = entry->d_name;
		int procura = tipo.find(".");
		string extensao = tipo.substr(procura + 1);
		//cout << extensao << endl;
		if(extensao == "txt"){
			//sleepcp(250);
			cout << arq_escolha << " - ";
			arq_escolha += 1;
			cout << entry->d_name << endl;
		}
	}
	closedir(dir);
}

char list_file_content(){
	char filename[50];
	ifstream file;
	string line;
	//sleepcp(1500);
	cout << "\nQual arquivo será aberto?" << endl;
	cin.getline(filename, 50);
	file.open(filename);
	
	if(!file.is_open()){
		exit(EXIT_FAILURE);
	}
	
	char word[50];
		
	file >> word;
	while(file.good()){
		cout << word;
		//cout << break_line << "\n";
		file >> word;
	}
}

int main() {
	setlocale (LC_ALL,"");
	
	list_dir("./");	
	
	list_file_content();
}
