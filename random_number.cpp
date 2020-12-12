#include <stdlib.h>
#include <ctime>
#include <locale.h>

int main(){
	setlocale (LC_ALL,"");
	
	//GERA NUMEROS
	int rNum, qtdApostas, qtdNumeros, aux, i, j, k, l, cont, diferente = 1;
	int menorNum, maiorNum;
	
	srand (time(NULL));
	
	printf("**GERADOR DE NÚMEROS QUE COM CERTEZA SERÃO SORTEADOS NA MEGA DA VIRADA**\r\n");
	
	printf("Digite a quantidade de apostas que serão feitas: ");
	scanf("%d", &qtdApostas);
	
	printf("Digite a quantidade de números que serão apostados: ");
	scanf("%d", &qtdNumeros);
	
	printf("\nDigite o menor número do sorteio: ");
	scanf("%d", &menorNum);
	
	printf("Digite o maior número do sorteio: ");
	scanf("%d", &maiorNum);
		
	int apostas[qtdApostas][qtdNumeros];
	
	//printf("\n\n**NUMEROS SORTEADOS**");
	for(i = 0; i < qtdApostas; i++){
		//printf("\n%d°\t", i+1);
		for(j = 0; j < qtdNumeros; j++){
			rNum = rand() % maiorNum + menorNum;
			
			//printf("%d	", rNum);
				
			apostas[i][j] = rNum;
						
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
	
	/*//GUARDANDO OS NÚMEROS EM OUTRA VARIÁVEL, CASO NECESSÁRIO (BACKUP)
	int apostas_bkp[i][j];
	printf("\n\n**REALIZANDO BACKUP...**\n");
	for(i = 0; i < qtdApostas; i++){
		for(j = 0; j < qtdNumeros; j++){
			apostas_bkp[i][j] = apostas[i][j];
		}
	}*/	
	
	//ORGANIZA NUMEROS
	//printf("\n**APLICANDO ASCENDENTE NOS NÚMEROS...**\n");
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
	
	printf("\n**RESULTADO**");
	for(i = 0; i < qtdApostas; i++){
		printf("\n%d°\t", i+1);
		for(j = 0; j < qtdNumeros; j++){
			printf("%d	",apostas[i][j]);
		}
	}
}
