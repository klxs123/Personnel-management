#define _CRT_SECURE_NO_WARNINGS
#include "Bank management.h"
static bool FLAG = 0;

int main()
{
	NodePtr header = 0;
	char manage[MAX_MANAGE][20] = { 0 };
	Read_Saved_information(&header, manage); 
	login_read_information(header, manage);
	int choice = 0;
	while (1)
	{
		int return_value = Login_system(manage);
		if (return_value == -1) //创建普通账户
		{
			return_value = newRecord(&header, manage, FLAG);
		}
		if (return_value == 0) // 退出账户
		{
			break;
		}
		while (choice = enterChoice(FLAG))
		{

			switch (choice)
			{
			case 1:
				if (0 == FLAG)
				{
					updateData(header, manage[return_value], FLAG);
					break;
				}
				newRecord(&header, manage, FLAG);
				break;
			case 2:
				if (0 == FLAG)
				{
					Print_all_Data(header, manage[return_value], FLAG);
					break;
				}
				updateData(header, 0, FLAG);
				break;
			case 3:
				if (0 == FLAG)
				{
					Writedata(header, manage);
					break;
				}
				deleteRecord(&header, FLAG);
				break;
			case 4:
				if (0 == FLAG)
					break;
				Print_all_Data(header, 0, FLAG);
				break;
			case 5:
				if (0 == FLAG)
					break;
				Enquiries_Data(header);
				break;
			case 6:
				if (header)
				{
					Writedata(header, manage);
				}
				break;
			default:
				break;
			}
			if (choice == 6)
				break;
			if (choice == 3 && FLAG == 0)
				break;
		}
	}
	return 0;
}

int Login_system(char manage_data[][20])
{
	char* login_account = (char*)malloc(20);
	memset(login_account, 0, 20);
	int choice = 0;
	int password_count = 1;
	while (int login_choice = Login_Enterchoice())
	{
		if (login_choice == 3)  //退出系统
		{
			return 0;
		}
		if (login_choice == 2)  //创建普通用户
		{
			return -1;
		}
		printf("Please input your Login account:\n--> ");
		scanf("%s", login_account);
		int flag = 0;
		switch (flag = login_accountdata(manage_data, login_account))
		{
		case -1:
			fputs("		Password error 3 times!\n", stdout);
			break;
		case 0:
			fputs("The account has no information!\n", stdout);
			break;
		case  1:
			fputs(
				"\n"
				"	    The current account is an administrator account\n"
				"--------------------------------------------------------------------------------\n",
				stdout);
			FLAG = 1;
			return 1;
		default:
			fputs(
				"\n"
				"	    The current account is not administrator account\n"
				"--------------------------------------------------------------------------------\n",
				stdout);
			return flag;
		}
		FLAG = 0;
	}
}


Node* Read_Saved_information(NodePtr* ppNode, char manage[][20])
{
	FILE* file = fopen("D:\\github Project\\Personnel management\\Data.dat", "r+");
	int count_seek = 1;
	int amount = 1;
	fseek(file, 0, SEEK_SET);
	NodePtr pNode = (Node*)malloc(sizeof(Node));
	memset(pNode, 0, sizeof(Node));
	int ret = fread(pNode, sizeof(Node), 1, file);
	if (ret == 0)
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
		_itoa(pCarNode->acctNum, manage[amount], 10);
		strcpy(manage[amount + 1], pCarNode->password);
		fseek(file, count_seek * sizeof(Node), SEEK_SET);
		count_seek++;
		amount++;
	}
	fclose(file);
	return 0;
}

void Writedata(Node* header, char manage[][20])
{
	FILE* file = fopen("D:\\github Project\\Personnel management\\Data.dat", "w+");
	NodePtr writedataPtr = header;
	int seek_count = 0;
	while (writedataPtr != 0)
	{
		fseek(file, 0, SEEK_END);
		fwrite(writedataPtr, sizeof(Node), 1, file);
		writedataPtr = writedataPtr->next;
		seek_count++;
	}
	fclose(file);
	file = 0;
	FLAG = 0;
}