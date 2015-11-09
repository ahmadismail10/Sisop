#include<stdio.h>
#include<pthread.h>

int sum;
int total;

void *prime_thread(void *args)
{
	int i, n,count=0;
	n=*((int*)args);
	for(i=1; i<=n; i++)
	{
		if(n%i==0)
		{
			count++;
		}
	}
	if(count==2)
	{
		sum = sum + 1;			
		printf ("%d prima\n",n);
		total=total+n;
	}
	else printf("%d bukan prima\n",n);
}

int main()
{
	int i, input;
	printf("Masukkan Nilai : ");
	scanf("%d",&input);
	pthread_t a[input];
	int b[input];
	for(i=2; i<input; i++)
	{
		b[i]=i;
		pthread_create(&a[i],NULL,prime_thread,&b[i]); 	
	}
	for(i=2; i<input; i++)
	{
		pthread_join(a[i],NULL); 
	}
	printf("Total bilangan prima Kurang dari %d ada %d\n",input, sum);
	printf("Total semua nilainya adalah %d\n",total);
	return 0; 
}
