#define CHANNEL 0
#define SPEED 12500000
#define MODE 0
#define DATA_SIZE 2880
#define LED 0

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

	uint8_t output_1[2880];
	uint8_t output_2[2880];
	
	uint8_t input[2880];

void setup_rpi_spi()
{
        if( wiringPiSPISetup(CHANNEL,SPEED)==-1)
        {
                perror("Could not initialise SPI\n");
                exit(0);
        }

}


int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Invalid arguements\n");
		exit(1);
	}

	wiringPiSetup();
	pinMode(LED, OUTPUT);

	int spi_fd=0;
	int flag=0;

	setup_rpi_spi();

	spi_fd=wiringPiSPIGetFd(CHANNEL);


	int i=0,j=0;

	FILE *fd=fopen(argv[1],"r");

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
	
	digitalWrite (LED, HIGH);
	write(spi_fd,output_1,DATA_SIZE);
	read(spi_fd,input,DATA_SIZE);
	for(i=0;i<DATA_SIZE;i++)
	{
		printf("%x\t",input[i]);
	}
	digitalWrite (LED, LOW);

/*_____________________________________________________________________*/

	delay(1000);

	digitalWrite (LED, HIGH);
	write(spi_fd,output_2,DATA_SIZE);
	read(spi_fd,input,DATA_SIZE);
	for(i=0;i<DATA_SIZE;i++)
	{
		printf("%x\t",input[i]);
	}
	digitalWrite (LED, LOW);
	
	return 0;
}
