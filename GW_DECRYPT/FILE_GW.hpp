#include <openssl\aes.h>
#include <sstream>
#include <stdlib.h>
namespace FILE_GW {
	unsigned char cKey1[]	= "\x58\x00\x06\x19\x28\x00\xC5\xF0\xFB\xFB\x04\xE0\x6A\x68\x20\x88";
	unsigned char cKey2[]	= "\x11\x66\xD4\x0C\xCD\xC9\xBD\x6A\xE2\xF3\x8E\x8A\x0D\x4F\xE1\x28";
	unsigned char iVec[]	= "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	bool DEC1(const char *file_in, const char *file_out) {
		FILE *fIn, *fOut;
		if((fIn = fopen(file_in, "rb+")) == NULL) return false;
		fseek(fIn, 0, SEEK_END);
		int fLen = ftell(fIn);
		char *fEnc = (char*)malloc(fLen), *fDec = (char*)malloc(fLen);
		rewind(fIn);
		fread(fEnc, fLen, 1, fIn);
		fclose(fIn);
		AES_KEY key;
		AES_set_decrypt_key(cKey1, 128, &key);
		AES_cbc_encrypt((unsigned char*)fEnc, (unsigned char*)fDec, fLen, &key, iVec, AES_DECRYPT);
		if((fOut = fopen(file_out, "wb+")) == NULL) return false;
		fwrite(fDec, fLen, 1, fOut);
		fflush(fOut);
		fclose(fOut);
		delete [] fEnc;
		delete [] fDec;
		return true;
	}
	bool DEC2(const char *file_in, const char *file_out) {
		FILE *fIn, *fOut;
		if((fIn = fopen(file_in, "rb+")) == NULL) return false;
		fseek(fIn, 0, SEEK_END);
		int fLen = ftell(fIn);
		char *fEnc = (char*)malloc(fLen), *fDec = (char*)malloc(fLen);
		rewind(fIn);
		fread(fEnc, fLen, 1, fIn);
		fclose(fIn);
		AES_KEY key;
		AES_set_decrypt_key(cKey2, 128, &key);
		AES_cbc_encrypt((unsigned char*)fEnc, (unsigned char*)fDec, fLen, &key, iVec, AES_DECRYPT);
		if((fOut = fopen(file_out, "wb+")) == NULL) return false;
		fwrite(fDec, fLen, 1, fOut);
		fflush(fOut);
		fclose(fOut);
		delete [] fEnc;
		delete [] fDec;
		return true;
	}
}