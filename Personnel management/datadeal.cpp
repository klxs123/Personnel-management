#include "Bank management.h"

static int INITIAL_ACCOUNT = 1000; 

Node* Get_newdata(void)  //管理员获取新账户信息
{
	Node* account = (Node*)malloc(sizeof(Node));
	memset(account, 0, sizeof(Node));
	fputs("Please input AcctNum,Name,Password,Banance:\n-->", stdout);
	scanf("%d%s%s%lf", &account->acctNum, account->data.Name,
		account->password, &account->data.balance);
	return account;
}

Node* Get_ordinary_newdata(NodePtr pNode) //创建普通账户
{
	Node* account = (Node*)malloc(sizeof(Node));
	memset(account, 0, sizeof(Node));
	while (recordIndex(pNode, INITIAL_ACCOUNT))
	{
		INITIAL_ACCOUNT++;
		recordIndex(pNode, INITIAL_ACCOUNT);
	}
	printf("The current acquiescence account is %d !\n", INITIAL_ACCOUNT);
	fputs("Please input Name and Password:\n-->", stdout);
	scanf("%s%s", account->data.Name, account->password);
	account->acctNum = INITIAL_ACCOUNT;
	account->data.balance = 0;
	fprintf(stdout, "%-12s%-12s%-12s%-10s\n",
		"AcctNum", "Name", "Password", "Balance");
	printf("%-12d%-12s%-12s%-10.2f\n",
		account->acctNum, account->data.Name,
		account->password, account->data.balance);
	INITIAL_ACCOUNT++;
	return account;
}

int Data_synchronization(char manage[][20], NodePtr CarNode)  //信息同步到数组
{
	int amount;
	for (amount = 2; amount <= MAX_MANAGE; amount++)
	{
		if (manage[amount][0] == 0)
		{
			break;
		}
	}
	_itoa(CarNode->acctNum, manage[amount], 10);
	strcpy(manage[amount + 1], CarNode->password);
	return amount;
}

Node* recordIndex(Node* pNode, int account) //判断账户是否存在
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

int newRecord(NodePtr *nodeptr, char manage[][20], bool Flag)
{
	int return_value = 0;
	Node* Data = 0;
	if (1 == Flag)
	{
		Data = Get_newdata();
	}
	else
	{
		Data = Get_ordinary_newdata(*nodeptr);
	}
	NodePtr CarNode = *nodeptr;
	if (*nodeptr == 0)
	{
		//信息为空
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
			return 0;
		}
		Node* pNewNode = (Node*)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		pNewNode->next = CarNode;
		*nodeptr = pNewNode;
		CarNode = pNewNode;
	}
	CarNode->acctNum = Data->acctNum;
	strcpy(CarNode->password, Data->password);
	strcpy(CarNode->data.Name, Data->data.Name);
	CarNode->data.balance = Data->data.balance;
	return_value = Data_synchronization(manage, CarNode);
	return return_value;
}

int deleteRecord(NodePtr *ppNode, bool Flag)
{
	if (0 == Flag)
	{
		fputs("Not enough permissions!\n", stdout);
		return -1;
	}
	int accountNum;
	printf("Enter account number to delete : \n-->");
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
			printf("Delete successful!\n");
			return 0;
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
			printf("Delete successful!\n");
			return 0;
		}
	}
	printf("This account has no information!\n");
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
	fprintf(stdout, "%-12s%-12s%-12s%-10s\n",
		"AcctNum", "Name", "Password", "Balance");
	while (findPtr != 0)
	{
		if (findPtr->acctNum == 0)
		{
				return ;
		}
		if (1 == Flag)
		{
			printf("%-12d%-12s%-12s%-10.2f\n",
				findPtr->acctNum, findPtr->data.Name,
				findPtr->password, findPtr->data.balance);
		}
		else
		{
			if (findPtr->acctNum == number)
			{
				printf("%-12d%-12s%-12s%-8.2f\n",
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

void Enquiries_Data(NodePtr header) // 查询账户
{
	NodePtr findPtr = header;
	int faccount = 0;
	fputs("Please input want to Enquiries account:\n--> ", stdout);
	scanf("%d", &faccount);
	if (findPtr)
	{
		if (findPtr->acctNum == faccount)
		{
			fprintf(stdout, "%-12s%-12s%-12s%-12s\n",
				"AcctNum", "Name", "Password", "Balance");
			printf("%-12d%-12s%-12s%-10.2f\n",
				findPtr->acctNum, findPtr->data.Name,
				findPtr->password, findPtr->data.balance);
			return;
		}
		findPtr = findPtr->next;
	}
	fputs("This account has no information!\n", stdout);
}
