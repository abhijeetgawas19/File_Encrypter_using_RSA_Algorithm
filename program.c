#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int primechecker(int,int);
//void keygenrator();
int prikey=0,pubkey=0,N=0;
int keydiff=0;
int keyer=0;
FILE *reader,*writer;
void encryption();
void decryption();
int main(void)
{
	int ch;
	char efile[100],dfile[100];
	char character;
	int pr,qr,result;
	int i,j,e,d;
	while(1)
	{
	printf("\n");
	printf("Encryption and Decryption Application:\n");
	printf("1.Encrypt the File using RSA:\n");
	printf("2.Decrypt the File using RSA:\n");
	printf("3.Exit\n");
	printf("Enter your choice and make sure file to be encrypted/decrypted is in same folder as application file\n");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			{
				int flag=0;
				printf("Enter the 2 Prime Nos\n");
				scanf("%d%d",&pr,&qr);
				result=primechecker(pr,qr);
				if(result==2)
				{
					N=(pr-1)*(qr-1);
					for(e=2;e<N;e++)
					{
						for(d=1;d<N;d++)
						{
							if((e*d)%N==1 && (e*d)>N && e!=d)
							{
									flag++;
									pubkey=e;
									prikey=d;
									break;
							}
						}
						if(flag==1)
						{
							break;
						}
					}
				}
				else
				{
					printf("One or Both Number is Non-Prime\n");
					printf("Prime Number is mandatory \n");
				}
				if((prikey==0 && pubkey==0)||(prikey==pubkey) && result==2)
				{
					printf("Insert other combination of Prime Numbers\n");
					break;
				}
				else
				{
					printf("Private key (%d,%d)\n",prikey,N);
					printf("Public key (%d,%d)\n",pubkey,N);
				}
				encryption();
				break;
			}
		case 2:
			{
				printf("Enter the Private Key\n");
				scanf("%d",&prikey);
				printf("Enter the Public Key \n");
				scanf("%d",&pubkey);
				printf("Enter the N term \n");
				scanf("%d",&N);
				if(prikey==pubkey)
				{
					printf("Private Key and Primary Key Can't be same");
					break;
				}
				else
				{
				decryption();
				}
				break;	
			}
		case 3:
			{
				exit(0);
				break;
			}
		default:
			{
				printf("Choice You Entered is Invalid Do Try again\n");
			}
	}
	}
}
int primechecker(int x,int y)
{
	int checkerflag=0,flag=0,i;
	for(i=2;i<=x/2;i++)
	{
		if(x%i==0)
			{
				flag++;
			}
	}
	if(flag==0)
	{
		++checkerflag;
	}
	for(i=2;i<=y/2;i++)
	{
		if(y%i==0)
			{
				flag++;
			}
	}
	if(flag==0)
	{
			++checkerflag;
	}
	return checkerflag;
}
void encryption()
{
	char efile[100];
	char ichar;
	printf("Enter the File Name with extension (No Spaces!!!)\n");
	scanf(" %s",&efile);
	reader=fopen(efile,"r");
	writer=fopen("encrypt_rsa.txt","w");
	if(reader==NULL)
	{
		printf("File doesn't exist Try Again!!!!");
		exit(0);
	}
	keyer=N/pubkey;
	//printf("Encryption Keyer:%d\n",keyer);
	ichar=fgetc(reader);
	while(ichar!=EOF)
	{
		ichar=ichar+keyer;
		fprintf(writer,"%c",ichar);
		ichar=fgetc(reader);
	}
	printf("File Encrypted Successfully with RSA");
	fclose(writer);
	fclose(reader);
	keyer=0;
}
void decryption()
{
	int pri,pub;
	pri=prikey;
	pub=pubkey;
	keydiff=0;
	keyer=0;
	char efile[100];
	char ichar;
	printf("Enter the File Name with extension (No Spaces!!!)\n");
	scanf(" %s",&efile);
	reader=fopen(efile,"r");
	writer=fopen("decrypt_rsa.txt","w");
	if(reader==NULL)
	{
		printf("File doesn't exist Try Again!!!!");
		exit(0);
	}
	keydiff=pri-pub;
	prikey=prikey-keydiff;
	//printf("%d\n",N);
	keyer=0;
	keyer=N/prikey; //Issue;
	//printf("Keyer Decrypt:%d\n Private Key:%d\n Public Key:%d\n N term:%d\n",keyer,prikey,pubkey,N);
	ichar=fgetc(reader);
	while(ichar!=EOF)
	{
		ichar=ichar-keyer;
		fprintf(writer,"%c",ichar);
		ichar=fgetc(reader);
	}
	printf("File Decrypted Successfully with RSA");
	fclose(writer);
	fclose(reader);
}
