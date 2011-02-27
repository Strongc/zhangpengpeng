#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char argv[])
{
	int num;
	int temp;
	char beansType[32][20];
	char beansName[32][20];
	char beansBigName[32][20];

	printf("Please input the number of your beans (<32) :\n");
	scanf("%d",&num);
	printf("Now please input your beans' type and name:\n");
	printf("for example : int mybeans (notice: no semicolon!)\n");
	for(temp=0;temp<num;temp++)
	{
		scanf("%s %s",beansType[temp],beansName[temp]);
	}

	for(temp=0;temp<num;temp++)
	{
		strcpy(beansBigName[temp],beansName[temp]);
		beansBigName[temp][0]=beansBigName[temp][0]-'a'+'A';
	}

	for(temp=0;temp<num;temp++)
	{
		printf("\n");
		printf("public void set%s(%s %s)\n",beansBigName[temp],beansType[temp],beansName[temp]);
		printf("{\n");
		printf("\tthis.%s = %s;\n",beansName[temp],beansName[temp]);
		printf("}\n");
		printf("public %s get%s()\n",beansType[temp],beansBigName[temp]);
		printf("{\n");
		printf("\treturn this.%s;\n",beansName[temp]);
		printf("}\n");
	}
	
	printf("\n\n");
	return 0;
}

