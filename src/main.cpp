#include <iostream>
#include "file_reader.hpp"
int main(){
	std::cout << "Hello, World!" << std::endl;
	std::string file("adaptec1");
	std::cout << "Reading file: " << file << std::endl;
	auto fr = new FileReader(file);
	fr->print();
	std::cout << "File read successfully!" << std::endl;
	return 0;
}
