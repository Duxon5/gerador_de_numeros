#include <locale.h>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>

using namespace std;
int qtd_arquivos = 0;

void sleepcp(int milliseconds);

void lista_quantidade_arquivo_pasta(const char *caminho);

std::string lista_arquivo_pasta(const char *caminho, int arquivo_escolhido);

char lista_conteudo_arquivo(const char *caminho, std::string& nome_arquivo);

int main() {
	setlocale (LC_ALL,"");
	const char *caminho = "./files";

	cout << "******CHAMANDO A FUNCAO lista_quantidade_arquivo_pasta\n\n";
	lista_quantidade_arquivo_pasta(caminho);

	cout << "******CHAMANDO A FUNCAO lista_arquivo_pasta\n\n";
	int escolha = 0;
	lista_arquivo_pasta(caminho, escolha);

	cout << "\nEscolha o número do arquivo desejado: ";
	cin >> escolha;

	cout << "******CHAMANDO A FUNCAO lista_arquivo_pasta\n";
	std::string nome_arquivo_escolhido;
	nome_arquivo_escolhido = lista_arquivo_pasta(caminho, escolha);
	cout << "\n\nArquivo escolhido (main) -> " << nome_arquivo_escolhido << "\n\n";

	cout << "******CHAMANDO A FUNCAO lista_conteudo_arquivo\n";

	lista_conteudo_arquivo(caminho, nome_arquivo_escolhido);

	cout << "\n\nFIM MAIN()";
}

void sleepcp(int milliseconds){
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end){}
}

void lista_quantidade_arquivo_pasta(const char *caminho){
	qtd_arquivos = 0;
	struct dirent *entrada;
	DIR *dir = opendir(caminho);

	if (dir == NULL){
		cout << "Diretório não encontrado.\n";
		exit(EXIT_FAILURE);
	}
	//verificando quantos arquivos tem na pasta
	while ((entrada = readdir(dir)) != NULL) {
		string tipo = entrada->d_name;
		int procura = tipo.find(".");
		string extensao = tipo.substr(procura + 1);
		if(extensao == "txt"){
			qtd_arquivos += 1;
		}
	}
	closedir(dir);
}

std::string lista_arquivo_pasta(const char *caminho, int arquivo_escolhido) {

	//Se na pasta houver ao menos um arquivo
	if(qtd_arquivos > 0){
		struct dirent *entrada;
		DIR *dir = opendir(caminho);

		//Mostra quando o usuário ainda não informou o arquivo
		if(arquivo_escolhido < 1)
			cout << "Foram encontrados " << qtd_arquivos << ", segue a relação abaixo:" << endl;

		int contador = 0;
		//IMPORTANTE: arquivos -> grava a posição + o nome do arquivo
		// 						arquivo_original -> grava o nome do arquivo.
		std::string cont_para_string, arquivos[qtd_arquivos], arquivo_original[qtd_arquivos];
		//grava os arquivos em um array
		while ((entrada = readdir(dir)) != NULL) {
			string tipo = entrada->d_name;
			int procura = tipo.find(".");
			string extensao = tipo.substr(procura + 1);
			if(extensao == "txt"){
				std::stringstream aux_string;
				aux_string << contador + 1;
				cont_para_string = aux_string.str();
				arquivos[contador] = cont_para_string + " - " + entrada->d_name;
				arquivo_original[contador] = entrada->d_name;
				//Mostra quando o usuário ainda não informou o arquivo
				if(arquivo_escolhido < 1)
					cout << arquivos[contador] << endl;
				contador += 1;
			}
		}
		closedir(dir);
		//Executa quando o usuário já escolheu o arquivo
		if(arquivo_escolhido > 0){
			std::string arquivo_escolhido_str;
			std::stringstream aux_string;
			aux_string << arquivo_escolhido;
			arquivo_escolhido_str = aux_string.str();
			//Compara a opção digitada com a posição dos arquivos. Mostra o arquivo que tiver a mesma opção.
			for(int i = 0; i < qtd_arquivos; i++){
				int procura_espaco = arquivos[i].find(" ");
				std::string primeira_posicao = arquivos[i].substr(0,procura_espaco);
					if(arquivo_escolhido_str == primeira_posicao){
						arquivo_escolhido_str = arquivo_original[i];
						break;
					}
			}
			//cout << "O arquivo escolhido foi: \n" << arquivo_escolhido_str << "\n\n";
			return arquivo_escolhido_str;
		}
	}else{
		cout << "Nenhum arquivo foi encontrado." << endl;
	}
}

char lista_conteudo_arquivo(const char *caminho, std::string& nome_arquivo){
	system("cls");
	//sleepcp(1500);
	std::string caminho_arquivo = caminho, linha;
	nome_arquivo = caminho_arquivo + "/" + nome_arquivo;

	cout << "\nO arquivo '" << nome_arquivo << "' será aberto.\n";
	std::ifstream arquivo (nome_arquivo.c_str());
	if(arquivo.is_open()){
		while(getline(arquivo, linha)){
			std::cout << linha << "\n";
		}
		arquivo.close();
	}

	/*DA PROXIMA VEZ Q CODIFICAR, SERÁ NECESSÁRIO REALIZAR TESTES PARA GRAVAR O CONTEÚDO NO ARQUIVO.
	Testar com os resultados do FOR abaixo
	*/
	int teste = 1;
	for(int i = 1; i <= 10; i++){
		for(int j = 1; j <= 10; j++){
			cout << teste << " ";
			teste = teste + 1;
		}
		cout << endl;
	}

}
