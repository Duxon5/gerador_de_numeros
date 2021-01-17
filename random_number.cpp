#include <conio.h>
#include <ctime>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <tuple>

using namespace std;

bool delay = true;
bool cls = true;

int qtd_arquivos = 0;
bool arquivo_recarregado = false;

int **numSorteioOrganizado;
int qtd_apos;
int qtd_num;

void atraso(int milliseconds);

//Funcoes para sortear
tuple<int,int,int,int> recebeParametro();
int ** sorteiaNumero(int qtdApostas, int qtdNumeros, int menorNum, int maiorNum);
int ** organizaNumero(int qtdApostas, int qtdNumeros, int menorNum, int maiorNum, int **numSorteio);
int opcaoEscolhida();
int isInteiroPositivo();

//Funcoes para gravar
void listaQtdArquivoPasta(const char *caminho);
std::string listaArquivoPasta(const char *caminho, int arquivo_escolhido);
char listaConteudoArquivo(const char *caminho, std::string& nome_arquivo);
std::string criarArquivo(const char *caminho, string caminho_nome_arquivo);
char gravarArquivo(string caminho_nome_arquivo);
bool hasArquivo(std::string& nome_arquivo);
int arquivoEscolhido();
bool isExtensaoValida(string caminho_nome_arquivo);
string verificaExtensao(string caminho_nome_arquivo);

int main(){
  int qtdApostas, qtdNumeros, menorNum, maiorNum;
  tie(qtdApostas, qtdNumeros, menorNum, maiorNum) = recebeParametro();

  int **numSorteio = sorteiaNumero(qtdApostas, qtdNumeros, menorNum, maiorNum);

  numSorteioOrganizado = organizaNumero(qtdApostas, qtdNumeros, menorNum, maiorNum, numSorteio);

  int opEscolhida = opcaoEscolhida();

	return 0;
}

void atraso(int milliseconds){
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end){}
}

tuple<int,int,int,int> recebeParametro(){
  int qtdApostas, qtdNumeros, menorNum, maiorNum;
	cout << "**GERADOR DE NUMEROS QUE COM CERTEZA SERAO SORTEADOS NA MEGA DA VIRADA**\n";

	cout << "Qual sera a quantidade de apostas que serao feitas? ";
	qtdApostas = isInteiroPositivo();

	cout << "Qual sera a quantidade de numeros que serao apostados: ";
	qtdNumeros = isInteiroPositivo();

	bool menorNumXmaiorNum, maiorNumXqtdNumeros, difMenorNumXMaiorNum;
	do{
		menorNumXmaiorNum = true;
		maiorNumXqtdNumeros = true;
		difMenorNumXMaiorNum = true;

		cout << "\nQual o menor numero possivel? ";
		menorNum = isInteiroPositivo();

		cout << "Qual o maior numero do sorteio? ";
		maiorNum = isInteiroPositivo();
		if(menorNum >= maiorNum){
			menorNumXmaiorNum = false;
			cout << "\nO menor numero possivel deve ser menor que o maior numero possivel.";
		}
		if(maiorNum <= qtdNumeros){
			maiorNumXqtdNumeros = false;
			cout << "\nO maior numero possivel deve ser maior que a quantidade de numeros.";
		}
		if((menorNum + qtdNumeros) > maiorNum){
			difMenorNumXMaiorNum = false;
			cout << "\nO maior numero possivel deve ser " << qtdNumeros << " numeros maior que menor numero possivel.";
		}
	}while((menorNumXmaiorNum == false) || (maiorNumXqtdNumeros == false) || ((menorNum + qtdNumeros) > maiorNum));

	qtd_apos = qtdApostas;
	qtd_num = qtdNumeros;

  return {qtdApostas, qtdNumeros, menorNum, maiorNum};
}

int ** sorteiaNumero(int qtdApostas, int qtdNumeros, int menorNum, int maiorNum){
  if(delay==true)  atraso(2000);
  cout << "\nSORTEANDO NUMEROS...";
	if(delay==true)  atraso(3000);
	if(cls==true)  system("cls");

	srand (time(NULL));
  cout << "\n**NUMEROS SORTEADOS**";
	int** apostas = new int*[qtdApostas];
  int rNum, aux, i, j, k;

	for(i = 0; i < qtdApostas; i++){
		if(delay==true) atraso(25);
		apostas[i] = new int[qtdNumeros];
		for(j = 0; j < qtdNumeros; j++){
			if(delay==true)  atraso(50);
			rNum = rand() % maiorNum + menorNum;
			apostas[i][j] = rNum;
			//VALIDA SE O NUMERO É REPETIDO. CASO FOR, SORTEIA UM NOVO.
			bool diferente = false;
			for(k = 0; k < j; k++){
				do{
					if(rNum == apostas[i][k]){
						k = 0;
						diferente = true;
						rNum = rand() % maiorNum + menorNum;
						apostas[i][j] = rNum;
					}else{
						diferente = false;
					}
				}while(diferente != false);
			}
		}
	}

	//Mostrando os numeros sorteados
	int l, m;
	for(l = 0; l < qtdApostas; l++){
		cout << "\n" << l+1 << "\t";
		for(m = 0; m < qtdNumeros; m++){
			cout << apostas[l][m] << "	";
		}
	}

  return apostas;
}

int ** organizaNumero(int qtdApostas, int qtdNumeros, int menorNum, int maiorNum, int **numSorteio){
	if(delay==true)  atraso(2000);
	cout << "\n\n**APLICANDO ORDEM CRESCENTE NOS NUMEROS SORTEADOS...**\n";
	if(delay==true)  atraso(3000);
	if(cls==true)  system("cls");

  // int** apostas = new int*[qtdApostas];
  int aux, cont, i, j;

	for(i = 0; i < qtdApostas; i++){
    // apostas[i] = new int[qtdNumeros];
		for(cont = 0; cont < qtdNumeros; cont++){
			for(j = cont; j < qtdNumeros; j++){
				if(numSorteio[i][cont] >= numSorteio[i][j]){
					aux = numSorteio[i][cont];
					numSorteio[i][cont] = numSorteio[i][j];
					numSorteio[i][j] = aux;
				}
			}
		}
	}

	cout << "\n**RESULTADO**\n";
	if(delay==true)  atraso(25);
  cout << qtdApostas << " apostas | " << qtdNumeros << " NUMEROS por aposta\n";
	if(delay==true)  atraso(25);
  cout << "NUMEROS entre " << menorNum << " e " << maiorNum << endl;
	for(i = 0; i < qtdApostas; i++){
    cout << "\n" << i+1 << "\t";
		if(delay==true) atraso(25);
		for(j = 0; j < qtdNumeros; j++){
			if(delay==true)  atraso(50);
      cout << numSorteio[i][j] << "	";
		}
	}
  return numSorteio;
}

int opcaoEscolhida(){
	cout << "\n\n------------------------------------\n";
	cout << "\nO que voce deseja fazer com as apostas?";
	cout << "\n1 - Sortear novamente.";
	cout << "\n2 - Gravar o resultado em um arquivo de texto ja existente.";
	cout << "\n3 - Gravar o resultado em um novo arquivo de texto.";
	cout << "\n4 - Sair\nEscolha a opcao desejada -> ";
	int opcao = 5; //Setando 5 para poder entrar no WHILE
	while(opcao > 4){
		opcao = isInteiroPositivo();
		if(opcao > 4) cout << "Escolha entre 1 e 4 -> ";
	}
	cout << endl;

	switch(opcao){
		case 1:
			if(delay==true)  atraso(1000);
			cout << "\nO PROGRAMA SERA INICIADO NOVAMENTE.";
			if(delay==true)  atraso(2000);
			if(cls==true)  system("cls");
			return main();
		case 2:
			escolherArquivo:{
			const char *caminho = "./files";
			string nome_arquivo_escolhido;

			nome_arquivo_escolhido = listaArquivoPasta(caminho, 0);
				if(nome_arquivo_escolhido=="nao_existe") goto CriaArquivo;

			int escolha = arquivoEscolhido();
			nome_arquivo_escolhido = listaArquivoPasta(caminho, escolha);
				if(nome_arquivo_escolhido=="nao_existe") goto CriaArquivo;

			char lista_conteudo_arquivo = listaConteudoArquivo(caminho, nome_arquivo_escolhido);
				if(lista_conteudo_arquivo=='1') goto escolherArquivo;
				if(lista_conteudo_arquivo=='2') goto CriaArquivo;

			string caminho_str = caminho, nome_arquivo;
			nome_arquivo = caminho_str + "/" + nome_arquivo_escolhido;
			gravarArquivo(nome_arquivo);

			listaConteudoArquivo(caminho, nome_arquivo_escolhido);

			if(delay==true)  atraso(2000);
			cout << "\nPRESSIONE QUALQUER TECLA PARA ENCERRAR O PROGRAMA.\n";
			getch();
			if(cls==true)  system("cls");
			exit(EXIT_FAILURE);
			return 0;
		}
		case 3:{
			CriaArquivo:
			const char *caminho = "./files";

			string arquivo_criado = criarArquivo(caminho, "");
			if(delay == true)	atraso(2000);
			if(cls == true) system("cls");
			listaConteudoArquivo("", arquivo_criado);
			gravarArquivo(arquivo_criado);
			listaConteudoArquivo("", arquivo_criado);

			if(delay==true)  atraso(2000);
			cout << "\nPRESSIONE QUALQUER TECLA PARA ENCERRAR O PROGRAMA.\n";
			getch();
			if(cls==true)  system("cls");
			exit(EXIT_FAILURE);
			return 0;
		}
		case 4:
			if(cls==true)  system("cls");
			if(delay==true)  atraso(2000);
			cout << "\nO PROGRAMA SERA FINALIZADO.\n";
			if(delay==true)  atraso(3000);
			return 0;
	}
}

int isInteiroPositivo(){
	int valor = 0;
	cin >> valor;
	while(cin.fail() || valor <= 0) {
			cout << "Apenas numero inteiro positivo -> ";
			cin.clear();
			cin.ignore(256,'\n');
			cin >> valor;
	}
	return valor;
}

void listaQtdArquivoPasta(const char *caminho){
	qtd_arquivos = 0;
	struct dirent *entrada;
	DIR *dir = opendir(caminho);

	if (dir == NULL){
		mkdir(caminho);
	}
	//verificando quantos arquivos tem na pasta
	while ((entrada = readdir(dir)) != NULL) {
		string nome_arquivo = entrada->d_name;
		bool isExtensaoOk = isExtensaoValida(nome_arquivo);
		if(isExtensaoOk == true){
			qtd_arquivos += 1;
		}
	}
	closedir(dir);
}

std::string listaArquivoPasta(const char *caminho, int arquivo_escolhido) {
	listaQtdArquivoPasta(caminho);
	//Se na pasta houver ao menos um arquivo
	if(qtd_arquivos > 0){
		struct dirent *entrada;
		DIR *dir = opendir(caminho);
		//Mostra quando o usuArio ainda não informou o arquivo
		if(arquivo_escolhido < 1)
			cout << "Foram encontrados " << qtd_arquivos << " arquivos, segue a relacao abaixo:" << endl;

		int contador = 0;
		//IMPORTANTE: arquivos -> grava a posicão + o nome do arquivo
		// 						arquivo_original -> grava o nome do arquivo.
		std::string cont_para_string, arquivos[qtd_arquivos], arquivo_original[qtd_arquivos];
		//grava os arquivos em um array
		while ((entrada = readdir(dir)) != NULL) {
			string nome_arquivo = entrada->d_name;
			bool isExtensaoOk = isExtensaoValida(nome_arquivo);
			if(isExtensaoOk == true){
				std::stringstream aux_string;
				aux_string << contador + 1;
				cont_para_string = aux_string.str();
				arquivos[contador] = cont_para_string + " - " + entrada->d_name;
				arquivo_original[contador] = entrada->d_name;
				//Mostra quando o usuArio ainda não informou o arquivo
				if(arquivo_escolhido < 1)
					cout << arquivos[contador] << endl;
				contador += 1;
			}
		}
		closedir(dir);
		//Executa quando o usuArio jA escolheu o arquivo
		if(arquivo_escolhido > 0){
			std::stringstream aux_string;
			std::string arquivo_escolhido_str;
			aux_string << arquivo_escolhido;
			arquivo_escolhido_str = aux_string.str();
			//Compara a opcão digitada com a posicão dos arquivos. Mostra o arquivo que tiver a mesma opcão.
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
		}else{
			//passando algum valor string para o retorno;
			return "";
		}
	}else{
		cout << "Nenhum arquivo foi encontrado." << endl;
		int resposta = 0;
		/*CORRIGIR*/
		while(resposta != 1){
			cout << "Deseja criar um novo arquivo?\n1 - Sim\n2 - Nao\n-> ";
			cin >> resposta;
			if(resposta==1){
				return "nao_existe";
			}else if(resposta==2){
				cout << "O programa sera encerrado.\n";
				exit(EXIT_FAILURE);
			}else{
				if(delay == true)	atraso(1000);
				cout << "Opcão escolhida inexistente.\n-------------------------\n";
				if(delay == true)	atraso(1000);
				if(cls == true) system("cls");
			}
		}
	}
}

char listaConteudoArquivo(const char *caminho, std::string& nome_arquivo){
	if(delay==true){
		atraso(1500);
		if(cls == true) system("cls");
	}

	std::string caminho_arquivo = caminho, caminho_nome_arquivo, linha;
	if(caminho != ""){
		caminho_nome_arquivo = caminho_arquivo + "/" + nome_arquivo;
	}else{
		caminho_nome_arquivo = nome_arquivo;
	}

	if(arquivo_recarregado == false){
		cout << "Tentando carregar o arquivo selecionado...\n\n";
		if(delay==true)	atraso(1500);
	}else{
		cout << "CARREGANDO O ARQUIVO ATUALIZADO...\n";
		if(delay==true)	atraso(2000);
	}

	std::ifstream mostrar_arquivo (caminho_nome_arquivo.c_str());

	bool arq_existe = hasArquivo(caminho_nome_arquivo);
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
				cout << "\nGRAVANDO RESULTADOS...";
				if(delay==true)	atraso(1500);
				cout << "\n\nRESULTADOS GRAVADOS...\n";
				if(delay==true)	atraso(1500);
				if(cls == true) system("cls");
				arquivo_recarregado = true;
				mostrar_arquivo.close();
				// listaConteudoArquivo(caminho, nome_arquivo);
			}
		}
		return 'o';
	}else{
		cout << "O arquivo escolhido não existe mais. O que deseja fazer?";
		int escolha = 0;
		/*CORRIGIR ESSA PARTE*/
		while(escolha != 1){
			cout << "\n1 - Escolher um novo arquivo.\n2 - Criar um novo arquivo\n\nDigite uma opcão -> ";
			cin >> escolha;
			if(escolha==1){
				if(delay==true)	atraso(1500);
				if(cls == true) system("cls");
				return '1';
			}else if(escolha==2){
				if(delay==true)	atraso(1500);
				return '2';
			}else{
		    if(delay == true)	atraso(1000);
		    cout << "Opcão escolhida inexistente.\n-------------------------\n";
		    if(delay == true)	atraso(1000);
		    if(cls == true) system("cls");
		  }
		}
	}
}

std::string criarArquivo(const char *caminho, string caminho_nome_arquivo){
	//a funcao abaixo cria a pasta, caso nao exista.
	listaQtdArquivoPasta(caminho);
	bool isExtensaoOk = true;
	do{
		if(isExtensaoOk == false)	cout << "\nExtensao aceita apenas .txt ou .csv (minusculo)\n";
		cout << "Digite o nome do arquivo a ser criado: " << endl;
		cin >> caminho_nome_arquivo;

		isExtensaoOk = isExtensaoValida(caminho_nome_arquivo);
	}while(isExtensaoOk == false);

	string caminho_str = caminho;
	caminho_nome_arquivo = caminho_str + "/" + caminho_nome_arquivo;
	cout << "\nLocal do arquivo -> " << caminho_nome_arquivo << "\n";

	std::ofstream cria_arquivo;
	cria_arquivo.open(caminho_nome_arquivo, ios::app);
	return caminho_nome_arquivo;
}

char gravarArquivo(string caminho_nome_arquivo){
	fstream gravarArquivo(caminho_nome_arquivo, ios::app);
	string extensao = verificaExtensao(caminho_nome_arquivo);
	char tipo_espaco;
	if(extensao == "txt")	tipo_espaco = ' ';
	if(extensao == "csv")	tipo_espaco = ';';

	if(gravarArquivo.is_open()){
		gravarArquivo << endl;
		for(int i = 0; i < qtd_apos; i++){
			for(int j = 0; j < qtd_num; j++){
				gravarArquivo << numSorteioOrganizado[i][j] << tipo_espaco;
			}
			gravarArquivo << "\n";
		}
	}
}

bool hasArquivo(std::string& nome_arquivo){
    std::ifstream arquivo(nome_arquivo);
    return arquivo.good();
}

int arquivoEscolhido(){
	int valor = 0;
	cout << "\nEscolha o numero do arquivo desejado: ";
	cin >> valor;
	while(cin.fail() || valor <= 0) {
			cout << "Apenas nUmero inteiro positivo -> ";
			cin.clear();
			cin.ignore(256,'\n');
			cin >> valor;
	}
	return valor;
}

bool isExtensaoValida(string caminho_nome_arquivo){
		bool isExtensaoOk;
		string tipo = caminho_nome_arquivo;
		int procura = tipo.find(".");
		string extensao = tipo.substr(procura + 1);
		if((extensao == "txt") || (extensao == "csv")){
			isExtensaoOk = true;
		}else{
			isExtensaoOk = false;
		}
		return isExtensaoOk;
}

string verificaExtensao(string caminho_nome_arquivo){
	//Como o caminho possui pontuacao (./files), sera necessario procurar a segunda pontuacao (no caso a da extensao)
	int procura = caminho_nome_arquivo.find(".");
	string auxiliar = caminho_nome_arquivo.substr(procura + 1);
	procura = auxiliar.find(".");
	string extensao = auxiliar.substr(procura + 1);

	return extensao;
}
