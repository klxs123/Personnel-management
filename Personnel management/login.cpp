#include "Bank management.h"


int Write_array_information(NodePtr pNode, char manage[][20]) //写入账号密码到数组
{
	strcpy(manage[0], ADMIN_ACCOUNT);
	strcpy(manage[1], ADMIIN_PASSWORD);
	NodePtr FindPtr = pNode;
	if (pNode == 0)
	{
		return 0;
	}
	int count = 2;
	while (FindPtr)
	{
		if (FindPtr->acctNum == 0)
			return 0;
		itoa(FindPtr->acctNum, manage[count], 10);
		strcpy(manage[count + 1], FindPtr->password);
		FindPtr = FindPtr->next;
		count+=2;
	}
	return 0;
}

int login_accountdata(char manage[][20], char* input_manage_data)
{
	char login_password[10] = { 0 };
	int count_password = 3;
	int  count_array = 0;
	if (strcmp(input_manage_data, manage[count_array]) == 0)
	{
		count_array = 1;
		while (count_password > 0)
		{
			printf("Please Input Password,surplus %d chances!\n--> ", count_password);
			scanf("%s", login_password);
			if (strcmp(login_password, manage[count_array]) == 0)
				return 1;
			count_password--;
		}
		if (count_password <= 1)
			return -1;
	}
	else
	{
		for (int amount = 2; amount <= MAX_MANAGE; amount += 2)
		{
			if (manage[amount][0] == 0)
			{
				return 0;
			}
			if (!strcmp(manage[amount], input_manage_data))
			{
				while (count_password > 0)
				{
					printf("Please Input Password,surplus %d chances!\n--> ", count_password);
					scanf("%s", login_password);
					if (strcmp(login_password, manage[amount+1]) == 0)
						return amount;
					count_password--;
				}
				if (count_password <= 0)
					return -1;
			}
		}
	}
}

Node* Read_Saved_information(NodePtr* ppNode)
{
	FILE* file = fopen("D:\\github Project\\Personnel management\\Data.dat", "r+");
	int count_seek = 1;
	fseek(file, 0, SEEK_SET);
	NodePtr pNode = (Node*)malloc(sizeof(Node));
	memset(pNode, 0, sizeof(Node));
	int ret = fread(pNode, sizeof(Node), 1, file);
	if (ret == 0)								// 数据为空
	{
		free(pNode);
		pNode = 0;
		return 0;
	}
	else
	{
		*ppNode = pNode;
	}
	NodePtr pCarNode = *ppNode;
	while (feof(file) != EOF)
	{
		NodePtr pNewNode = (Node*)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		pNewNode->next = pCarNode->next;
		pCarNode->next = pNewNode;
		pCarNode = pNewNode;

		fread(pCarNode, sizeof(Node), 1, file);
		if (pCarNode->acctNum == 0)
		{
			return 0;
		}
		fseek(file, count_seek * sizeof(Node), SEEK_SET);
		count_seek++;
	}
	fclose(file);
	void To_heavy(NodePtr);
	return 0;
}