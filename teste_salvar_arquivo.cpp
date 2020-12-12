#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

using namespace std;
void list_dir(const char *path) {
	struct dirent *entry;
	DIR *dir = opendir(path);
	
	if (dir == NULL) {
		return;
	}
	
	while ((entry = readdir(dir)) != NULL) {
		string tipo = entry->d_name;
		int procura = tipo.find(".");
		string extensao = tipo.substr(procura + 1);
		//cout << extensao << endl;
		if(extensao == "txt"){
			cout << entry->d_name << endl;
		}
	}
	closedir(dir);
}
int main() {
	list_dir("./");
}
