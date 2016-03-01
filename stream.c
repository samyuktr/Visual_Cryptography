#include "function.h"
/*
Samyukta Satish Rao
University of Southern California
*/

//---------------generates md5 key for the homework---------------------------------------------------------------
unsigned char *  stream_call(int l, char * p, int flag)
{
    // variables required for md5 generation. 

   	char md5_buf[MD5_DIGEST_LENGTH];
    int len=strlen(p)+2+MD5_DIGEST_LENGTH;
    char *s=malloc(len+1);
    int i=0, m=0, j=0; // variables for the loop. 
    int counter = 0; // counter to contain the while loop 
    unsigned char * key_str = calloc(l, sizeof(char));
    key_str[l] = '\0'; // variable to hold the key in hex format for use in encryt function.

//-----------------------------------------------------------------------------------------------------------------
    
    MD5((unsigned char *)p, (unsigned  int)strlen(p), (unsigned char *)md5_buf);
    unsigned char * ret_ptr;

    if(flag==0) // hw1 part2
    {
        while(1) 
        {
            counter=counter+8;
            if(counter<=l) // normal 8 byte generation
            {
                sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, p);
                memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
                MD5((unsigned char *)s, (unsigned int)len, (unsigned char * )md5_buf);
                fwrite(md5_buf, 1, sizeof(md5_buf)>>1, stdout);
                
            }

            else if(counter>l) // boundary condition
            {
                int out_no = 8-(counter-l); // left over bytes to print
                if(out_no==0)
                {
                    break;
                }
                else
                {
                    sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, p);
                    memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
                    MD5((unsigned char *)s, (unsigned int)len, (unsigned char * )md5_buf);
                    fwrite(md5_buf, 1, out_no, stdout);
                    break;
         
                }
            }

         
            if (++i == 100) 
                i = 0;    
            
        }
    }
    //---------------------------------------------------------------------------------------------------------------
    else if(flag==1) // hw2 part2
    {
        while(1) 
        {
            counter=counter+8;
            if(counter<=l) // normal 8 byte genaration.
            {
                sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, p);
                memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
                MD5((unsigned char *)s, (unsigned int)len, (unsigned char * )md5_buf);
                for(m=0;m<8;m++)
                {                      
                    //sprintf((unsigned char )&key_str[j], "%c", (unsigned char)md5_buf[m]); //prints md5 key to a buffer.
                    key_str[j] = md5_buf[m];
                    j=j+1;               
                }
            }

            else if(counter>l) // boundary condition.
            {
                int out_no = 8-(counter-l); // left over bytes to print
                if(out_no==0)
                {
                    break;
                }
                else
                {
                    sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, p);
                    memcpy(s, md5_buf, MD5_DIGEST_LENGTH);
                    MD5((unsigned char *)s, (unsigned int)len, (unsigned char * )md5_buf);
                    for(m=0;m<out_no;m++)
                    {                      
                        //sprintf(&key_str[j], "%c", (unsigned char)md5_buf[m]);
                        key_str[j] = md5_buf[m];
                       
                        j=j+1;               
                    }
                    break;
         
                }
            }

            if (++i == 100) 
                i = 0;    
            
        }
       // printf("Counter value is : %d and J is: %d and last character: %c and length of key_str: %d\n\n", counter, j, key_str[3562], strlen(key_str));
        ret_ptr = key_str;
    }
//------------------------------------------------------------------------------------------------------------------
    free(s);
   
    return (unsigned char *)ret_ptr;
    

}











