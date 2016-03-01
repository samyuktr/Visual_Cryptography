#include "function.h"

int ctr=0;



void merge(FILE * fp1, FILE * fp2)
{
	//char data[3];
	int i=0, w=0, h=0, w1=0, h1=0, wb_bytes_perLine, j=0;
	char c1, c2;

//---------------------------------------------------------------------------------------------------------------------------------------------------
	//file1
	char * line1 = (char *) malloc(5); // array for reading P4\n
	line1[0] = '\0'; // initialising
	fgets(line1, 5, fp1); // read the first line. fgets stops when it sees \n
	if(strncmp(line1, "P4\n", 3)!=0) // returns 0 if it matches else return non zero;
	{
		fprintf(stderr, "Error! Not a PBM file. \n");
	}
	//file2
	fgets(line1, 5, fp2); // read the first line. fgets stops when it sees \n
	if(strncmp(line1, "P4\n", 3)!=0) // returns 0 if it matches else return non zero;
	{
		fprintf(stderr, "Error! Not a PBM file. \n");
	}

//-------------------------------------calculating h and w for both files.-----------------------------------------------------------------------------------------------------------------

	char * line2  = (char *) malloc(10);



	line2[0] = '\0';
	fgets(line2, 10, fp1); //file1

	w = (int)strtol(line2, &line2, 10);
	h = (int)strtol(line2, NULL, 10);

	line2[0] = '\0';
	fgets(line2, 10, fp2); //file2

	w1 = (int)strtol(line2, &line2, 10);
	h1 = (int)strtol(line2, NULL, 10);
//---------------------------------------------------------------------------------------------------------------------------
	if(w%8 == 0)
	{
		wb_bytes_perLine = (w/8); //number of bytes to consider at a time. 
	}
	else
	{
		wb_bytes_perLine = (w/8)+1; 
	}
	int no_total_in_bytes = h * wb_bytes_perLine;//  bytes to be read from *.1.pbm and *.2.pbm
	unsigned char * s1 = malloc(no_total_in_bytes);
	unsigned char * s2 = malloc(no_total_in_bytes);


	fread ( s1, sizeof ( unsigned char ), no_total_in_bytes, fp1 ); 
	fread ( s2, sizeof ( unsigned char ), no_total_in_bytes, fp2 );
	unsigned char * merged = malloc(wb_bytes_perLine);  

//--------------------writing in md5 format-------------------------------------------------------------------

	printf ( "P4\n" );
	printf ( "%d %d\n", w, h);



	for(i=0;i<h; i++)
	{
		for(j=0;j<wb_bytes_perLine; j++)
		{
			c1= *(s1++);
			c2 = *(s2++);
			merged[j] = c1 | c2;
		}
		fwrite ( merged, sizeof ( unsigned char ), wb_bytes_perLine, stdout );
	}
	
//------------------------freeing file pointers------------------------------------------------------------------------
fclose ( fp1 );
fclose ( fp2 );




}
