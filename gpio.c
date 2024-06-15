#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	
#include<stdio.h>
#include<string.h>  
#include<stdlib.h>

#define GPIO_EN  "/sys/class/gpio/export"
#define GPIO_DIR1 "/sys/class/gpio/PC13/direction"
#define GPIO_DIR2 "/sys/class/gpio/PC15/direction"
#define GPIO_DIR3 "/sys/class/gpio/PC17/direction"


#define GPIO_Val1 "/sys/class/gpio/PC13/value"
#define GPIO_Val2 "/sys/class/gpio/PC15/value"
#define GPIO_Val3 "/sys/class/gpio/PC17/value"



int main()
{
int  gpio_fd;
char gpio_buf[150];
int  gpio_num1 = 77;
int  gpio_num2 = 81;
int  gpio_num3 = 83;



int  count =10;
gpio_fd = open(GPIO_EN,O_WRONLY);
if(gpio_fd < 0)
{
printf("Unable to open the file  %s\n",GPIO_EN);
exit(0);
}
printf("Enable the GPIO");
sprintf(gpio_buf,"%d",gpio_num1);
write(gpio_fd,gpio_buf,strlen(gpio_buf));
close(gpio_fd);

printf("Configuring GPIO direction  \n");

gpio_fd = open(GPIO_DIR1,O_WRONLY);
if(gpio_fd < 0)
{
printf("Unable to open the file   %s",GPIO_DIR1);
exit(0);
}

write(gpio_fd,"out",3);
close(gpio_fd);

printf("Set the value into GPIO_Val1 \n");

gpio_fd = open( GPIO_Val1,O_WRONLY);
if(gpio_fd < 0)
{
printf("Unable to open the file   %s",GPIO_Val1);
exit(0);
}
printf("Toggling the GPIO_PIN");
while(count--)
{
write(gpio_fd,"1" ,1);
sleep(5);
write(gpio_fd,"0" ,1);
sleep(5);
}
close(gpio_fd);
}
