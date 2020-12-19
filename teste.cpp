#include <iostream>
#include <stdlib.h>

using namespace std;



int main(){
	int x = 5;
	int *p = &x;
	
	x = x + 4;
	cout << "X: " << x << endl;
	x = 5;
	x = *p + 4;
	cout << "X: " << x << endl;
	x = 5;
	*p = *p + 4;
	cout << "X: " << p << endl;
	
}
