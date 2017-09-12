#include "Bank management.h"

Node* GetData(void)
{
	Node* account = (Node*)malloc(sizeof(Node));
	memset(account, 0, sizeof(Node));
	fputs("Please input acctNum,password,name,banance:\n", stdout);
	scanf("%d%s%s%lf", &account->acctNum, account->password,
		account->data.Name, &account->data.balance);
	return account;
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