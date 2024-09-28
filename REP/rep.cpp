#include<iostream>
#include<fstream>
#include<string>

using namespace std;


int main(int argc,  char** argv){
	ifstream file (argv[1]);
	if(!file.is_open()) return cout << "Not such a file!" << endl, 0;
	
	string line;
	while( getline(file,line) ) cout << line << endl;
   
    file.close();
}
