#define _CRT_SECURE_NO_WARNINGS
#include "Bank management.h"

int login(char data_manage[][20]) //读入账号密码
{
	FILE *file = fopen("D:\\github Project\\Personnel management\\password.txt", "r+");
	int data_amount = 0;
	while (!feof(file))
	{
		fseek(file, data_amount * 20, SEEK_SET);
		fread(data_manage[data_amount], 20, 1, file);
		data_amount++;
	}
	if (data_manage[0][0] == 0)
	{
		memcpy(data_manage[0], "admin",sizeof("admin"));
		memcpy(data_manage[1], "666666", sizeof("666666"));
	}
	fclose(file);
	return 0;
}

int login_accountdata(char managedata[][20],char input_manage_data[])
{
	for (int amount = 0; amount <= MAX_MANAGE; amount += 2)
	{
		if (managedata[amount][0] == 0)
		{
			return 0;
		}
		if (!memcmp(managedata[amount], input_manage_data, strlen(managedata[amount])))
		{
			return amount + 1;
		}
	}		
}

int login_passworddata(char manage[], char login_password[])
{
	if (!memcmp(manage, login_password, strlen(manage)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Login_system(char manage_data[][20])
{
	char login_account[20] = { 0 };
	char login_password[20] = { 0 };
	int choice = 0;
	while (1)
	{
		printf("Please input your Login account:\n");
		scanf("%s", login_account);
		if (int flag = login_accountdata(manage_data, login_account))
		{
			if (!memcmp(login_account, manage_data[0], strlen(manage_data[1])))
			{
				fputs("The current account is an administrator account!\n", stdout);
				FLAG = 1;
			}
			else
			{
				fputs("The current account is not an administrator account!\n", stdout);
			}
			fputs("Please input your password:\n", stdout);
			scanf("%s", login_password);
			if (login_passworddata(manage_data[flag], login_password))
			{
				if (1 == FLAG)
				{
					return 1;
				}
				return flag-1;
			}
			else
			{
				fputs("Password input failure!\n", stdout);
				FLAG = 0;
			}
		}
		else
		{
			fputs("Account exist!\n", stdout);
			FLAG = 0;
		}

	}
}
Node* GetData(void)
{
	Node* account = (Node*)malloc(sizeof(Node));
	memset(account, 0, sizeof(Node));
	if (FLAG == ture)
	{
		fputs("Please input acctNum,password,name,banance:\n", stdout);
		scanf("%d%s%s%lf", &account->acctNum, account->password,
			account->data.Name, &account->data.balance);
		return account;
	}
	else
	{
		fputs("Please input acctNum,password,name:\n", stdout);
		scanf("%d%s%s", &account->acctNum, account->password,
			account->data.Name);
		account->data.balance = 0;
		return account;
	}
}

void Datacopy(char manage[][20], NodePtr CarNode)
{
	int amount;
	for (amount = 0; amount <= MAX_MANAGE; amount++)
	{
		if (manage[amount][0] == 0)
		{
			break;
		}
	}
	_itoa(CarNode->acctNum, manage[amount],10);
	memcpy(manage[amount + 1], CarNode->password,strlen(CarNode->password));
}

void newRecord(NodePtr *nodeptr,char manage[][20])
{
	Node* Data = GetData();
	NodePtr CarNode = *nodeptr;
	if (*nodeptr == 0)
	{
		//存储区为空
		*nodeptr = (Node*)malloc(sizeof(Node));
		memset(*nodeptr, 0, sizeof(Node));
		CarNode = *nodeptr;
	}
	else
	{
		//账号已被建立
		if (recordIndex(*nodeptr, Data->acctNum))
		{
			printf("Account #%d already contains information.\n",
				Data->acctNum);
			return;
		}
		Node* pNewNode = (Node*)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		CarNode = pNewNode->next ;
		pNewNode->next = *nodeptr;
		*nodeptr = pNewNode;
		CarNode = pNewNode;
	}
	CarNode->acctNum = Data->acctNum;
	strcpy(CarNode->password, Data->password);
	strcpy(CarNode->data.Name, Data->data.Name);
	if (FLAG == 1)
	{
		CarNode->data.balance = Data->data.balance;
	}
	else
	{
		CarNode->data.balance = 0;
	}
	Datacopy(manage, CarNode);
}

void Printf_updata(NodePtr findPtr)
{
	if (findPtr)
	{
		fprintf(stdout, "%-s\t\t%-s\t\t%s\t%s\n",
			"AcctNum", "Name", "Password", "Balance");
		printf("%-d\t\t%s\t\t%s\t\t%.2f\t\n",
			findPtr->acctNum, findPtr->data.Name,
			findPtr->password, findPtr->data.balance);
	}
}

NodePtr changechoice(NodePtr findPtr)
{
	int choice = -1;
	double balance = 0;
	while (choice != 0)
	{
		printf(
			"		* * * * * * * * * * * * * * * * \n"
			"		* Input want charge dataitem: * \n"
			"		* 1 - to change name!         * \n"
			"		* 2 - to change password!     * \n"
			"		* 3 - to change balance!      * \n"
			"		* 0 - to change complete!     * \n"
			"		* * * * * * * * * * * * * * * * \n?"	
		);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			fputs("Input name:\n", stdout);
			scanf("%s", findPtr->data.Name);
			break;
		case 2:
			fputs("Input password:\n", stdout);
			scanf("%s", findPtr->password);
			break;
		case 3:
			if (FLAG == 0)
				break;
			fputs("Input change (+) or (-) balance: ", stdout);
			scanf("%lf", &balance);
			findPtr->data.balance += balance;
			break;
		default:
			break;
		}
	}
	return findPtr;
}

int enterChoice(void)
{
	int menuChoice;
	if (FLAG == ture)
	{
		printf(
			"		* * * * * * * * * * * * * * * *\n"
			"		* Enter your choice           *\n"
			"		* 1 - add an account          *\n"
			"		* 2 - updata a account        *\n"
			"		* 3 - delete an account       *\n"
			"		* 4 - print accounts          *\n"
			"		* 5 - end program             *\n"
			"		* * * * * * * * * * * * * * * *\n? "
		);
	}
	else
	{
		printf(
			"		* * * * * * * * * * * * * * * *\n"
			"		* Enter your choice           *\n"
			"		* 1 - updata a account        *\n"
			"		* 2 - print accounts          *\n"
			"		* 3 - end program             *\n"
			"		* * * * * * * * * * * * * * * *\n? "
		);
	}
	scanf("%d", &menuChoice);
	return menuChoice;
}
void Print_Data(Node* data, char return_value[])
{
	int number = 0;
	if (return_value)
	{
		number = atoi(return_value);
	}
	if (data == 0 )
	{
		printf("No find information!\n");
		return;
	}
	NodePtr findPtr = data;
	fprintf(stdout, "%-s\t\t%-s\t\t%s\t%s\n",
		"AcctNum", "Name", "Password", "Balance");
	while (findPtr != 0)
	{
		if (findPtr->acctNum == 0)
		{
			return;
		}
		if (FLAG == 1)
		{
			printf("%-d\t\t%s\t\t%s\t\t%.2f\n",
				findPtr->acctNum, findPtr->data.Name,
				findPtr->password, findPtr->data.balance);
		}
		else
		{
			if (findPtr->acctNum == number)
			{
				printf("%-d\t\t%s\t\t%s\t\t%.2f\n",
					findPtr->acctNum, findPtr->data.Name,
					findPtr->password, findPtr->data.balance);
				return;
			}
		}
		findPtr = findPtr->next;
	}
}
Node* readdata(NodePtr* ppNode, char manage[][20])
{
	FILE* file = fopen("D:\\github Project\\Personnel management\\account.dat", "r+");
	NodePtr pCarNode = *ppNode;
	int count_seek = 1;
	int amount = 2;
	while (!feof(file))
	{
		if (!(*ppNode))
		{
			*ppNode = (Node*)malloc(sizeof(Node));
			memset(*ppNode, 0, sizeof(Node));
			pCarNode = *ppNode;
		}
		else
		{
			NodePtr pNewNode = (Node*)malloc(sizeof(Node));
			memset(pNewNode, 0, sizeof(Node));
			pNewNode->next = pCarNode->next;
			pCarNode->next = pNewNode;
			pCarNode = pNewNode;
		}
		fread(pCarNode, sizeof(Node), 1, file);
		if (pCarNode->acctNum == 0)
		{
			return 0;
		}
		_itoa(pCarNode->acctNum, manage[amount], 10);
		memcpy(manage[amount + 1], pCarNode->password, strlen(pCarNode->password));
		fseek(file, count_seek * sizeof(Node), SEEK_SET);
		count_seek++;
		amount++;
	}
	fclose(file);
	return 0;
}
int main()
{
	NodePtr header = 0;
	char manage[MAX_MANAGE][20] = { 0 };
	login(manage);            //
	readdata(&header,manage);        //读入已经添加的账号
	int choice = 0;
	if (int return_value = Login_system(manage))
	{
		while (choice = enterChoice())
		{

			switch (choice)
			{
			case 1:
				if (FLAG == 0)
				{
					updateData(header, manage[return_value]);
					break;
				}
				newRecord(&header, manage);
				break;
			case 2:
				if (FLAG == 0)
				{
					Print_Data(header, manage[return_value]);
					break;
				}
				updateData(header,0);
				break;
			case 3:
				if (FLAG == 0)
				{
					Writedata(header, manage);
					return 0;
				}
				deleteRecord(&header);
				break;
			case 4:
				Print_Data(header,0);
				break;
			case 5:
				if (header)
				{
					Writedata(header, manage);
				}
				return 0;
			}

		}
	}
	return 0;
}

Node* recordIndex(Node* pNode, int account)
{
	NodePtr findPtr = pNode;
	while (findPtr)
	{
		if (findPtr->acctNum == account)
		{
			return findPtr;
		}
		findPtr = findPtr->next;
	}
	return 0;
}

int updateData(NodePtr node, char return_value[])
{
	int account = 0;
	if(return_value)
	{
		int account = atoi(return_value);
	}
	double balance = 0;
	NodePtr findPtr = node;
	if (1 == FLAG)
	{
		printf("Enter account to update : ");
		scanf("%d", &account);
	}
	if (findPtr = recordIndex(findPtr, account))
	{
		Printf_updata(findPtr);
		findPtr = changechoice(findPtr);
		Printf_updata(findPtr);
		return 0;
	}
	else
	{
		printf("Acount #%d has no information.\n", account);
		return 0;
	}
}

int deleteRecord(NodePtr *ppNode)
{
	if (FLAG == 0)
	{
		fputs("Not enough permissions!\n", stdout);
		return -1;
	}
	int accountNum;
	printf("Enter account number to delete : ");
	scanf("%d", &accountNum);
	if (*ppNode == 0)
	{
		printf("Delete flase! This data is not exist!\n");
		return -1;
	}
	NodePtr pNode = *ppNode;
	NodePtr preNode = 0;
	while (pNode->next != 0)
	{
		if (pNode->acctNum == accountNum)
		{
			if (preNode == 0)
			{
				*ppNode = (*ppNode)->next;
			}
			else
			{
				preNode->next = pNode->next;
			}
			free(pNode);
			break;
		}
		preNode = pNode;
		pNode = pNode->next;
	}
	if (pNode->next == 0)
	{
		if (pNode->acctNum == accountNum)
		{
			if (preNode != 0)
			{
				preNode->next = 0;
				free(pNode);
				pNode = 0;
			}
			else
			{
				*ppNode = 0;
			}
		}
	}
	printf("Delete successful!\n");
	return 0;
}
void Writedata(Node* header,char manage[][20])
{
	FILE* file = fopen("D:\\github Project\\Personnel management\\account.dat", "r+");
	NodePtr writedataPtr = header;
	int seek_count = 0;
	while (writedataPtr != 0)
	{
		fwrite(writedataPtr, sizeof(Node), 1, file);
		fseek(file, seek_count * sizeof(Node), SEEK_CUR);
		writedataPtr = writedataPtr->next;
		seek_count++;
	}
	fclose(file);
	file = fopen("D:\\github Project\\Personnel management\\password.txt", "w+");
	for (int amount = 0; amount <= MAX_MANAGE; amount++)
	{
		if (manage[amount][0] == 0)
		{
			break;
		}
		fseek(file, amount * 20, SEEK_SET);
		fwrite(manage[amount], 20, 1, file);
	}
	fclose(file);
	file = 0;
}
