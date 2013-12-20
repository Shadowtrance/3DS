#include <iostream>
#include "NAND.h"
void ERROR(char *error) {
	std::cout << std::endl<< " [ERROR]: " << error << std::endl;
}
void help(char *app_name) {
	std::cout 
		<< std::endl
		<< "Usage " << app_name << " [options] <nand filepath>" << std::endl
		<< "OPTIONS				Explanation" << std::endl
		<< " -d				Display NAND info" << std::endl
		<< " -x				Extract all NAND partitions" << std::endl
		<< " -r				Repack NAND partitions" << std::endl
		<< " -h				Print this help" << std::endl;
	exit(EXIT_FAILURE);
}
void main(int argc, char *argv[]) {
	system("title 3NDAN - 3DS NAND analyze - ernilos");
	if(argc != 3){
		ERROR("Incorrect arguments");
		help(argv[0]);
	}
	if(strcmp(argv[1], "-d") == 0) {if(!pNAND::INFO(argv[2])) ERROR("Can't display NAND info");}
	else if(strcmp(argv[1],"-x") == 0) {if(!pNAND::EXTRACT(argv[2])) ERROR("Can't extract NAND partitions");}
	else if(strcmp(argv[1],"-r") == 0) {if(!pNAND::REPACK(argv[2]))  ERROR("Can't repack NAND partitions");}
	else if(strcmp(argv[1],"-h") == 0) {help(argv[0]);}
	else {
		ERROR("Incorrect arguments");
		help(argv[0]);
	}
}