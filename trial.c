#define CHANNEL 0
#define SPEED 12500000
#define MODE 0
#define DATA_SIZE 2880

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

	uint8_t output_1[2880];
	uint8_t output_2[2880];
	

int main(int argc, char **argv)
{
	int i=0,j=0;

	int flag=0;

	FILE *fd=fopen("frame.txt","r");

	unsigned char temp[4];

	char buff;

	buff=fgetc(fd);

	
	while(feof(fd)==0)
	{
		while(buff!='.')
		{
			temp[i++]=buff;
			buff=getc(fd);
		}
		temp[i]='\0';
		if(j==DATA_SIZE)
		{
			j=0;
			flag=1;
		}

		(flag==0)?(output_1[j++]=atoi(temp)):(output_2[j++]=atoi(temp));

		strcpy(temp,"000\0");

		i=0;
		
		fseek(fd,3,SEEK_CUR);
		buff=fgetc(fd);
	}
	
	for(i=0;i<DATA_SIZE;i++)
	{
		printf("%d-->%x\t",i,output_1[i]);
		printf("%x\n",output_2[i]);
	}

	fclose(fd);
}
