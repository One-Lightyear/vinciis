#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

int main(int argc, char **argv)
{
	uint8_t output[25];
	
	int i=0,j=0,flag=0;

	FILE *fd=fopen("frame2.txt","r");

	unsigned char temp[4];
	char buff;

	buff=fgetc(fd);

	
	while(feof(fd)==0)
	{
		while(buff!='.')
		{
			temp[i++]=buff;
			buff=fgetc(fd);
		
	/*		if(feof(fd)!=0)
			{
				printf("End reached\n");
				flag=1;
				break;
			}*/
		}
		temp[i]='\0';

		output[j++]=atoi(temp);
	
		if(flag==1)
		{
			break;
		}
	
		strcpy(temp,"000\0");

		i=0;
		fseek(fd,3,SEEK_CUR);
/*
		buff=fgetc(fd);
		if(buff==EOF)
		{
			printf("End here 1");
		}
		buff=fgetc(fd);
		if(buff==EOF)
		{
			printf("End here 2");
		}
		buff=fgetc(fd);
		if(buff==EOF)
		{
			printf("End here 3");
		}*/

		buff=fgetc(fd);
		if(buff==EOF)
		{
			printf("End here 4\n");
		}

/*		if(feof(fd)!=0)
		{
			printf("End reached\n");
			flag=1;
			break;
		}
*/	}

	for(i=0;i<25;i++)
	{
		printf("%d-->%d\n",i,output[i]);
	}


	fclose(fd);
}
