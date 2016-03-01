#include "function.h"


/*
Samyukta Satish Rao
University of Southern California
*/

int main(int argc, char * argv[])
{
	char p = 'p';
	char l = 'l';
	char eq = '=';
	char d = '-';

	char * input_str;
	char * input_len;
	int len;
	char * s_null;
	s_null = "";
	char * output_filename1;
	char * output_filename2;
	if(argc==1)
		{
			fprintf(stderr, "Malformed command. \n");
		}
		else
		{

	if(strcmp(argv[1], "stream")==0)
	{
		
		if(argc!=4)
		{
			fprintf(stderr, "Enter enough information.\n");
			exit(0);
		}
		else
		{

			if(argv[2][1]==p)
			{
				input_str = strchr(argv[2], eq);
				input_str++;
			}
			else if(argv[2][1]==l)
			{
				input_len = strchr(argv[2], eq);
				input_len++;
				len = atoi(input_len);
				//md5_digest_len = len;
			}
			else
			{
				fprintf(stderr, "Error: Enter valid arguements.\n");
				exit(0);
			}

			if((argv[2][0]!=d)||(argv[3][0]!=d))
			{
				fprintf(stderr, "Error: Enter valid arguements.\n");
				exit(0);	
			}

			if(argv[3][1]==p)
			{
				input_str = strchr(argv[3], eq);
				input_str++;
			}
			else if(argv[3][1]==l)
			{
				input_len = strchr(argv[3], eq);
				input_len++;
				len = atoi(input_len);
			}
			else
			{
				fprintf(stderr, "Error: Enter valid arguements.\n");
				exit(0);
			}



			if(strcmp(argv[1], "stream")==0)
			{
				stream_call(len, input_str, 0);

			}
			else
			{
				fprintf(stderr, "Error: Enter valid arguements.\n");
				exit(0);
			}
			
		}
	} 

	else if(strcmp(argv[1], "encrypt")==0)
	{
		if((argc<2)||(argc<3)||(argc<4))
		{
			fprintf(stderr, "Error: Enter valid arguements.\n");
		}
		if(argc==4 || argc==5)
		{

			if((argv[2][0]!=d)||(argv[3][0]!=d))
			{
				fprintf(stderr, "Error: Enter valid arguements.\n");
				exit(0);	
			}
			if(argv[2][1]==p)
			{
				input_str = strchr(argv[2], eq);
				input_str++;
				
			}
			else if(strstr(argv[2], "out" )!=NULL)
			{
				
				output_filename1 = strchr(argv[3], eq);
				output_filename1++;
				output_filename2 = strchr(argv[3], eq);
				output_filename2++;
				printf("Found output filename=%s\n", output_filename1);
				
			}
			else
			{
				fprintf(stderr, "Error: Enter valid arguements.\n");
				exit(0);
			}
			if(argv[3][1]==p)
			{
				input_str = strchr(argv[3], eq);
				input_str++;
			}
			else if(strstr(argv[3], "out" )!=NULL)
			{
				
				output_filename1 = strchr(argv[3], eq);
				output_filename1++;
				output_filename2 = strchr(argv[3], eq);
				output_filename2++;
				
			}
			else
			{
				fprintf(stderr, "Error: Enter valid arguements.\n");
				exit(0);
			}
			if(argc==5)
			{
				encryption(argv[4], output_filename1, output_filename2, input_str, argc);
							
			}
			else
			{
				encryption(s_null, output_filename1, output_filename2, input_str, argc);
			}
			

		}
	}

	else if(strcmp(argv[1], "merge")==0)
	{
		if(argc!=4)
		{
			fprintf(stderr, "Enter valid arguements\n");
			exit(0);
		}
		else
		{
				FILE *fp1 = NULL;
				FILE *fp2 = NULL;
				fp1 = fopen(argv[argc-2], "r");
				fp2 = fopen(argv[argc-1], "r");
				if((fp1 == NULL) || ( fp2 == NULL))
				{
					fprintf(stderr, "ERROR: Invalid file name. File does not exist. \n");
					return 0;
				}

			   	merge(fp1, fp2);

				fclose(fp1);
				fclose(fp1);
			
		}
	}
	else if(strcmp(argv[1], "decrypt") == 0) 
	{
		if(argc == 3) 
		{
			FILE *fp= NULL;
			fp = fopen(argv[2], "r");
			if(fp != NULL) 
			{	
				decryption(fp);
			}
			else
			{
				fprintf(stderr, "ERROR: input file %s does not exist.\n", argv[2]);
				return 0;
			}

		} 
		else if(argc ==2)
		{
			decryption(stdin);
		}
		else
		{
			fprintf(stderr, "Invalid arguements\n");
		}
	}
	else
	{

	}


}
	return 0;

}
