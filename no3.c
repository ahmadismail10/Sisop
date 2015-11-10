#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *task1 ()
{
	FILE *baca, *salin;
	baca = fopen("file.txt", "r");
	salin = fopen("salinan1.txt", "w");

	char kar;
	while((kar=fgetc(baca))!=EOF)
	{
		//fprintf(salin, "thread 1 : ");
		fputc(kar,salin);
		//fprintf(salin, "\n");
	}
	fclose(baca);
	fclose(salin);
}

void *task2 ()
{
        FILE *in, *out;
	in = fopen("salinan1.txt","r");
	out = fopen("salinan2.txt","w");

	char isi;;
	while((isi=fgetc(in))!=EOF) 
	{
		//fprintf(out, "thread 2 : ");
		fputc(isi,out);
		//fprintf(out, "\n");
	}
	fclose(in);
	fclose(out);
}

void main()
{
        pthread_t t1, t2;
        pthread_create(&t1, NULL, task1, NULL);
	pthread_join(t1, NULL);
        pthread_create(&t2, NULL, task2, NULL);
        pthread_join(t2, NULL);
}

