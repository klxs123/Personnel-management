#define _CRT_SECURE_NO_WARNINGS
#include "Bank management.h"
static bool FLAG = 0;

MYSQL *con;

int main()
{
	NodePtr header = 0;
	char manage[MAX_MANAGE][20] = { 0 };
	//Creat_database();
	connect_database();
	Read_Saved_information(&header, con);					//读入所有账号信息
	Write_array_information(header, manage);			//同步信息到字符数组
	int choice = 0;
	while (1)
	{
		int return_value = Login_system(manage);
		if (return_value == -1)						//创建默认账号的账户
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
						Writedata(header);
						break;
					}
					deleteRecord(&header, FLAG);
					break;
				case 4:
					if (0 == FLAG)
					{
						OutputData(header);
					}
					Print_all_Data(header, 0, FLAG);
					break;
				case 5:
					Enquiries_Data(header);
					break;
				case 6:
					OutputData(header);
					break;
				case 7:
				{
					FLAG = 0;
					Writedata(header);
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

void Writedata(Node* header)
{
	;
}

//void Writedata(Node* header)
//{
//	NodePtr writedataPtr = header;
//	int write_count = 0;
//
//	if (mysql_query(con, "DROP TABLE IF EXISTS Information"))
//	{
//		finish_with_error(con);
//	}
//
//	if (mysql_query(con,
//		"CREATE TABLE Information(Account INT, Name TEXT, Password TEXT, Balance DOUBLE)"))
//	{
//		finish_with_error(con);
//	}
//
//	char *cache = (char*)malloc(100);
//	memset(cache, 0, 100);
//	while (writedataPtr != 0)
//	{
//		sprintf(cache, "INSERT INTO Information VALUES('%d','%s','%s','%lf')",
//			writedataPtr->acctNum, writedataPtr->data.Name,
//			writedataPtr->password, writedataPtr->data.balance);
//		if (mysql_query(con, cache))
//		{
//			finish_with_error(con);
//		}
//		writedataPtr = writedataPtr->next;
//	}
//	free(cache);
//	return;
//}

void creat_new_record(NodePtr data)
{
	char *cache = (char*)malloc(50);
	memset(cache, 0, 50);

	sprintf(
		cache,"INSERT INTO Information VALUES('%d','%s','%s','%lf')",
		data->acctNum, data->data.Name, 
		data->password, data->data.balance);

	if (mysql_query(con, cache))
	{
		finish_with_error(con);
	}
}

void connect_database()
{
	con = mysql_init(NULL);
	if (mysql_real_connect(con, "127.0.0.1", "root", "root",
		"Bank", 0, NULL, 0) == NULL)
	{
		finish_with_error(con);
	}
}