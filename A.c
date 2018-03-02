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
	int sizeR;
	int sizeRA;
	int r,w=0;
	int stat;
	char buf[1];

	if(i<argc)
		w=open("Archiv",O_WRONLY|O_CREAT,0664);
	else
		printf("Не указаны названия файлов\n");
		
	while(i<argc)
	{
		sizeR=0;sizeRA=0;		
		r=open(argv[i],O_RDONLY);
		if(r<0)
		{
			printf("Файл %s не может быть добавлен в архив\n",argv[i]);
			close(r);
			break;
		}
		//Подсчёт размера файла
		do{
			sizeR=read(r,&buf,1);
			sizeRA=sizeRA+1;
		}while(sizeR==1);
		//Запись в файл
		lseek (r, 0, SEEK_SET);

		write(w,argv[i],sizeName);
		write(w,&sizeRA,sizeof(sizeRA));
	
		do{
			sizeR=read(r,&buf,1);
			write(w,&buf,1);
		}while(sizeR==1);
		close(r);
		i++;
	}
	close(w);
	return 0;
}
