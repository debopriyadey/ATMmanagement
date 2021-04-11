#include<stdio.h>
#include<stdlib.h>

main()
{
	FILE *fp, *ft;
	char another, choice,ename[100];
	
	struct emp
	{
		char name[100];
		int age;
		float sal;
	};
	struct emp e;
	int reclen=sizeof(e);
	
	fp=fopen("EMP.DAT","r+");
	if(fp==NULL)
	{
		fp=fopen("EMP.DAT","w+");
		if(fp==NULL)
		{
			printf("\nFile cannot be cretaed/opened...");
			exit(0);
		}
	}
}
