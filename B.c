#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define sizeName 128
#define sizeSize 10

int main(int argc,char *argv[])
{
	char nameF[sizeName];
	int r,w;
	int sizeF[1];
	char buf[1];
	int n;
	r=open(argv[1],O_RDONLY);
	if(argc!=2)
		printf("Не введено название архива\n");
	while(1)
	{
		n=read(r,&nameF,sizeName);
		if(n<1)
			break;
		w=open(nameF,O_WRONLY|O_CREAT,0664);
		read(r,&sizeF,sizeof(int));
		while(sizeF[0]>1)
		{
			read(r,&buf,1);
			write(w,&buf,1);
			sizeF[0]=sizeF[0]-1;
		}
		read(r,&buf,sizeF[0]);
		write(w,&buf,sizeF[0]);
		close(w);
	}
	close(r);
	return 0;
}
