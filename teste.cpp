// string::substr
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

std::string * retorna(){
	std::string palavras[5] = {"oie", "eaei mano", "beleza?", "bao?", "teste"};
	std::string palavras_op[5];
	
	std::stringstream str_bkp;
	std::string out_string;
	static string concat[5];
	
	for(int i = 0; i < 5; i++){
		//std::cout << i + 1 << " - " << palavras[i] << "\n";
		std::stringstream str;
		str << i+1;
		out_string = str.str();
		//std::cout << "teste: " << out_string << "\t";
		concat[i] = out_string + " - " + palavras[i];
		cout << concat[i] << endl;
		
	}
	return concat;
}

int main (){
	std::string* ret_palavras;
	
	ret_palavras = retorna();
	string valor;
	cout << "\nDigite: ";
	cin >> valor;
	std::string escolhido;
	
	for(int i = 0; i < 5; i++){
		string fPos = ret_palavras[i].substr(0,1);
		if(valor == fPos){
			escolhido = ret_palavras[i];
			break;
		}
	}
	cout << "resultado: " << escolhido;
}
