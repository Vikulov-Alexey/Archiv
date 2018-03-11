#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#define sizeName 128

int main(int argc,char *argv[])
{
	struct stat st;
	char name[sizeName]; //хранит текущее имя
	int i=1;
	int w=0,r=0;
	int sizeRA;
	int stat;
	char buf[1];
	long err;

	if(i<argc)
		w=open("Archive",O_WRONLY|O_CREAT,0664);
	else
		printf("Не указаны названия файлов\n");
		
	while(i<argc)
	{
		int sizeR=0;sizeRA=0;		
		int r=open(argv[i],O_RDONLY);
		if(r<0)
		{
			printf("Файл %s не может быть добавлен в архив\n",argv[i]);
			err=close(r);
			if(err<0)
			{
				printf("Ошибка записи\n");
				return 1;
			}
			break;
		}
		//Подсчёт размера файла
		do{
			sizeR=read(r,&buf,1);
			sizeRA=sizeRA+1;
		}while(sizeR==1);
		sizeRA=sizeRA-1;
		//Запись в файл
		err=lseek(r,0,SEEK_SET);
		if (err==1L)
		{
			printf("Ошибка\n");
			return 1;
		}

		err=write(w,argv[i],sizeName);
		if(err<0)
		{
			printf("Ошибка записи\n");
			return 1;
		}
		err=write(w,&sizeRA,sizeof(sizeRA));
		if(err<0)
		{
			printf("Ошибка записи\n");
			return 1;
		}
	
		do{
			sizeR=read(r,&buf,1);
			if(sizeR>0)
				err=write(w,&buf,1);
			if(err<0)
			{
				printf("Ошибка записи\n");
				return 1;
			}
		}while(sizeR==1);
		err=close(r);
		if(err<0)
		{
			printf("Ошибка\n");
			return 1;		
		}
		i++;
	}
	err=close(w);
	if(err<0)
	{
		printf("Ошибка записи\n");
		return 1;
	}
	return 0;
}
