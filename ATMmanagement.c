#include<stdio.h>
#include<stdlib.h>

main()
{
	FILE *fp, *ft;
	char another, choice, accnum, accpin;
	
	struct acc
	{
		char name[100];
		int num;
		int pin;
		int balance;
	};
	struct acc a;
	int reclen=sizeof(a);
	
	fp=fopen("BankAcc.DAT","r+");
	if(fp==NULL)
	{
		fp=fopen("BankAcc.DAT","w+");
		if(fp==NULL)
		{
			printf("\nFile cannot be cretaed/opened...");
			exit(0);
		}
	}
}
