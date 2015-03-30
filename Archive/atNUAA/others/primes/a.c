#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int main()
{
	unsigned long i,count;
	unsigned long num;
	int sta;
	FILE *pf;
	unsigned long primes[MAX];
	unsigned long statis[10]={0,0,0};

	primes[0]=2;
	num=1;
	for(count=1;count<MAX;count++)
	{
		sta=1;
		while(sta>0)
		{
			num+=2;
			for(i=0;i<count && sta>0;i++)
				if(num%primes[i]==0)
					break;
			if(i==count)
				sta=0;
		}
		primes[count]=num;
	}

	for(count=0;count<MAX;count++)
		statis[(primes[count]%10)]++;
	for(i=0;i<10;i++)
		printf("%ld:%f\n",i,statis[i]/(float)MAX);

	pf=fopen("primes.txt","w");
	for(count=0;count<MAX;count++)
		fprintf(pf,"%ld\n",primes[count]);
	fclose(pf);

	return 0;
}
