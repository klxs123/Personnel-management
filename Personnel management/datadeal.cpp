#include "Bank management.h"

Node* Get_newdata(void)  //获取新账户信息
{
	Node* account = (Node*)malloc(sizeof(Node));
	memset(account, 0, sizeof(Node));
	fputs("Please input acctNum,password,name,banance:\n", stdout);
	scanf("%d%s%s%lf", &account->acctNum, account->password,
		account->data.Name, &account->data.balance);
	return account;
}

void Data_synchronization(char manage[][20], NodePtr CarNode)
{
	int amount;
	for (amount = 0; amount <= MAX_MANAGE; amount++)
	{
		if (manage[amount][0] == 0)
		{
			break;
		}
	}
	_itoa(CarNode->acctNum, manage[amount], 10);
	memcpy(manage[amount + 1], CarNode->password, strlen(CarNode->password));
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

void newRecord(NodePtr *nodeptr, char manage[][20], bool Flag)
{
	Node* Data = Get_newdata();
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
		CarNode = pNewNode->next;
		pNewNode->next = *nodeptr;
		*nodeptr = pNewNode;
		CarNode = pNewNode;
	}
	CarNode->acctNum = Data->acctNum;
	strcpy(CarNode->password, Data->password);
	strcpy(CarNode->data.Name, Data->data.Name);
	if (1 == Flag)
	{
		CarNode->data.balance = Data->data.balance;
	}
	else
	{
		CarNode->data.balance = 0;
	}
	Data_synchronization(manage, CarNode);
}

int deleteRecord(NodePtr *ppNode, bool Flag)
{
	if (0 == Flag)
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

void Print_all_Data(Node* data, char return_value[], bool Flag)
{
	int number = 0;
	if (return_value)
	{
		number = atoi(return_value);
	}
	if (data == 0)
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
		if (1 == Flag)
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

int updateData(NodePtr node, char return_value[], bool Flag)
{
	int account = 0;
	if (return_value)
	{
		account = atoi(return_value);
	}
	double balance = 0;
	NodePtr findPtr = node;
	if (1 == Flag)
	{
		printf("Enter account to update : ");
		scanf("%d", &account);
	}
	if (findPtr = recordIndex(findPtr, account))
	{
		Print_updated_information(findPtr);
		findPtr = changechoice(findPtr, Flag);
		Print_updated_information(findPtr);
		return 0;
	}
	else
	{
		printf("Acount #%d has no information.\n", account);
		return 0;
	}
}

void Enquiries_Data(NodePtr header) 
{
	NodePtr findPtr = header;
	int faccount = 0;
	fputs("Please input want to Enquiries account:\n", stdout);
	scanf("%d", &faccount);
	if (findPtr)
	{
		if (findPtr->acctNum == faccount)
		{
			fprintf(stdout, "%-s\t\t%-s\t\t%s\t%s\n",
				"AcctNum", "Name", "Password", "Balance");
			printf("%-d\t\t%s\t\t%s\t\t%.2f\t\n",
				findPtr->acctNum, findPtr->data.Name,
				findPtr->password, findPtr->data.balance);
			return ;
		}
		findPtr = findPtr->next;
	}
}

Node* Read_Saved_information(NodePtr* ppNode, char manage[][20])
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

void Writedata(Node* header, char manage[][20])
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