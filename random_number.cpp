#include <stdlib.h>
#include <ctime>
#include <locale.h>
#include <iostream>
#include <time.h>
#include <tuple>
#include <sstream>

using namespace std;

bool delay = false;
bool cls = false;

void sleepcp(int milliseconds);

tuple<int,int,int,int> recebeParametro();
int ** sorteiaNumero(int qtdApostas, int qtdNumeros, int menorNum, int maiorNum);
int ** organizaNumero(int qtdApostas, int qtdNumeros, int menorNum, int maiorNum, int **numSorteio);
int opcaoEscolhida();
int isInteiroPositivo();

int main(){
	setlocale (LC_ALL,"");

  int qtdApostas, qtdNumeros, menorNum, maiorNum;
  tie(qtdApostas, qtdNumeros, menorNum, maiorNum) = recebeParametro();

  int **numSorteio = sorteiaNumero(qtdApostas, qtdNumeros, menorNum, maiorNum);

  int **numSorteioOrganizado = organizaNumero(qtdApostas, qtdNumeros, menorNum, maiorNum, numSorteio);

  int opEscolhida = opcaoEscolhida();

	return 0;
}

void sleepcp(int milliseconds){
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end){}
}

tuple<int,int,int,int> recebeParametro(){
  int qtdApostas, qtdNumeros, menorNum, maiorNum;
	cout << "**GERADOR DE NÚMEROS QUE COM CERTEZA SERÃO SORTEADOS NA MEGA DA VIRADA**\n";

	cout << "Qual será a quantidade de apostas que serão feitas? ";
	qtdApostas = isInteiroPositivo();

	cout << "Qual será a quantidade de números que serão apostados: ";
	qtdNumeros = isInteiroPositivo();

	cout << "\nQual o menor número possível? ";
	menorNum = isInteiroPositivo();

	cout << "Qual o maior número do sorteio? ";
	maiorNum = isInteiroPositivo();

  return {qtdApostas, qtdNumeros, menorNum, maiorNum};
}

int ** sorteiaNumero(int qtdApostas, int qtdNumeros, int menorNum, int maiorNum){
  if(delay==true)  sleepcp(2000);
  cout << "\nSORTEANDO NÚMEROS...";
	if(delay==true)  sleepcp(3000);
	if(cls==true)  system("cls");

	srand (time(NULL));
  cout << "\n**NUMEROS SORTEADOS**";
	int** apostas = new int*[qtdApostas];
  int rNum, aux, i, j, k, diferente = 1;

	for(i = 0; i < qtdApostas; i++){
    cout << "\n" << i+1 << "\t";
    apostas[i] = new int[qtdNumeros];

		if(delay==true) sleepcp(25);
		for(j = 0; j < qtdNumeros; j++){
			if(delay==true)  sleepcp(50);
			rNum = rand() % maiorNum + menorNum;

      cout << rNum << "	";

			apostas[i][j] = rNum;

			//VALIDA SE O NÚMERO É REPETIDO. CASO FOR, SORTEIA UM NOVO.
			for(k = 0; k < j; k++){
				do{
					if(rNum == apostas[i][k]){
						diferente = 0;
						rNum = rand() % maiorNum + menorNum;
						apostas[i][j] = rNum;
					}else{
						diferente = 1;
					}
				}while(diferente != 1);
			}
		}
	}
  return apostas;
}

int ** organizaNumero(int qtdApostas, int qtdNumeros, int menorNum, int maiorNum, int **numSorteio){
	if(delay==true)  sleepcp(2000);
	cout << "\n\n**APLICANDO ORDEM CRESCENTE NOS NÚMEROS SORTEADOS...**\n";
	if(delay==true)  sleepcp(3000);
	if(cls==true)  system("cls");

  // int** apostas = new int*[qtdApostas];
  int aux, cont, i, j;

	for(i = 0; i < qtdApostas; i++){
    // apostas[i] = new int[qtdNumeros];
		for(cont = 0; cont < qtdNumeros; cont++){
			for(j = cont; j < qtdNumeros; j++){
				if(numSorteio[i][cont] > numSorteio[i][j]){
					aux = numSorteio[i][cont];
					numSorteio[i][cont] = numSorteio[i][j];
					numSorteio[i][j] = aux;
				}
			}
		}
	}

	cout << "\n**RESULTADO**\n";
	if(delay==true)  sleepcp(25);
  cout << qtdApostas << " apostas | " << qtdNumeros << " NÚMEROs por aposta\n";
	if(delay==true)  sleepcp(25);
  cout << "NÚMEROs entre " << menorNum << " e " << maiorNum << endl;
	for(i = 0; i < qtdApostas; i++){
    cout << "\n" << i+1 << "\t";
		if(delay==true) sleepcp(25);
		for(j = 0; j < qtdNumeros; j++){
			if(delay==true)  sleepcp(50);
      cout << numSorteio[i][j] << "	";
		}
	}
  return numSorteio;
}

int opcaoEscolhida(){

	int opcao;
	cout << "\n\n------------------------------------\n";
	cout << "\nO que você deseja fazer com as apostas?";
	cout << "\n1 - Sortear novamente.";
	cout << "\n2 - Gravar o resultado em um arquivo de texto já existente.";
	cout << "\n3 - Gravar o resultado em um novo arquivo de texto.";
	cout << "\n4 - Sair\nEscolha a opção desejada -> ";
	cin >> opcao;

	switch(opcao){
		case 1:
			if(delay==true)  sleepcp(1000);
			cout << "\nO PROGRAMA SERÁ INICIADO NOVAMENTE.";
			if(delay==true)  sleepcp(2000);
			if(cls==true)  system("cls");
			return main();
		case 2:
			break;
		case 3:
			break;
		case 4:
			if(cls==true)  system("cls");
			if(delay==true)  sleepcp(2000);
			cout << "\nO PROGRAMA SERÁ FINALIZADO.\n";
			if(delay==true)  sleepcp(3000);
			return 0;
	}
}

int isInteiroPositivo(){
	int valor = 0;
	cin >> valor;
	while(cin.fail() || valor <= 0) {
			cout << "Apenas número inteiro positivo -> ";
			cin.clear();
			cin.ignore(256,'\n');
			cin >> valor;
	}
	return valor;
}
