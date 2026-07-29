#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
int main(int argc, char** argv){
	std::ifstream read(argv[1]);
	std::ofstream write(argv[2]);
	std::string line;
	while (read >> line){
		//std::stringstream ss(line);
		//std::string greetStr;
		//while(ss >> greetStr){
		//	std::cout << greetStr << " ";
		//}
		
		write << line << " "; //<< std::endl;
	}
	return 0;
}
