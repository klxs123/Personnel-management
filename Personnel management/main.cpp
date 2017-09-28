#define _CRT_SECURE_NO_WARNINGS
#include "Bank management.h"
static bool FLAG = 0;

MYSQL *con = 0;

int main()
{
	int choice = 0;
	char manage[MAX_MANAGE][20] = { 0 };
	NodePtr header = 0;
	connect_database();										//连接数据库
	Creat_database();
	Read_Saved_information(&header, con);					//读入所有账号信息
	Write_array_information(header, manage);				//同步信息到字符数组
	while (1)
	{
		int return_value = Login_system(manage);
		if (return_value == -1)								//创建默认账号的账户
		{
			return_value = newRecord(&header, manage, FLAG);
		}
		if (return_value == 0)
		{
			return 0;
		}
		while (choice = EnterChoice(FLAG))
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
						OutputData(header, manage[return_value], FLAG);
						break;
					}
					deleteRecord(&header, FLAG);
					break;
				case 4:
					if (0 == FLAG)
					{
						break;
					}
					Print_all_Data(header, 0, FLAG);
					break;
				case 5:
					Enquiries_Data(header);
					break;
				case 6:
					OutputData(header, manage[return_value], FLAG);
					break;
				case 7:
				{
					FLAG = 0;
				}
					break;
				default:
					break;
			}
			if ((choice == 7) || (choice == 4 && FLAG == 0))
			{
				break;
			}
		}
	}
	mysql_close(con);
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
				"		The current account is an administrator account\n"
				"--------------------------------------------------------------------------------\n",
				stdout);
			FLAG = 1;
			return 1;
		default:
			fputs(
				"\n"
				"		The current account is not administrator account\n"
				"--------------------------------------------------------------------------------\n",
				stdout);
			return flag;
		}
		FLAG = 0;
	}
	free(login_account);
	return 0;
}

void connect_database()
{
	int count = 0;
	char c;
	con = mysql_init(NULL);
	//char* cache = (char*)malloc(50);
	//memset(cache, 0, 50);
	//while (1)
	//{
	//	char locklhost[20] = { 0 };
	//	char name[10] = { 0 };
	//	char password[10] = { 0 };
	//	printf("Input locklhost or ip, accountname:\n--> ");
	//	scanf("%s%s", locklhost, name);
	//	printf("Input password:\n--> ");
	//	while ((c = getch()) != '\r')
	//	{
	//		password[count] = c;
	//		count++;
	//	}
	if (mysql_real_connect(con, "127.0.0.1", "root", "root",
		"Bank", 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
	}
		//	else
		//	{
		//		printf("\n-----------------------------Connect Successful!--------------------------------\n");
		//		break;
		//	}
		//}

}

void deal_database(NodePtr data, int flag, int account)
{
	char *cache = (char*)malloc(256);
	memset(cache, 0, 256);
	switch (flag)
	{
	case 1:
		sprintf(
			cache, "INSERT INTO Information VALUES('%d','%s','%s','%lf')",
			data->acctNum, data->data.Name,
			data->password, data->data.balance);
		break;
	case 2:
		sprintf(
			cache, "delete from Information where Account = '%d'", account);
		break;
	case 3:
		switch (account)
		{
		case 1:
			sprintf(
				cache, "update Information set Name = '%s' where Account = '%d'", data->data.Name, data->acctNum);
			break;
		case 2:
			sprintf(
				cache, "update Information set Password = '%s' where Account = '%d'", data->password, data->acctNum);
			break;
		case 3:
			sprintf(
				cache, "update Information set Balance = '%lf' where Account = %d", data->data.balance, data->acctNum);
			break;
		}
		break;
	default :
		fputs("Input error!\n", stdout);
		break;
	}
	if (mysql_query(con, cache))
	{
		finish_with_error(con);
	}
	free(cache);
}

NodePtr database_record(int account)
{
	NodePtr FindPtr = (NodePtr)malloc(sizeof(NodePtr));
	memset(FindPtr, 0, sizeof(NodePtr));
	char* cache = (char*)malloc(100);
	memset(cache, 0, 100);

	if (mysql_query(con, "select * from information"))
	{
		finish_with_error(con);
	}
	MYSQL_RES *result = mysql_store_result(con);

	if (result == NULL)
	{
		finish_with_error(con);
	}
	MYSQL_ROW row;
	while (row = mysql_fetch_row(result))
	{
		FindPtr->acctNum = atoi(row[0]);
		if (account == FindPtr->acctNum)
		{
			strcpy(FindPtr->data.Name, row[1]);
			strcpy(FindPtr->password, row[2]);
			FindPtr->data.balance = atof(row[3]);
			fputs("This record is exist!\n", stdout);
			return FindPtr;
		}
	}
	free(cache);
	return 0;
}