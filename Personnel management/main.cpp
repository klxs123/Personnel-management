#define _CRT_SECURE_NO_WARNINGS
#include "Bank management.h"
static bool FLAG = 0;

int main()
{
	NodePtr header = 0;
	char manage[MAX_MANAGE][20] = { 0 };
	login(manage);   
	readdata(&header, manage);        //读入已经添加的账号
	int choice = 0;
	if (int return_value = Login_system(manage))
	{
		while (choice = enterChoice(FLAG))
		{

			switch (choice)
			{
			case 1:
				if (0 == FLAG)
				{
					updateData(header, manage[return_value]);
					break;
				}
				newRecord(&header, manage);
				break;
			case 2:
				if (0 == FLAG)
				{
					Print_Data(header, manage[return_value]);
					break;
				}
				updateData(header, 0);
				break;
			case 3:
				if (0 == FLAG)
				{
					Writedata(header, manage);
					return 0;
				}
				deleteRecord(&header);
				break;
			case 4:
				Print_Data(header, 0);
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
				return flag - 1;
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
	if (1 == FLAG)
	{
		CarNode->data.balance = Data->data.balance;
	}
	else
	{
		CarNode->data.balance = 0;
	}
	Datacopy(manage, CarNode);
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
			if (0 == FLAG)
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
		if (1 == FLAG)
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
	if (0 == FLAG)
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

