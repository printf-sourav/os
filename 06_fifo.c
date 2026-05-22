#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>


int main(){
	int fd;
	char mes[] = "Hello";
	
	mkfifo("myfifo",0666);
	
	fd=open("myfifo",O_WRONLY);
	
	write(fd,mes,sizeof(mes));
	
	close(fd);
	return 0;
}

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>


int main(){
	int fd;
	
	char mes[20];
	
	fd=open("myfifo",O_RDONLY);
	
	read(fd,mes,sizeof(mes));
	
	printf("Message: %s",mes);
	
	return 0;
}
