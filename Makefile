all: main.o stream.o encrypt.o merge.o decrypt.o
	gcc -g -Wall main.o stream.o merge.o decrypt.o encrypt.o -o hw2 -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm

main.o: main.c function.h
	gcc -c -g -Wall main.c -I/home/scf-22/csci551b/openssl/include

encrypt.o: encrypt.c function.h
	gcc -c -g -Wall encrypt.c -I/home/scf-22/csci551b/openssl/include

stream.o: stream.c function.h
	gcc -c -g -Wall stream.c -I/home/scf-22/csci551b/openssl/include

merge.o: merge.c function.h
	gcc -c -g -Wall merge.c -I/home/scf-22/csci551b/openssl/include

decrypt.o: decrypt.c function.h
	gcc -c -g -Wall decrypt.c -I/home/scf-22/csci551b/openssl/include

clean:
	rm *.o
	rm hw2
