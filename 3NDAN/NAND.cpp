#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>

#include "struct.h"
#include "NAND.h"
#include "CRC32.h"

bool pNAND::INFO(char *filename) {
	FILE *file;
	std::cout << " Reading: ";
	file = fopen((const char*)filename, "rb+");
	if(file == NULL) {
		std::cout << "FAIL!";
		return false;
	}
	NAND *nand = (NAND*)malloc(sizeof(NAND));
	fread(nand, sizeof(NAND), 1, file);
	fseek(file, 0, SEEK_END);
	std::cout << "OK!" << std::endl
		<< " NAND struct size: " << sizeof(NAND) << std::endl
		<< " NAND size: " << ftell(file) << std::endl
		<< " Partitions:" << std::endl << std::endl
		<< "  NCSD [" << sizeof(nand->Header) << "] " << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->Header, sizeof(nand->Header))<< std:: dec << std::endl
		<< "   Magic sign: " << nand->Header.magic_number << std::endl
		<< "   FS type: " << nand->Header.FS_type << std::endl
		<< "   Crypto type: " << nand->Header.crypt_type << std::endl
		<< "   Partition table: " << std::endl;
	for(auto i = 0; i <8; i++)
		std::cout << "    Offset 0x" << std::hex << nand->Header.table[i].offset << " Size 0x" << nand->Header.table[i].size << std::dec << std::endl;
	std::cout << "   Partition id table: " << std::endl;
	for(auto i = 0; i < 8; i++)
		std::cout << "    ID 0x" << std::hex << nand->Header.id_table[i] << std::dec << std::endl;
	std::cout << std::endl
		<< "  TWLN [" << sizeof(nand->TWLN_partition) << "]" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->TWLN_partition, sizeof(nand->TWLN_partition)) << std::dec << std::endl;
	std::cout << std::endl
		<< "  TWLP [" << sizeof(nand->TWLP_partition) << "]" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->TWLP_partition, sizeof(nand->TWLP_partition)) << std::dec << std::endl;
	std::cout << std::endl
		<< "  AGB FIRM [" << sizeof(nand->AGB_FIRM) << "]" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->AGB_FIRM, sizeof(nand->AGB_FIRM)) << std::dec << std::endl;
	std::cout << std::endl
		<< "  FIRM0 [" << sizeof(nand->FIRM0) << "]" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->FIRM0, sizeof(nand->FIRM0)) << std::dec << std::endl;
	std::cout << std::endl
		<< "  FIRM1 [" << sizeof(nand->FIRM1) << "]" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->FIRM1, sizeof(nand->FIRM1)) << std::dec << std::endl;
	std::cout << std::endl
		<< "  CTR NAND [" << sizeof(nand->CTR_NAND) << "]" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->CTR_NAND, sizeof(nand->CTR_NAND)) << std::dec << std::endl; 
	std::cout << std::endl
		<< "  CTR NAND FileSystem[" << sizeof(nand->CTR_NAND_FAT16) << "]" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->CTR_NAND_FAT16, sizeof(nand->CTR_NAND_FAT16)) << std::dec << std::endl; 
	fclose(file);
	delete [] nand;
	return true;
}
bool pNAND::EXTRACT(char *filename){
	FILE *file, *fOut;
	float start = clock();
	std::cout << " Reading: ";
	file = fopen((const char*)filename, "rb+");
	if(file == NULL) {
		std::cout << "FAIL!";
		return false;
	}
	NAND *nand = (NAND*)malloc(sizeof(NAND));
	fread(nand, sizeof(NAND), 1, file);
	fseek(file, 0, SEEK_END);
	std::cout << "OK!" << std::endl
		<< " NAND struct size: " << sizeof(NAND) << std::endl
		<< " NAND size: " << ftell(file) << std::endl << std::endl
		<< " Extracting partitions: " << std::endl << std::endl
		<< "  NCSD:	";
	if((fOut = fopen("NCSD.bin", "wb+")) == NULL) { std::cout << "			FAIL"; return false; }
	fwrite(&nand->Header, sizeof(nand->Header), 1, fOut);
	fflush(fOut);
	fclose(fOut);
	std::cout << "			OK!" << std::endl
		<< "  TWLN: ";
	if((fOut = fopen("TWLN.bin", "wb+")) == NULL) { std::cout << "			FAIL"; return false; }
	fwrite(&nand->TWLN_partition, sizeof(nand->TWLN_partition), 1, fOut);
	fflush(fOut);
	fclose(fOut);
	std::cout << "			OK!" << std::endl
		<< "  TWLP: ";
	if((fOut = fopen("TWLP.bin", "wb+")) == NULL) { std::cout << "			FAIL"; return false; }
	fwrite(&nand->TWLP_partition, sizeof(nand->TWLP_partition), 1, fOut);
	fflush(fOut);
	fclose(fOut);
	std::cout << "			OK!" << std::endl
		<< "  AGB FIRM:	";
	if((fOut = fopen("AGB_FIRM.bin", "wb+")) == NULL) { std::cout << "		FAIL"; return false; }
	fwrite(&nand->AGB_FIRM, sizeof(nand->AGB_FIRM), 1, fOut);
	fflush(fOut);
	fclose(fOut);
	std::cout << "		OK!" << std::endl
		<< "  FIRM0: ";
	if((fOut = fopen("FIRM0.bin", "wb+")) == NULL) { std::cout << "			FAIL"; return false; }
	fwrite(&nand->FIRM0, sizeof(nand->FIRM0), 1, fOut);
	fflush(fOut);
	fclose(fOut);
	std::cout << "			OK!" << std::endl
		<< "  FIRM1: ";
	if((fOut = fopen("FIRM1.bin", "wb+")) == NULL) { std::cout << "			FAIL"; return false; }
	fwrite(&nand->FIRM1, sizeof(nand->FIRM1), 1, fOut);
	fflush(fOut);
	fclose(fOut);
	std::cout << "			OK!" << std::endl
		<< "  CTR NAND: ";
	if((fOut = fopen("CTR_NAND.bin", "wb+")) == NULL) { std::cout << "			FAIL"; return false; }
	fwrite(&nand->CTR_NAND, sizeof(nand->CTR_NAND), 1, fOut);
	fflush(fOut);
	fclose(fOut);
	std::cout << "			OK!" << std::endl
		<< "  CTR NAND FileSystem: ";
	if((fOut = fopen("CTR_NAND_FAT16.bin", "wb+")) == NULL) { std::cout << "		FAIL"; return false; }
	fwrite(&nand->CTR_NAND_FAT16, sizeof(nand->CTR_NAND_FAT16), 1, fOut);
	fflush(fOut);
	fclose(fOut);
	std::cout << "		OK!" << std::endl << std::endl
		<< " Extracted correctly in "<<  ((clock() - start) / (double) CLOCKS_PER_SEC)<<"s" << std::endl;
	delete [] nand;
	return true;
}
bool pNAND::REPACK(char *filename){
	FILE *file, *fOut;
	if((fOut = fopen(filename, "wb+")) == NULL) return false;
	NAND *nand = (NAND*)malloc(sizeof(NAND));
	std::cout << " Repacking NAND" << std::endl << std::endl
		<< " Reading partitions: " << std::endl
		<< "  NCSD: ";
	if((file = fopen("NCSD.bin", "rb+")) == NULL) {std::cout << "FAIL"; return false;}
	fread(&nand->Header, sizeof(NCSD), 1, file);
	std::cout
		<< "OK!" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->Header, ftell(file)) << std::dec << std::endl
		<< "   Size: " << ftell(file)<< std::endl;
	fclose(file);
	std::cout << "  TWLN: ";
	if((file = fopen("TWLN.bin", "rb+")) == NULL) {std::cout << "FAIL"; return false;}
	fread(&nand->TWLN_partition, 0x8FB5200, 1, file);
	std::cout
		<< "OK!" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->TWLN_partition, ftell(file)) << std::dec << std::endl
		<< "   Size: " << ftell(file)<< std::endl;
	fclose(file);
	std::cout << "  TWLP: ";
	if((file = fopen("TWLP.bin", "rb+")) == NULL) {std::cout << "FAIL"; return false;}
	fread(&nand->TWLP_partition, 0x20B660, 1, file);
	std::cout
		<< "OK!" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->TWLP_partition, ftell(file)) << std::dec << std::endl
		<< "   Size: " << ftell(file)<< std::endl;
	fclose(file);
	std::cout << "  AGB FIRM: ";
	if((file = fopen("AGB_FIRM.bin", "rb+")) == NULL) {std::cout << "FAIL"; return false;}
	fread(&nand->AGB_FIRM, 0x30000, 1, file);
	std::cout
		<< "OK!" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->AGB_FIRM, ftell(file)) << std::dec << std::endl
		<< "   Size: " << ftell(file) << std::endl;
	fclose(file);
	std::cout << "  FIRM0: ";
	if((file = fopen("FIRM0.bin", "rb+")) == NULL) {std::cout << "FAIL"; return false;}
	fread(&nand->FIRM0, 0x400000, 1, file);
	std::cout
		<< "OK!" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->FIRM0, ftell(file)) << std::dec << std::endl
		<< "   Size: " << ftell(file) << std::endl;
	fclose(file);
	std::cout << "  FIRM1: ";
	if((file = fopen("FIRM1.bin", "rb+")) == NULL) {std::cout << "FAIL"; return false;}
	fread(&nand->FIRM1, 0x400000, 1, file);
	std::cout
		<< "OK!" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->FIRM1, ftell(file)) << std::dec << std::endl
		<< "   Size: " << ftell(file) << std::endl;
	fclose(file);
	std::cout << "  CTR NAND: ";
	if((file = fopen("CTR_NAND.bin", "rb+")) == NULL) {std::cout << "FAIL"; return false;}
	fread(&nand->CTR_NAND, 0x1ECA00, 1, file);
	std::cout
		<< "OK!" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->FIRM1, ftell(file)) << std::dec << std::endl
		<< "   Size: " << ftell(file) << std::endl;
	fclose(file);
	std::cout << "  CTR NAND FileSystem: ";
	if((file = fopen("CTR_NAND_FAT16.bin", "rb+")) == NULL) {std::cout << "FAIL"; return false;}
	fread(&nand->CTR_NAND_FAT16, 0x2F3E3600, 1, file);
	std::cout
		<< "OK!" << std::endl
		<< "   CheckSum: 0x" << std::hex << CRC_32(&nand->FIRM1, ftell(file)) << std::dec << std::endl
		<< "   Size: " << ftell(file) << std::endl;
	fclose(file);

	memset(&nand->Blank_1, 0xFF, 0x12C00);
	memset(&nand->Blank_2, 0xFF, 0x49A00);
	memset(&nand->Blank_3, 0xFF, 0x1EE2FA0);
	std::cout << std::endl <<  " Writting to " << filename << ": ";
	fwrite(&nand->Header, 0x200, 1, fOut);
	fwrite(&nand->Blank_1, sizeof(nand->Blank_1), 1, fOut);
	fwrite(&nand->TWLN_partition, sizeof(nand->TWLN_partition), 1, fOut);
	fwrite(&nand->Blank_2, sizeof(nand->Blank_2), 1, fOut);
	fwrite(&nand->TWLP_partition, sizeof(nand->TWLP_partition), 1, fOut);
	fwrite(&nand->Blank_3, sizeof(nand->Blank_3), 1, fOut);
	fwrite(&nand->AGB_FIRM, sizeof(nand->AGB_FIRM), 1, fOut);
	fwrite(&nand->FIRM0, sizeof(nand->FIRM0), 1, fOut);
	fwrite(&nand->FIRM1, sizeof(nand->FIRM1), 1, fOut);
	fwrite(&nand->CTR_NAND, sizeof(nand->CTR_NAND), 1, fOut);
	fwrite(&nand->CTR_NAND_FAT16, sizeof(nand->CTR_NAND_FAT16), 1, fOut);
	fflush(fOut);
	fclose(fOut);
	std::cout << "OK!" << std::endl;
	delete [] nand;
	return true;
};