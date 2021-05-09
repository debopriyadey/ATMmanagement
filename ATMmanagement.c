#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
struct account
{
	int num;
	int pin;
	int balance;
	char name[100];
};
struct account a;

int addon, deduct, remain;
struct account* create(struct account*,int,char*,int);
//void check(struct account*,FILE *);
int deposit(struct account*);
int withdraw(struct account*);
void details(struct account*,int,int);
int main()
{
	FILE *fp;
	int n,i;
	int ch,z,k,pointer=0;
	int flag = 0,counter=0;
	int reclen = sizeof(a);
	
	struct account* p = NULL;
	
	fp = fopen("BankAcc.dat", "rb+");
	if(fp==NULL)
	{
		fp = fopen("BankAcc.dat", "wb+");
		{
			if(fp==NULL)
			{
				printf("\nFile cannot be created/opened...");
				exit(0);
			}
		}
	}
	
	//fseek(fp,0,SEEK_END);
	//fprintf(fp,"%s %d %f\n",name, num, bal);
	
	// check the A/c num then copy the data to struct a
	printf("Enter the number= ");
	scanf("%d",&n);
	rewind(fp);
	while(!feof(fp)) //The counter is running one extra time
	{
		fscanf(fp,"%s %d %d %d",a.name, &a.num, &a.pin, &a.balance);
		if(a.num == n){
			printf("\nA/c No. Matched");
		//	printf("\n%s, %d, %d",a.name, a.num, a.balance);
			flag = 1;
			break;
		}
		else {
		//	printf("\nEnter valid account number!!!");
			continue;
		}
	}
	
	if(flag == 1)
	{
		printf("\nEnter pin= ");
		
		scanf("%d",&k);
		if(a.pin==k)
		{
		if(p==NULL)
		{
			p=create(p,a.num,a.name,a.balance);
		}
		printf("\n\n1.Check info\n2.Deposit\n3.Withdraw");	
		while(1)
		{
			printf("\nEnter choice= ");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					//check;
					pointer=1;
					details(p,z,pointer);
					break;
					
				case 2:
					z = deposit(p);
					pointer=2;
					details(p,z,pointer);
					break;
					
				case 3:
					z = withdraw(p);
					pointer=3;
					if(z!=0)
					details(p,z,pointer);
					break;
				
				case 4:
					struct account b;
					rewind(fp);  //rewind makes the pointer point towards starting
					while(!feof(fp))
					{
						printf("1");
						if(strcmp(a.name,p->name)==0)
						{
							strcpy(a.name,b.name);
							printf("%s", b.name);
							b.num=a.num;
							b.balance=p->balance;
							b.pin=a.pin;
							fseek(fp,-reclen,SEEK_CUR); //fseek(fp,0,SEEK_END);
							fwrite(&b,reclen,1,fp);
							break;
						}
					}
					break;
				/*while(fread(&e,reclen,1,fp)==1)
				{
					if(strcmp(e.name,ename)==0)
					{
						printf("\nEnter new name, age and salary: ");
						scanf("%s%d%f",ee.name,&ee.age,&ee.sal);
						fseek(fp,-reclen,SEEK_CUR); //fseek(fp,0,SEEK_END);
						fwrite(&ee,reclen,1,fp);
						break;
					}
				}*/
				case 5:
					fclose(fp);
					exit(1);
						
				default:
					printf("\nEnter correct choice!!!");
			}
		}
		}
		return 0;
	}
}

struct account* create(struct account* p,int acc_num,char* name,int bal)
{
	p = (struct account*)malloc(sizeof(struct account));
	strcpy(p->name,name);
	p->num = acc_num;
	p->balance = bal;
	return p;
}

int deposit(struct account* p)
{
	int bal= (p->balance);
	printf("\nYour current balance = %d", bal);
	printf("\nEnter the amount you want to deposit= ");
	scanf("%d", &addon);
	remain=(bal+addon);
	p->balance = remain;
	return remain;
	
}

int withdraw(struct account* p)
{
	int bal = (p->balance);
	printf("\nYour current balance = %d", bal);
	printf("\nEnter the amount you want to take out= ");
	scanf("%d",&deduct);
	if(deduct<=bal)
	{
		remain = (bal-deduct);
		printf("\nWithdrawl successful!!!");
		p->balance = remain;
		return remain;
	}
	else
	{
		printf("\nInsufficient balance!!!");
		return 0;
	}
}

void details(struct account* p,int balance,int pointer)
{
	if(pointer==1){
		printf("\n\n....The receipt....");
		printf("\nName of the account holder = %s",p->name);
		printf("\nAccount number = %d",p->num);
		printf("\nBalance = %d",p->balance);
		printf("\n.....Thank You.....");
	}
	else if(pointer==2){
		printf("\n\n....The receipt....");
		printf("\nName of the account holder = %s",p->name);
		printf("\nAccount number = %d",p->num);
		printf("\nThe amount added = %d",addon);
		printf("\nBalance = %d",p->balance);
		printf("\n.....Thank You.....");
	}
	else if(pointer==3){
		printf("\n\n....The receipt....");
		printf("\nName of the account holder = %s",p->name);
		printf("\nAccount number = %d",p->num);
		printf("\nThe amount taken out = %d",deduct);
		printf("\nBalance = %d",p->balance);
		printf("\n.....Thank You.....");
	}	
}
