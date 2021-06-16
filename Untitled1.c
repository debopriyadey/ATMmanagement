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

struct profile
{
	int id;
	int password;
};

struct account a;
struct account m;
struct profile admin;
int addon, deduct, remain;
int deposit(struct account);
int withdraw(struct account);
void details(struct account,int);
void customer();
void manager();
void list();
void add();
void modify();
int reclen=sizeof(a);
int bal;

int main()
{
	int choice;
	printf("\nENTER AS \n1. MANAGER \n2. CUSTOMER");
	printf("\nEnter choice= ");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			manager();
			break;
			
		case 2:
			customer();
			break;
			
		default:
			printf("\nEnter the correct choice!!!");
	}
	
	return 0;
}

void manager()
{
	FILE *fm;
	int id,flag=0;
	int pass,ch;
	fm = fopen("Manager.dat","rb+");
	if(fm==NULL)
	{
		fm = fopen("Manager.dat","wb+");
		if(fm==NULL)
		{
			printf("\nFile cannot be opened");
			exit(0);
		}
	}
	printf("\nEnter the manager id= ");
	scanf("%d",&id);
	rewind(fm);
	while(!feof(fm))
	{
		fscanf(fm,"%d %d",&admin.id, &admin.password);
		if(id==admin.id)
		{
			printf("Enter the password= ");
			scanf("%d",&pass);
			if(pass==admin.password)
			{
				printf("\n...Access Granted...\n");
				flag=1;
				break;
			}
		}
		else
		{
			continue;
		}
	}

	if(flag==1)
	{
		printf("Enter \n1.List all accounts \n2.Add account \n3.Modify existing account \n4.Exit");
		while(1)
		{
			printf("\nEnter choice= ");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					list();
					break;
					
				case 2:
					add();
					break;
					
				case 3:
					modify();
					break;
				
				case 4: 
					exit(1);
					
				default:
					printf("\nEnter the correct choice!!!");
			}
		}
	}
	else 
	{
		printf(".....Acesses denied......");

	}
}

void list()
{
	FILE *fp;
	fp = fopen("BankAcc.dat", "rb+");
	if(fp==NULL)
	{
		fp = fopen("BankAcc.dat", "wb+");
		if(fp==NULL)
		{
			printf("\nFile cannot be created/opened...");
			exit(0);
		}
	}
	rewind(fp);
	while(!feof(fp))
	{
		fscanf(fp, "%s %d %d %d", a.name,&a.num,&a.pin,&a.balance);
		printf("%s %d %d %d\n", a.name,a.num,a.pin,a.balance);
	}
}

void add()
{
	FILE *fp;
	char another;
	fp = fopen("BankAcc.dat", "rb+");
	if(fp==NULL)
	{
		fp = fopen("BankAcc.dat", "wb+");
		if(fp==NULL)
		{
			printf("\nFile cannot be created/opened...");
			exit(0);
		}
	}
	fseek(fp,0,SEEK_END);
	another='Y';
	while(another=='Y')
	{
		printf("\nEnter Name \tAccount number \tPin \tBalance \n");
		scanf("%s %d %d %d",a.name,&a.num,&a.pin,&a.balance);
		fprintf(fp,"\n%s %d %d %d",a.name,a.num,a.pin,a.balance);
		printf("\nWant to add more accounts? ");
		fflush(stdin);
		another=getchar();
    }
    fclose(fp);
}

void modify(){
    char mname[100];
    int reclen;
	printf("\nEnter name of the holder whose record needs to be changed....");
	scanf("%s", mname);
	fflush(stdin);
    FILE *fp;
	fp = fopen("BankAcc.dat", "rb+");
	if(fp==NULL)
	{
		fp = fopen("BankAcc.dat", "wb+");
		if(fp==NULL)
		{
			printf("\nFile cannot be created/opened...");
			exit(0);
		}
	}
    
	while (!feof(fp))
	{
	    fscanf(fp, "%s %d %d %d", a.name,&a.num,&a.pin,&a.balance);
	    if (strcmp(a.name, mname) == 0)
	    {
	        printf("\nEnter Name \tAccount number \tPin \tBalance \n");
	        scanf("%s %d %d %d", m.name,&m.num,&m.pin,&m.balance);
	        fseek(fp, reclen, SEEK_CUR);
			//fwrite(&m, reclen, 1, fp);
	        fprintf(fp, "\n%s %d %d %d", m.name,m.num,m.pin,m.balance);
	        printf("\nFile write complete...");
	        break;
	        //fseek(fp,0,SEEK_END);
	        //fseek(fp,0,SEEK_SET);
	        //fscanf(fp,"%s %d %f",e.name,&e.age,&e.sal);
	    }
	}
	
	/*while (fread(&a, reclen, 1, fp) == 1)
	{
	    if (strcmp(a.name, mname) == 0)
	    {
	        printf("\nEnter Name \tAccount number \tPin \tBalance \n");
	        scanf("%s %d %d %d", m.name,&m.num,&m.pin,&m.balance);
	        fseek(fp, -reclen, SEEK_CUR); 
	        fwrite(&m, reclen, 1, fp);
	        printf("\nFile write complete...");
	        break;
	    }
	}*/
	fclose(fp);
}


void customer()
{
	FILE *fp;
	int n,i;
	int ch,z,k,pointer=0;
	int flag = 0,counter=0;
	int balance;
	char temp_name[50];

	
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
	
	// check the A/c num then copy the data to struct a
	printf("Enter the Account number= ");
	scanf("%d",&n);
	rewind(fp);
	while(!feof(fp)) //The counter is running one extra time
	{
		fscanf(fp,"%s %d %d %d",a.name, &a.num, &a.pin, &a.balance);
		if(a.num == n)
		{
			printf("\nA/c No. Matched");
			printf("\nEnter pin= ");
			scanf("%d",&k);
			if(a.pin==k)
			{
				flag = 1;
				break;
			}
		}
		else {
			continue;
		}
	}
	
	if(flag == 1)
	{
		strcpy(temp_name,a.name);                            
		// temp_name is used to store the name temporarily for future use.
		printf("\n\n1.Check info\n2.Deposit\n3.Withdraw\n4.Exit\n");
		balance = a.balance;	
		while(1)
		{
			printf("\nEnter choice= ");
			scanf("%d",&ch);
			switch(ch)
			{
				case 1:
					z = a.balance;
					pointer=1;
					details(a,pointer);
					break;
					
				case 2:
					z = deposit(a);
					pointer=2;
					a.balance = z;
					details(a,pointer);
					break;
					
				case 3:
					if(a.balance<=100)
					{
						z = withdraw(a);
						pointer=3;
						a.balance = z;
						details(a,pointer);	
					}
					else 
					{
						printf("\nInsufficient balance...");
					}
					break;
				
				case 4:
				rewind(fp);  //rewind makes the pointer point towards starting
				struct account b;
				while(fread(&a,reclen,1,fp)==1)
				{
					if(strcmp(a.name,temp_name)==0)
					{
						strcpy(a.name,b.name);
						b.num=a.num;
						b.balance=bal;
						b.pin=a.pin;
						fseek(fp,-reclen,SEEK_CUR); //fseek(fp,0,SEEK_END);
						fwrite(&b,reclen,1,fp);
						break;
					}
				}              
					fclose(fp);
					exit(1);
						
				default:
					printf("\nEnter correct choice!!!");
			}
		}
	}
	else 
	{
		printf("......User Credential not matched........");
	}
}

/*struct account* create(struct account* p,int acc_num,char* name,int bal)
{
	p = (struct account*)malloc(sizeof(struct account));
	strcpy(p->name,name);
	p->num = acc_num;
	p->balance = bal;
	return p;
}*/

int deposit(struct account a)
{
	bal= a.balance;
	printf("\nYour current balance = %d", bal);
	printf("\nEnter the amount you want to deposit= ");
	scanf("%d", &addon);
	remain=(bal+addon);
	return remain;
	
}

int withdraw(struct account a)
{
	bal = a.balance;
	printf("\nYour current balance = %d", bal);
	printf("\nEnter the amount you want to take out= ");
	scanf("%d",&deduct);
	if(deduct<=bal)
	{
		remain = (bal-deduct);
		printf("\nWithdrawl successful!!!");
		return remain;
	}
	else
	{
		printf("\nInsufficient balance!!!");
		return 0;
	}
}

void details(struct account a,int pointer)
{
	if(pointer==1){
		printf("\n\n....The receipt....");
		printf("\nName of the account holder = %s",a.name);
		printf("\nAccount number = %d",a.num);
		printf("\nBalance = %d",a.balance);
		printf("\n.....Thank You.....");
	}
	else if(pointer==2){
		printf("\n\n....The receipt....");
		printf("\nName of the account holder = %s",a.name);
		printf("\nAccount number = %d",a.num);
		printf("\nThe amount added = %d",addon);
		printf("\nBalance = %d",a.balance);
		printf("\n.....Thank You.....");
	}
	else if(pointer==3){
		printf("\n\n....The receipt....");
		printf("\nName of the account holder = %s",a.name);
		printf("\nAccount number = %d",a.num);
		printf("\nThe amount taken out = %d",deduct);
		printf("\nBalance = %d",a.balance);
		printf("\n.....Thank You.....");
	}	
}
