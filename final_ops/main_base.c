#define DATA_SIZE 2880
#define MAX 4
#define CHANNEL 0
#define SPEED 12500000
#define MODE 0
#define TRIGGER 0

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <string.h>

void setup_rpi_spi()
{
        if( wiringPiSPISetup(CHANNEL,SPEED)==-1)
        {
                perror("Could not initialise SPI\n");
                exit(0);
        }

}

int main(int argc, char ** argv)
{
	puts("arguments: file_to_read delay divide_factor")
	if(argc!=4)
	{
		printf("Invalid arguements\n");
		exit(1);
	}
	
	wiringPiSetup();
        pinMode(TRIGGER, OUTPUT);

        setup_rpi_spi();

	int spi_fd=0;
        spi_fd=wiringPiSPIGetFd(CHANNEL);

	unsigned long total_size=0;
	
	uint8_t buffer[DATA_SIZE];
	unsigned int buffer_count=0;
	uint8_t input[DATA_SIZE];

	char temp[9];
	char ok;
	int j=0;

	FILE *fd1=fopen(argv[1],"r");

	int flag_delay=0,i=0;
	uint8_t divide_factor=atoi(argv[3]);

	while(1)
	{
		ok=fgetc(fd1);

		if((feof(fd1)!=0)||((ok>=0)&&(ok<20)))
		{
			temp[j]='\0';
			buffer[buffer_count++]=atoi(temp)/divide_factor;
			
			
			digitalWrite (TRIGGER, HIGH);

                        write(spi_fd,buffer,DATA_SIZE);
			read(spi_fd,input,DATA_SIZE);
                        for(i=0;i<DATA_SIZE;i++)
                        {
                                printf("%x\t",input[i]);
                        }

                        digitalWrite (TRIGGER, LOW);
			
			total_size+=buffer_count;
			buffer_count=0;
			
			break;
		}

		if((ok!=' ')) temp[j++]=ok;
		else
		{
			temp[j]='\0';
			buffer[buffer_count++]=atoi(temp)/divide_factor;
			j=0;
		}

		if(buffer_count==DATA_SIZE)
		{
			total_size+=buffer_count;
			buffer_count=0;

			digitalWrite (TRIGGER, HIGH);
			
			write(spi_fd,buffer,DATA_SIZE);
			read(spi_fd,input,DATA_SIZE);
        		for(i=0;i<DATA_SIZE;i++)
        		{
        		        printf("%x\t",input[i]);
        		}

        		digitalWrite (TRIGGER, LOW);

			if (flag_delay==0)
			{
				flag_delay=1;
			}
			else
			{
				delay(atoi(argv[2]));
				flag_delay=0;
			}
		}
	}
	fclose(fd1);

	printf("Total data transferred = %d bytes\n",total_size);
}
