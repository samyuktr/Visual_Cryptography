#ifndef _FUNCTION_H_  //handling multiple inclusions
#define _FUNCTION_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <openssl/md5.h>
#include <math.h>

unsigned char * stream_call(int l, char * p, int flag);
void encryption(char * ip_filename, char * output_filename, char * ofn, char * pphrase, int n);
void to_bytechar(int no, char * line, int last_line_bits, int flag, int fileno, int w1, int h1, char * of);
void merge(FILE * a, FILE * b);
void decryption(FILE * fp);



#endif
