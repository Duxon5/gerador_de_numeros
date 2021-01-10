// BUGS/PROBLEMAS
// [RESOLVIDO] QUANDO O NOVO ARQUIVO É CRIADO, É GRAVADO DUAS VEZES*
// QUANDO O ARQUIVO É EXCLUIDO, O PRÓXIMO É SELECIONADO*
// CORRIGIR do/while de lista_conteudo_arquivo e [resolvido]lista_arquivo_pasta

// MELHORIAS
// COLOCAR TXT e CSV na clausula, atualmente está txt e csv (converter todas extensoes para minusculo)*/
// CHECAR A PASTA, SE N EXISTIR -> cria_arquivo

#include <locale.h>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <ctime>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;
int qtd_arquivos = 0;
bool delay = true;
bool cls = false;
bool arquivo_recarregado = false;

void sleepcp(int milliseconds);
void lista_quantidade_arquivo_pasta(const char *caminho);
std::string lista_arquivo_pasta(const char *caminho, int arquivo_escolhido);
char lista_conteudo_arquivo(const char *caminho, std::string& nome_arquivo);
char criar_arquivo(const char *caminho, string caminho_nome_arquivo);
char grava_arquivo(string caminho_nome_arquivo);
bool arquivo_existe(std::string& nome_arquivo);

int main() {
	setlocale (LC_ALL,"");
	const char *caminho = "./files";

	lista_quantidade_arquivo_pasta(caminho);

	/*SERÁ NECESSÁRIO COLOCAR UM WHILE AQUI, POIS o lista_conteudo_arquivo NÃO VAI FUNCIONAR DO JEITO QUE ESTÁ*/
	int escolha = 0;
	lista_arquivo_pasta(caminho, escolha);

	cout << "\nEscolha o número do arquivo desejado: ";
	cin >> escolha;

	std::string nome_arquivo_escolhido;
	nome_arquivo_escolhido = lista_arquivo_pasta(caminho, escolha);
	cout << "\n\nArquivo escolhido (main) -> " << nome_arquivo_escolhido << "\n\n";

	lista_conteudo_arquivo(caminho, nome_arquivo_escolhido);
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
		if((extensao == "txt") || (extensao == "csv")){
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
			cout << "Foram encontrados " << qtd_arquivos << " arquivos, segue a relação abaixo:" << endl;

		int contador = 0;
		//IMPORTANTE: arquivos -> grava a posição + o nome do arquivo
		// 						arquivo_original -> grava o nome do arquivo.
		std::string cont_para_string, arquivos[qtd_arquivos], arquivo_original[qtd_arquivos];
		//grava os arquivos em um array
		while ((entrada = readdir(dir)) != NULL) {
			string tipo = entrada->d_name;
			int procura = tipo.find(".");
			string extensao = tipo.substr(procura + 1);
			if((extensao == "txt") || (extensao == "csv")){
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
			std::stringstream aux_string;
			std::string arquivo_escolhido_str;
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
		int resposta = 0;
		/*CORRIGIR*/
		while(resposta != 1){
			cout << "Deseja criar um novo arquivo?\n1 - Sim\n2 - Não\n-> ";
			cin >> resposta;
			if(resposta==1){
				criar_arquivo(caminho, "");
				if(delay == true)	sleepcp(2000);
				if(cls == true) system("cls");
				lista_quantidade_arquivo_pasta(caminho);
				lista_arquivo_pasta(caminho,0);
			}else if(resposta==2){
				cout << "O programa será encerrado.\n";
				exit(EXIT_FAILURE);
			}else{
				if(delay == true)	sleepcp(1000);
				cout << "Opção escolhida inexistente.\n-------------------------\n";
				if(delay == true)	sleepcp(1000);
				if(cls == true) system("cls");
			}
		}
	}
}

char lista_conteudo_arquivo(const char *caminho, std::string& nome_arquivo){
	if(delay==true){
		sleepcp(1500);
		if(cls == true) system("cls");
	}

	std::string caminho_arquivo = caminho, linha;
	string caminho_nome_arquivo = caminho_arquivo + "/" + nome_arquivo;
	if(arquivo_recarregado == false){
		cout << "Tentando carregar o arquivo selecionado...\n\n";
		if(delay==true)	sleepcp(1500);
	}else{
		cout << "CARREGANDO O ARQUIVO ATUALIZADO...\n";
		if(delay==true)	sleepcp(2000);
	}

	std::ifstream mostrar_arquivo (caminho_nome_arquivo.c_str());

	bool arq_existe = arquivo_existe(caminho_nome_arquivo);
	if(arq_existe == true){
		if(mostrar_arquivo.is_open()){
			cout << "----------------------------------------------------------------------" << endl;
			while(getline(mostrar_arquivo, linha)){
				std::cout << linha << "\n";
			}
			cout << "----------------------------------------------------------------------" << endl;

			if(arquivo_recarregado == false){
				cout << "Pressione qualquer tecla para gravar os resultados...\n";
				getch();
				/*FUNÇÃO PARA GRAVAR OS RESULTADOS AQUI*/
				criar_arquivo(caminho, caminho_nome_arquivo);
				cout << "\n\nGRAVANDO RESULTADOS...";
				if(delay==true)	sleepcp(1500);
				cout << "\n\nRESULTADOS GRAVADOS...";
				if(delay==true)	sleepcp(1500);
				if(cls == true) system("cls");
				arquivo_recarregado = true;
				mostrar_arquivo.close();
				lista_conteudo_arquivo(caminho, nome_arquivo);
			}
		}
	}else{
		cout << "O arquivo escolhido não existe mais. O que deseja fazer?";
		int escolha = 0;
		/*CORRIGIR ESSA PARTE*/
		while((escolha != 1)){
			cout << "\n1 - Escolher um novo arquivo.\n2 - Criar um novo arquivo\n\nDigite uma opção -> ";
			cin >> escolha;
			if(escolha==1){
				if(delay==true)	sleepcp(1500);
				if(cls == true) system("cls");
				lista_quantidade_arquivo_pasta(caminho);
				lista_arquivo_pasta(caminho,0);
			}else if(escolha==2){
				criar_arquivo(caminho,"");
				lista_quantidade_arquivo_pasta(caminho);

				if(delay == true)	sleepcp(1000);
				cout << "\nCarregando lista dos arquivos disponíveis...\n";
				if(delay == true)	sleepcp(1000);
				if(cls == true) system("cls");

				lista_arquivo_pasta(caminho,0);
			}else{
		    if(delay == true)	sleepcp(1000);
		    cout << "Opção escolhida inexistente.\n-------------------------\n";
		    if(delay == true)	sleepcp(1000);
		    if(cls == true) system("cls");
		  }
		}
	}
}

char criar_arquivo(const char *caminho, string caminho_nome_arquivo){
	std::ofstream cria_arquivo;

	if(caminho_nome_arquivo != ""){
		cout << "\nLocal do arquivo -> " << caminho_nome_arquivo << "\n";

		cria_arquivo.open(caminho_nome_arquivo, ios::app);
		grava_arquivo(caminho_nome_arquivo);
	}else{
		cout << "\nDigite o nome do arquivo a ser criado: " << endl;
		cin >> caminho_nome_arquivo;

		string caminho_str = caminho;
		caminho_nome_arquivo = caminho_str + "/" + caminho_nome_arquivo;
		cout << "\nLocal do arquivo -> " << caminho_nome_arquivo << "\n";

		cria_arquivo.open(caminho_nome_arquivo, ios::app);
	}
}

char grava_arquivo(string caminho_nome_arquivo){
	fstream grava_arquivo(caminho_nome_arquivo, ios::app);
	int teste = 1;
	if(grava_arquivo.is_open()){
		grava_arquivo << "\nGRAVANDO MAIS UMA LINHA" << endl;
		// for(int i = 1; i <= 10; i++){
		// 	for(int j = 1; j <= 10; j++){
		// 		grava_arquivo << teste << ";";
		// 		teste = teste + 1;
		// 	}
		// 	grava_arquivo << "\n";
		// }
		grava_arquivo.close();
	}

}

bool arquivo_existe(std::string& nome_arquivo){
    std::ifstream arquivo(nome_arquivo);
    return arquivo.good();
}
