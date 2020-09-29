#define CHANNEL 0
#define SPEED 12500000
#define MODE 0

#include <wiringPiSPI.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

	uint8_t output[5760];
	uint8_t input[5760];
	uint8_t input2[4000];

void setup_rpi_spi()
{
     //   if( wiringPiSPISetupMode (CHANNEL,SPEED,MODE)==-1)
        if( wiringPiSPISetup(CHANNEL,SPEED)==-1)
        {
                perror("Could not initialise SPI\n");
                exit(0);
        }

}


int main(int argc, char **argv)
{
int spi_fd=0;
	setup_rpi_spi();
	spi_fd=wiringPiSPIGetFd(CHANNEL);


	int i=0,j=0;

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
		output[j++]=atoi(temp);

		strcpy(temp,"000\0");

		i=0;
		
		fseek(fd,3,SEEK_CUR);
		buff=fgetc(fd);
	}
/*	
	for(i=0;i<5760;i++)
	{
		printf("%d\n",output[i]);
	}*/

	fclose(fd);

//	write(spi_fd,output,5760);
	write(spi_fd,output,4000);
//	read(spi_fd,input,5760);
	read(spi_fd,input2,4000);

	
//	wiringPiSPIDataRW(0,output,5760);

	for(i=0;i<4000;i++)
	{
		printf("%x\t",input2[i]);
	}
}
