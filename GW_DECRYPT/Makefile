all: GWDecrypt

GWDecrypt: main.o
		g++ main.o -o GWDecrypt -lcrypto

main.o: main.cpp FILE_GW.hpp
		g++ -c main.cpp

clean:
		rm -rf main.o GWDecrypt
