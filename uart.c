#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int set_interface_attribs(int fd, int speed)
{
	struct termios tty;

	if (tcgetattr(fd, &tty) < 0)
	{ 
		printf("error from tcgetattr: %s\n", strerror(errno));
		return -1;
	}

	cfsetispeed(&tty, (speed_t)speed);
	tty.c_cflag |=(CLOCAL | CREAD);
	tty.c_cflag &= ~CSIZE;
	tty.c_cflag |=CS8;
	tty.c_cflag &= ~PARENB;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;


	tty.c_iflag = IGNPAR;
	tty.c_iflag = 0;

	if (tcsetattr(fd, TCSANOW, &tty) !=0)
	{
		printf("error from tcsetattr: %s\n", strerror(errno));
		return -1;
	}
	return 0;

}



int main()
{
	char *portname ="/dev/ttyS3";
	int fd;
	int wlen;
	int rdlen;
	int ret;

	char res[5];
	char arr[7]="ABCDEF";
	unsigned char buf[7];

	fd = open(portname,O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0)
	{
		printf("error opening %s: %s\n", portname, strerror(errno));
		return -1;
	}
	set_interface_attribs(fd, B9600);

	wlen = write(fd,arr,sizeof(arr));
	sleep(1);

	rdlen= read(fd,buf,sizeof(buf));
	printf("%s \n",buf);

return 0;
}
