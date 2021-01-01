#include <stdlib.h>
#include <ctime>
#include <locale.h>
#include <iostream>
#include <time.h>

void sleepcp(int milliseconds);

void sleepcp(int milliseconds){
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end){}
}

int main(){
	setlocale (LC_ALL,"");

	//GERA NUMEROS
	int qtdApostas, qtdNumeros, menorNum, maiorNum;
	printf("**GERADOR DE NÚMEROS QUE COM CERTEZA SERÃO SORTEADOS NA MEGA DA VIRADA**\n");
	printf("Qual será a quantidade de apostas que serão feitas? ");
	scanf("%d", &qtdApostas);

	printf("Qual será a quantidade de números que serão apostados: ");
	scanf("%d", &qtdNumeros);

	printf("\nQual o menor número possível? ");
	scanf("%d", &menorNum);

	printf("Qual o maior número do sorteio? ");
	scanf("%d", &maiorNum);

	//sleepcp(2000);

	printf("\nSORTEANDO NÚMEROS...");
	//sleepcp(3000);
	system("cls");

	srand (time(NULL));
	printf("\n**NUMEROS SORTEADOS**");
	int apostas[qtdApostas][qtdNumeros], rNum, aux, i, j, k, diferente = 1;

	for(i = 0; i < qtdApostas; i++){
		printf("\n%d°\t", i+1);
		//sleepcp(25);
		for(j = 0; j < qtdNumeros; j++){
			//sleepcp(50);
			rNum = rand() % maiorNum + menorNum;

			printf("%d	", rNum);

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

	//GUARDANDO OS NÚMEROS EM OUTRA VARIÁVEL, CASO NECESSÁRIO (BACKUP)
	int apostas_bkp[i][j];
	//printf("\n\n**REALIZANDO BACKUP...**\n");
	for(i = 0; i < qtdApostas; i++){
		for(j = 0; j < qtdNumeros; j++){
			apostas_bkp[i][j] = apostas[i][j];
		}
	}

	//ORGANIZA NUMEROS
	//sleepcp(2000);
	printf("\n\n**APLICANDO ORDEM CRESCENTE NOS NÚMEROS SORTEADOS...**\n");
	//sleepcp(3000);
	system("cls");
	int cont;

	for(i = 0; i < qtdApostas; i++){
		for(cont = 0; cont < qtdNumeros; cont++){
			for(j = cont; j < qtdNumeros; j++){
				if(apostas[i][cont] > apostas[i][j]){
					aux = apostas[i][cont];
					apostas[i][cont] = apostas[i][j];
					apostas[i][j] = aux;
				}
			}
		}
	}

	printf("\n**RESULTADO**\n");
	//sleepcp(25);
	printf("%d apostas | %d NÚMEROs por aposta\n",qtdApostas, qtdNumeros);
	//sleepcp(25);
	printf("NÚMEROs entre %d e %d\n", menorNum, maiorNum);
	for(i = 0; i < qtdApostas; i++){
		printf("\n%d°\t", i+1);
		sleepcp(25);
		for(j = 0; j < qtdNumeros; j++){
			sleepcp(50);
			printf("%d	",apostas[i][j]);
		}
	}

	int opcao;
	printf("\n\n------------------------------------\n");
	printf("\nO que você deseja fazer com as apostas?");
	printf("\n1 - Sortear novamente.");
	printf("\n2 - Gravar o resultado em um arquivo de texto já existente.");
	printf("\n3 - Gravar o resultado em um novo arquivo de texto.");
	printf("\n4 - Sair\nEscolha a opção desejada:");
	scanf("%d", &opcao);

	switch(opcao){
		case 1:
			//sleepcp(1000);
			printf("\nO PROGRAMA SERÁ INICIADO NOVAMENTE.");
			//sleepcp(2000);
			system("cls");
			return main();
		case 2:
			break;
		case 3:
			break;
		case 4:
			system("cls");
			//sleepcp(2000);
			printf("O PROGRAMA SERÁ FINALIZADO.");
			//sleepcp(3000);
			return 0;
	}

	return 0;
}
