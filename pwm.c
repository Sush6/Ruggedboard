
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>


char export_path[] = "/sys/class/pwm/pwmchip0/export";
char pwm_periods[] = "/sys/class/pwm/pwmchip0/pwm1/period";
char pwm_enable[] = "/sys/class/pwm/pwmchip0/pwm1/enable";
char duty_cycle[] = "/sys/class/pwm/pwmchip0/pwm1/duty_cycle";


//        ./a.out  100      1
//                period   duty cycle
int main(int argc,char **argv)
{
	int fd;
	int value,period;
	char *value_str;
	value_str=malloc(4);
	fd = open(export_path,O_WRONLY);
	if(fd < 0)
		perror("export path error \n");
	write(fd,"1",2);
	close(fd);
	
	fd = open(pwm_periods,O_WRONLY);
	if(fd < 0)
		perror("period  error \n");
	write(fd,argv[1],4);
	close(fd);

	fd = open(pwm_enable,O_WRONLY);
	if(fd < 0)
		perror("enable  error \n");
	write(fd,"1",2);
	close(fd);

	period = atoi(argv[1]);	

	value_str = argv[2];
	value  = atoi(argv[2]);

	fd = open(duty_cycle,O_WRONLY);

	while(1)
	{
	start :	sprintf(value_str,"%d",value);
		write(fd,value_str,sizeof(value_str));
		printf("pwm value : %d \n",value);
		value++;
		usleep(100000);
		if(value >= period)
		{
			value=0;
			goto start;
		}

	}
	close(fd);
}

