#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

struct Transaction
{
	char username[100];
	time_t timestamp;
	int type;//0-ȡ�1-���
	int amount;
	
	struct Transaction * next;
};
typedef struct Transaction Transaction;

//���׼�¼��Ϣ���� 
Transaction * tHead=NULL;
Transaction * tTail=NULL;
Transaction * curTransaction=NULL;

struct Account
{
	char name[100];
	char password[7];
	char username[19];
	char idCard[19];
	char tel[12];
	float money;
	struct Account* next;
};
typedef struct Account Account;
int language;//1-����,2-English
Account* head=NULL;//ָ��ͷ����ָ��
Account* tail=NULL;//ָ��β����ָ��
Account *curAccount=NULL;//��¼��ǰ�˻�
Account * otherAccount=NULL;//��¼�Է��˻�  
int findAccount(Account a)
{
	Account *curp=head;
	while(curp!=NULL)
	{
		if((strcmp(curp->username,a.username)==0)&&(strcmp(curp->password,a.password)==0))
		{
			curAccount=curp;
			return 1; 
		}
		curp=curp->next;
	}
	return 0;
}

void drawMoney()
{
	if(language==1)
	{
		printf("������ȡ���");
	    int money;
	    scanf("%d",&money);
	
	    //��֤���
	    if(curAccount->money>=money)
	    {
		    printf("ȡ��ɹ���\n");
		    curAccount->money-=money;
		
		    //�������
		    Transaction * newNode=(Transaction*)malloc(sizeof(Transaction)); 
		
		    //����ʼ��
		    newNode->next=NULL;
		    strcpy(newNode->username,curAccount->username);
		    newNode->timestamp=time(NULL);
		    newNode->type=0;
		    newNode->amount=money;
		
	    	//��ӽ�㵽����
		    if(tHead==NULL)
		    {
			    tHead=newNode;
			    tTail=newNode;
		    }
		    else
		    {
			    tTail->next=newNode;
			    tTail=newNode;
		    }
	    } 
	    else
	    {
		    printf("���㣡\n");
	    }
	}
	else if(language==2)
	{
		printf("enter your draw money��");
	    int money;
	    scanf("%d",&money);
	
	    //��֤���
	    if(curAccount->money>=money)
	    {
		    printf("withdrawal succeeded��\n");
		    curAccount->money-=money;
		
		    //�������׼�¼...	
		
		    //�������
		    Transaction * newNode=(Transaction*)malloc(sizeof(Transaction)); 
		
		    //����ʼ��
		    newNode->next=NULL;
		    strcpy(newNode->username,curAccount->username);
		    newNode->timestamp=time(NULL);
		    newNode->type=0;
		    newNode->amount=money;
		
		    //��ӽ�㵽����
		    if(tHead==NULL)
		    {
			    tHead=newNode;
			    tTail=newNode;
		    }
		    else
		    {
			    tTail->next=newNode;
			    tTail=newNode;
		    }
	    } 
	    else
	    {
		    printf("sorry,your credit is running low��\n");
	    }
	}
}

void saveMoney()
{
	if(language==1)
	{
		printf("���������");
	    int money;
	    scanf("%d",&money);
	    printf("���ɹ���\n");
	    curAccount->money+=money;
	}
	else if(language==2)
	{
		printf("enter your save money��");
	    int money;
	    scanf("%d",&money);
	    printf("deposit succeeded��\n");
	    curAccount->money+=money;
	}
}

void updataPassword()//�޸����� 
{
	if(language==1)
	{
		printf("�����������:");
	    char oldpassword[100];
	    scanf("%s",oldpassword);
	    if(strcmp(oldpassword,curAccount->password)==0)
	    {
		    printf("������������:");
		    scanf("%s",curAccount->password);
		    if(strcmp(curAccount->password,oldpassword)==0)
		    {
			    for(int i=0;i<3;i++)
			    {
				    printf("���������������ͬ������������:");
			        scanf("%s",curAccount->password);
			        if(strcmp(curAccount->password,oldpassword)!=0)
			        {
			    	    printf("�޸ĳɹ�!");
			    	    break;
				    }
			    }
		    }
		    else
		    {
			    printf("�޸ĳɹ�!\n");
		    }
	    }
	    else
	    {
		    printf("������󣬲����޸�!\n");
	    }
	}
	else if(language==2)
	{
		printf("enter your old code:");
	    char oldpassword[100];
	    scanf("%s",oldpassword);
	    if(strcmp(oldpassword,curAccount->password)==0)
	    {
		    printf("enter your new code:");
		    scanf("%s",curAccount->password);
		    if(strcmp(curAccount->password,oldpassword)==0)
		    {
			    for(int i=0;i<3;i++)
			    {
				    printf("the new code is the same as the old code,re-enter:");
			        scanf("%s",curAccount->password);
			        if(strcmp(curAccount->password,oldpassword)!=0)
			        {
			    	    printf("modified successfully!");
			    	    break;
				    }
			    }
		    }
		    else
		    {
			    printf("modified successfully!\n");
		    }
	    }
	    else
	    {
		    printf("the code is incorrect and cannot be modified!\n");
	    }
	}
}
 
void signIn()//��¼
{
	if(language==1)
	{
		for(int i=0;i<3;i++)
	    {
		    Account a;
		    printf("�������˺�:");
		    scanf("%s",a.username);
		    printf("����������:");
		    scanf("%s",a.password);
		    if(findAccount(a))
		    {
		    	printf("��½�ɹ�!\n");
			    return;
		    }
		    else
		    {
			    printf("��½ʧ��!\n");
		    }
	    }
	}
	else if(language==2)
	{
		for(int i=0;i<3;i++)
	    {
		    Account a;
		    printf("enter your username:");
		    scanf("%s",a.username);
		    printf("enter your code:");
		    scanf("%s",a.password);
		    if(findAccount(a))
		    {
		    	printf("login successful!\n");
			    break;
		    }
		    else
		    {
			    printf("login failed!\n");
		    }
	    }
	}
}

void signUp()//ע��
{
	//����һ����ڴ�ռ䣬�����ַ��ֵ��ָ��newNode(�����ڵ㣩
	Account* newNode=(Account*)malloc(sizeof(Account));
	//��㸳ֵ
	if(language==1)
	{
	    printf("����������:\n");
	    scanf("%s",newNode->name);
	    printf("����������:\n");
	    scanf("%s",newNode->password);
	    printf("�������˺�:\n");
	    scanf("%s",newNode->username);
	    printf("���������֤:\n");
	    scanf("%s",newNode->idCard); 
	    printf("������绰:\n");
	    scanf("%s",newNode->tel);
    }
	else if(language==2)
	{
		printf("enter your name:\n");
	    scanf("%s",newNode->name);
	    printf("enter your code:\n");
	    scanf("%s",newNode->password);
	    printf("enter your account:\n");
	    scanf("%s",newNode->username);
	    printf("enter your idcard:\n");
	    scanf("%s",newNode->idCard); 
	    printf("enter your tel:\n");
	    scanf("%s",newNode->tel);
	}
	newNode->money=0.0f;
	newNode->next=NULL;
	//��ӽ�㵽����
	if(head==NULL)
	{
		head=newNode;
		tail=newNode;
	}
	else
	{
		tail->next=newNode;
		tail=newNode;
	}
	printf("�����ɹ�\n");
} 

//���ݿ��Ų��ҶԷ��˻����ҵ�����1���Ҳ�������0 
int findOtherAccount(char otherUsername[])
{
	Account * curp=head;
	while(curp!=NULL)
	{
		if(strcmp(curp->username,otherUsername)==0)	
		{
			otherAccount = curp; 
			return 1;
		}
		curp=curp->next;
	} 
	return 0;
}

void transfer()
{
	if(language==1)
	{
		printf("������Է��˻���");
	    char otherUsername[100];
	    scanf("%s",otherUsername);
	
	    //�ж��˻��Ϸ���
	    if(findOtherAccount(otherUsername))
	    {
		    printf("������ת�˽�");
		    int money;
		    scanf("%d",&money);
		
		    //�жϽ��ĺϷ���
		    if(curAccount->money>=money)
		    {
			    //ת�ˣ���ǰ�˻������٣��Է��˻�������ࣩ
			    curAccount->money -= money;
			    otherAccount->money += money;
			    printf("ת�˳ɹ�!\n");
		    }
		    else
		    {
			    printf("���㣡\n");
	        }
	    }
    	else
	    {
		    printf("�˻�������\n");
	    }
	}
	else if(language==2)
	{
		printf("enter opposite account��");
	    char otherUsername[100];
	    scanf("%s",otherUsername);
	
	    //�ж��˻��Ϸ���
	    if(findOtherAccount(otherUsername))
	    {
		    printf("enter transfer amount��");
		    int money;
		    scanf("%d",&money);
		
		    //�жϽ��ĺϷ���
		    if(curAccount->money>=money)
		    {
			    //ת�ˣ���ǰ�˻������٣��Է��˻�������ࣩ
			    curAccount->money -= money;
			    otherAccount->money += money;
			    printf("transfer succeeded!\n");
		    }
		    else
		    {
			    printf("sorry,your credit is running low��\n");
	        }
	    }
    	else
	    {
		    printf("account dose not exist\n");
	    }
	}
}

void showMenu()
{
	while(1)
	{
		if(language==1)
		{
			system("cls");
			printf("��¼���밴1\n");
			printf("�������밴2\n");
			printf("�޸����룬�밴3\n");
			printf("ȡ��밴4\n");
			printf("���밴5\n");
			printf("ת�ˣ��밴6\n"); 
			printf("�˳����밴7\n");
		}
		else if(language==2)
		{
			system("cls");
			printf("sign in,press 1\n");
			printf("sign up,press 2\n");
			printf("change password,press 3\n");
			printf("draw money,press 4\n");
			printf("save money,press 5\n");
			printf("transfer accounts,press 6\n");
			printf("sign out,press 7\n");
			system("pause");
		}
		int n;
		scanf("%d",&n);
		if(n==1)
		{
			system("cls");
		 	signIn();
		 	system("pause");
		}
		else if(n==2)
	    {
	    	system("cls");
			signUp();
			system("pause");
		}
		else if(n==3)
		{
			system("cls");
			signIn();
			updataPassword();
			system("pause"); 
		}
		else if(n==4)
		{
			system("cls");
			signIn();
			drawMoney();
			system("pause");
		}
		else if(n==5)
		{
			system("cls");
			signIn();
			saveMoney();
			system("pause");
		}
		else if(n==6)
		{
			system("cls");
			signIn();
			transfer();
			system("pause");
		} 
		else if(n==7)
		{
			system("cls");
		 	return;
		 	system("pause");
		}
		
	}
}
void printLinkedList()
{
	Account* curP=head;
	while(curP!=NULL)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%f\n",curP->name,curP->password,curP->username,curP->idCard,curP->tel,curP->money);
		curP=curP->next;
	}
}

void loadData()
{
	FILE* fp=fopen("D:/atm.txt","r"); 
	if(fp!=NULL)
	{
		while(!feof(fp))
		{
			//�������
			Account *newNode=(Account *)malloc(sizeof(Account));
			
			//����ʼ��
			newNode->next=NULL;
			fscanf(fp,"%s\t%s\t%s\t%s\t%s\t%f\n",newNode->name,newNode->password,newNode->username,newNode->idCard,newNode->tel,&newNode->money);
			
			//��ӽ�㵽���� 
			if(head==NULL)
			{
				head=newNode;
				tail=newNode;
			}
			else
			{
				tail->next=newNode;
				tail=newNode;
			}
		}
		fclose(fp); 
	}
}

void saveData()
{
	FILE* fp=fopen("D:/atm.txt","w");
	if(fp!=NULL)
	{
		Account* curP=head;
	    while(curP!=NULL)
	    {
		    fprintf(fp,"%s\t%s\t%s\t%s\t%s\t%f\n",curP->name,curP->password,curP->username,curP->idCard,curP->tel,curP->money);
		    curP=curP->next;
	    }
	    fclose(fp);
	}
}

int main()
{
	loadData();//�����˻���Ϣ 
	printf("���ķ����밴1\n");
	printf("English Service,press 2\n");
	scanf("%d",&language);
	
	showMenu();
	
	printLinkedList();
	saveData();
	
	return 0;
}