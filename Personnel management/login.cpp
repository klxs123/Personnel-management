#include "Bank management.h"


int login_read_information(NodePtr pNode, char manage[][20]) //¶ÁÈëÕËºÅÃÜÂë
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
		count++;
	}
	return 0;
}

int login_accountdata(char managedata[][20], char* input_manage_data)
{
	int count_password = 3;
	char login_password[10] = { 0 };
	if (strcmp(input_manage_data, ADMIN_ACCOUNT) == 0)
	{
		while (count_password > 0)
		{
			printf("Please Input Password,surplus %d chances!\n--> ", count_password);
			scanf("%s", login_password);
			if (strcmp(login_password, ADMIIN_PASSWORD) == 0)
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
			if (managedata[amount][0] == 0)
			{
				return 0;
			}
			if (!strcmp(managedata[amount], input_manage_data))
			{
				while (count_password > 0)
				{
					printf("Please Input Password,surplus %d chances!\n--> ", count_password);
					scanf("%s", login_password);
					if (strcmp(login_password, managedata[amount+1]) == 0)
						return amount;
					count_password--;
				}
				if (count_password <= 0)
					return -1;
			}
		}
	}
}

