#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "FILE_GW.hpp"

void help(char *app_name) 
{
	std::cout
		<< "Usage: " << app_name << " [version] [file_in] [file_out]" << std::endl
		<< "VERSION					GW Version" << std::endl
		<< "1					1.0, 1.1, 1.2" << std::endl
		<< "2					2.0b1, 2.0b2" << std::endl;
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) 
{
	if(argc != 4)
	{
		help(argv[0]);
	}
		
	if(strcmp(argv[1], "1") == 0) 
	{
		if(!FILE_GW::DEC1(argv[2], argv[3]))
		{ 
			perror("Couldn't decrypt");
		}
	}		
	else if(strcmp(argv[1], "2") == 0) 
	{
		if(!FILE_GW::DEC2(argv[2], argv[3])) 
		{
			perror("Couldn't decrypt");
		}
	}
	else 
	{
		perror("Version don't match");
		help(argv[0]);
	}
	std::cout << "File decrypted correctly!" << std::endl;
	return 0;
}
