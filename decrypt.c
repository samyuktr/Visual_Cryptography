#include "function.h"
/*
Samyukta Satish Rao
University of Southern California
*/

void decryption (FILE* fp)
{
	int w=0, h=0, i=0, j=0, position=0; 
	int bit_ptr = 0, bs = 0, shift=0;
	int wb_bytes_perLine_in, wb_bytes_perLine_out;
	unsigned char two_bits = '\0';

	

//----------------validation of pbm---------------------------------------------------------------------------------------------
	char * line1 = (char *) malloc(5); // array for reading P4\n
	line1[0] = '\0'; // initialising

	//file1
	fgets(line1, 5, fp); // read the first line. fgets stops when it sees \n
	if(strncmp(line1, "P4\n", 3)!=0) // returns 0 if it matches else return non zero;
	{
		fprintf(stderr, "Error! Not a PBM file. \n");
		exit(0);
	}

//--------------------------calculationg height and width-------------------------------------------------------------------------
	char * line2  = (char *) malloc(10);



	line2[0] = '\0';
	fgets(line2, 10, fp); //file1

	w = (int)strtol(line2, &line2, 10);
	h = (int)strtol(line2, NULL, 10);

//-----------------------------------------------------------------------------------------------------------------------------

	if(w%8 == 0)
	{
		wb_bytes_perLine_in = (w/8); //number of bytes to encode. if its a multiple of 8.
	}
	else
	{
		wb_bytes_perLine_in = (w/8)+1; // if not a multiple of 8. 
	}
	int total_bytes_to_read_from_file = h*wb_bytes_perLine_in; // no of bytes after height and width in the file. 


//-------------------------------------------------------------------------------------------------------------------------------

	unsigned char* total_bytes_read = malloc (total_bytes_to_read_from_file);
	fread (total_bytes_read, sizeof (unsigned char), total_bytes_to_read_from_file, fp);
	
	wb_bytes_perLine_out = ceil(wb_bytes_perLine_in/2.0); // for output file. 
	unsigned char *write_out = malloc (wb_bytes_perLine_out); //output file. 

	
	unsigned char *out = malloc (sizeof (unsigned char));
	memset (out, 0, sizeof (unsigned char));
	
	
	unsigned char *read_in_ptr = malloc (wb_bytes_perLine_in);
	unsigned char *read_in;


	int bytes_read_atAtime = wb_bytes_perLine_in*2;
// -------------------------------------writing to stdout in pbm format. --------------------------------------------------
	printf ("P4\n");
	printf ("%d %d\n", w/2, h/2);	

	bs = 7;
	for (j = 0; j < h/2; j++) 
	{
		memcpy (read_in_ptr, &total_bytes_read[j * bytes_read_atAtime], wb_bytes_perLine_in); // reading 2 rows 
		read_in = read_in_ptr;
		position = 0;
		for (i = 0; i < wb_bytes_perLine_in; i++) 
		{
			shift = 3;
			bit_ptr = 0;
			while(bit_ptr<4) // 4 bits in output file. this is run twice. 
			{
				
				two_bits = (read_in[0] >> ((shift--) * 2)) & 3;
				if (two_bits == 3) 
				{
					out[0] = out[0] | (1 << bs--);
				} 
				else if (two_bits == 1 || two_bits == 2) 
				{
					out[0] = out[0] | (0 << bs--);
				} 
				else if (two_bits == 0) 
				{
					out[0] = out[0] | (0 << bs--);
				}
				
				if (bs < 0) // when 8 bits are written, consider that byte. 
				{
					bs = 7;
					write_out[position++] = out[0]; 
					memset (out, 0, sizeof (unsigned char));
				}
				bit_ptr++;
			}

			if (i == wb_bytes_perLine_in - 1) 
			{
				bs = 7;
				write_out[position++] = out[0];
				memset (out, 0, sizeof (unsigned char));
			}

			read_in++;
		}
		fwrite (write_out, sizeof (unsigned char), wb_bytes_perLine_out, stdout);
		
	}

	//---------------------------------freeing all pointers and arrays------------------------------------------------------
	free (total_bytes_read);
	free (out);
	free (write_out);
	fclose (fp);
	free (read_in_ptr);
	
}
