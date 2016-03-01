#include "function.h"



 char *byte_to_binary(char y) // converts byte to  bit stream 
{
    int x = (int)y;
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}


void to_bytechar(int no, char * line, int last_line_bits, int flag, int fileno, int w1, int h1, char * output_filename) //converts bit stream to character. 
{
	// line=34 characters containing 34bits. no=5 used to represent 34 bits as 5 bytes. Left overs appended with 0. 
	// last line bits --> no. of bits in the last byte so that the rest can be appended with 0. 
	int k=0, i=0;
	

		
	if(flag==1)
	{

		FILE * fp = fopen(output_filename, "w");
		fputs("P4\n", fp);
		char * buf = (char *)calloc(10, sizeof(char));
		sprintf(buf, "%d %d\n", w1, h1);
		fputs(buf, fp);
		for(i=0; i<10; i++)
		{
			buf[i] = '\0';
		}
		free(buf);

	}
	else if(flag==0)
	{
				int num=0; // holds decimal value. 
				char * binptr = (char *)malloc(8*sizeof(char)); // to read 8 charaters from line.
				char * bin = binptr;
				FILE * fp = fopen(output_filename, "a");
				if(bin==NULL)
				{
					printf("Malloc failed\n");
				}

				for(i=0;i<8;i++)
					bin[i] = '\0'; // initialising bin to null.
				
				bin[8] = '\0';

				char final_line[no]; 
				// initialising final_line to null.
				final_line[0] = '\0';
				
				for(i=0;i<no;i++)
					final_line[i] = '\0';
				final_line[no] = '\0';




				while(k<(no-1) ) // first few lines where 8 full bits are read. 
				{
					bin[8] = '\0'; // last position of bin set to null. If this is not done, second call to the function makes the size of bin 24 and 24 random bits are in bin.
					strncpy(bin, line, 8);
					line+=8;

					//Coverting char array to decimal.
					do
					{
						int b = *bin=='1'?1:0;
						num = (num<<1)|b;
						bin++;
					}while(*bin);
					fputc((char)num, fp);

					final_line[k] = (char)num; // appending char array with the character. 


					k++;
					for(i=0;i<8;i++) // resetting bin to null. 
						bin[i] = '\0';
					num=0;
				}
				if(k==(no-1)) // last line of every line that needs 0's appended. 
				{
					if(last_line_bits)
					{
						strncpy(bin, line, 2*last_line_bits);
						
					}
					for(i=last_line_bits*2; i<8; i++)
					{
						bin[i] = '0';
					}
					
					do
					{
						int b = *bin=='1'?1:0;
						num = (num<<1)|b;
						bin++;
					}while(*bin);
					fputc((char)num, fp);

					final_line[k] = (char)num;

					for(i=0;i<8;i++)
						bin[i] = '\0';
					num=0;
					
					

					
				}
	
				free(binptr);

			
	}
	

}




void encryption(char * ip_filename, char * output_filename1, char * output_filename2, char * pphrase, int n)
{
	FILE * fp;
	int w, h;
	char data[3];
	int no_bytes_toread;
	if(n==5)
	{
		fp = fopen(ip_filename, "rb");
	}
	else if(n==4)
	{
		fp = stdin;
	}
	
	if(fp!=NULL)
	{
		data[0] = fgetc(fp);
		data[1] = fgetc(fp);
		data[2] = fgetc(fp);

		
		if(strncmp(data, "P4\n", 3)!=0)	
		{
			fprintf(stderr, "Not a PBM file!");
		}

//------------------------------Calculating height and width-----------------------------------------------------

		
		char buffer[10] = "";
		char ch;
		int c_buf = 0;
		//buff = fgets(fp);
		while(1)
	{
		ch = fgetc(fp);
		if(ch==' ')
		{
			break;
		}
		else
		{
			buffer[c_buf] = ch;
			c_buf++;
		}


	}
	w = atoi(buffer);

	c_buf = 0;
	ch = '\0';



	while(1)
	{
		ch = fgetc(fp);
		if(ch=='\n')
		{
			break;
		}
		else
		{
			buffer[c_buf] = ch;
			c_buf++;
		}


	}
	h = atoi(buffer);


		
		h = atoi(buffer);


//-------------------------------------Number of bytes to read----------------------------------------------------
		int bytes_per_line;
		if(w%8==0)
		{
			no_bytes_toread = (w*h)/8;
		}
		else
		{
			no_bytes_toread = ceil(w*h/8.0);
		}

		if((w%8)==0)
		{
			bytes_per_line = w/8;
		}
		else
		{
			bytes_per_line = (w/8)+1;
		}
		 
		int last_line_bits = w%8;

//-----------------------------------Empty arrays------------------------------------------------------
		//eg: creating small image from small.pbm --> 17*17 bits. 
		int i, j;

		char* small[h];

		for(i=0;i<h;i++)
		{
			small[i] = (char *)calloc(w, sizeof(char));
			small[i][w] = '\0';
		}
		for(i=0;i<h;i++)
		{
			small[i][0] = '\0';
		}

		//creating output1 and output2 grids. 
		int h1 = h*2;
		char *small1[h1];
		for(i=0;i<h1;i++)
		{
			small1[i] = (char *)malloc(w*2 * sizeof(char));
			//small1[i][0] = '\0';
		}
		for(i=0;i<h1;i++)
		{
			small1[i][0] = '\0';
		}
		

		char *small2[h1];
		for(i=0;i<h1;i++)
		{
			small2[i] = (char *)malloc(w*2 *sizeof(char));
			//small2[i][h*2] = '\0';
		}
		for(i=0;i<h1;i++)
		{
			small2[i][0] = '\0';
		}
	
//---------------------------------------------------------------------------------------------------------
		int p=0; int q=0;
	
		char data_from_file;
		for(q=0;q<h;q++)
		{	

			for(p=0;p<bytes_per_line;p++)
			{

				data_from_file = fgetc(fp);
	
				char * bin = byte_to_binary(data_from_file);

		
					if(p==bytes_per_line-1) // and its the last byte being read
					{
						//int last = p*8; // So at pos 16 it should write the last few bits. Or at 24 if its 25x25
						if(last_line_bits) // if there's an extra byte where we need to ignore certain bits
						{
							strncat(small[q], bin, last_line_bits); // copy only first last_line_bits to buffer. 
							// h-1 = last row. p=last byte read. 
						}
					}
					

					else
					{

						strncat(small[q], bin, 8);
					}
	
				
			}
		}

//---------------------------------small.pbm converted to a 2D Array!--------------------
	/*	for(i=0;i<h;i++)
		{
			printf("%s\n", small[i]);
		} */
//-----------------generate appropriate number of md5--------------------------

		
		unsigned char * key = (unsigned char *) stream_call(no_bytes_toread, pphrase, 1);
	
//---------------------------Coverting md5 to binary----------------------------

		char key_str[no_bytes_toread*8];
 		key_str[0] = '\0';
		for(i=0;i<no_bytes_toread;i++)
		{
			char * temp = byte_to_binary(key[i]);
			strncat(key_str, temp, 8);
		}

		int o=0, k=0, l=0, m=0;
		j=0;

//---------------------------Creating small1 and small2---------------------------------------------------------		
	for(i=0, k=0, l=1; i<h && k<(2*h) && l< (2*h); i++, k=k+2, l=l+2)
	{
		for(j=0, m=0; j<w && m<(2*w); j=j+1, m=m+2)
		{
			if(small[i][j]=='1')
			{
				if(key_str[o]=='0')
				{	

					small1[k][m] = '1';
					small1[k][m+1] = '0';
					small1[l][m] = '0';
					small1[l][m+1] = '1';

					small2[k][m] = '0';
					small2[k][m+1] = '1';
					small2[l][m] = '1';
					small2[l][m+1] = '0';
					o++;

				}
				else if(key_str[o]=='1')
				{

					small1[k][m] = '0';
					small1[k][m+1] = '1';
					small1[l][m] = '1';
					small1[l][m+1] = '0';

					small2[k][m] = '1';
					small2[k][m+1] = '0';
					small2[l][m] = '0';
					small2[l][m+1] = '1';
					o++;


				}
			}

			else if(small[i][j]=='0')
			{
				if(key_str[o]=='0')
				{

					small1[k][m] = '1';
					small1[k][m+1] = '0';
					small1[l][m] = '0';
					small1[l][m+1] = '1';

					small2[k][m] = 1;
					small2[k][m+1] = '0';
					small2[l][m] = '0';
					small2[l][m+1] = 1;
					o++;
				}
				else if(key_str[o]=='1')
				{

					small1[k][m] = '0';
					small1[k][m+1] = '1';
					small1[l][m] = '1';
					small1[l][m+1] = '0';

					small2[k][m] = '0';
					small2[k][m+1] = '1';
					small2[l][m] = '1';
					small2[l][m+1] = '0';
					o++;


				}
			}	
		}
	}
	


//--------------------------converting small1 and small2 to bytes-------------------------------------------------

		int bytes_to_write = (bytes_per_line * 2) - 1;
		char * trial = malloc(strlen(output_filename1)+6);
		strcpy(trial,output_filename1);

		strcat(output_filename1, ".1.pbm");
		strcat(trial, ".2.pbm");

		to_bytechar(bytes_to_write, small1[i],last_line_bits, 1, 1, w*2, h*2, output_filename1);  // flag = 1
		for(i=0;i<2*h;i++)
		{
			to_bytechar(bytes_to_write, small1[i],last_line_bits, 0, 1, w*2, h*2, output_filename1); // flag = 0 ---> char write. 

		} 
	

		to_bytechar(bytes_to_write, small2[i],last_line_bits, 1, 2, w*2, h*2, trial);  // flag = 1
		for(i=0;i<2*h;i++)
		{
			to_bytechar(bytes_to_write, small2[i],last_line_bits, 0, 2, w*2, h*2, trial); // flag = 0 ---> char write. 

		} 
	

		fclose(fp);

		

		}	
		else
		{
			fprintf(stderr, "Input file error! \n");
		}
	
}
