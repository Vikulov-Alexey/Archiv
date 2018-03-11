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
	int sizeF[1];
	char buf[1];
	int r=open(argv[1],O_RDONLY);
	if(argc!=2)
	{
		printf("Некорректное название архива\n");
		close(r);		
		return 1;		
	}
	if(r<0)
	{
		printf("Ошибка открытия\n");
		return 1;		
	}
	while(1)
	{
		int n=read(r,&nameF,sizeName);
		if(n<sizeName)
			break;
		int w=open(nameF,O_WRONLY|O_CREAT,0664);
		if(w<0)
		{
			printf("Ошибка\n");
			close(r);
			close(w);
			return 1;		
		}
		int err=read(r,&sizeF,sizeof(int));
		if(err<0)
		{
			printf("Ошибка чтения\n");
			close(r);
			close(w);
			return 1;		
		}
		while(sizeF[0]>1)
		{
			err=read(r,&buf,1);
			if(err<0)
			{
				printf("Ошибка чтения\n");
				close(r);
				close(w);
				return 1;		
			}
			err=write(w,&buf,1);
			if(err<0)
			{
				printf("Ошибка записи\n");
				close(r);
				close(w);
				return 1;		
			}
			sizeF[0]=sizeF[0]-1;
		}
		err=read(r,&buf,sizeF[0]);
		if(err<0)
		{
			printf("Ошибка чтения\n");
			close(r);
			close(w);
			return 1;		
		}
		err=write(w,&buf,sizeF[0]);
		if(err<0)
		{
			printf("Ошибка записи\n");
			close(r);
			close(w);
			return 1;		
		}
		close(w);
	}
	close(r);
	return 0;
}
