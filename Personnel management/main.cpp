#define _CRT_SECURE_NO_WARNINGS
#include "Bank management.h"
static bool FLAG = 0;

int main()
{
	NodePtr header = 0;
	char manage[MAX_MANAGE][20] = { 0 };
	login_read_information(manage);   
	Read_Saved_information(&header, manage);        //读入已经添加的账号
	int choice = 0;
	while (1)
	{
		int return_value = Login_system(manage);
		if (return_value == 0)
		{
			return 0;
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
			if (choice == 6 )
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
	char login_password[20] = { 0 };
	int choice = 0;
	int password_count = 1;
	while (int login_choice = Login_Enterchoice())
	{
		printf("Please input your Login account:\n-->");
		scanf("%s", login_account);
		if (int flag = login_accountdata(manage_data, login_account))
		{
			if (!strcmp(login_account, manage_data[0]))
			{
				fputs(
					"\n"
					"	    The current account is an administrator account\n"
					"--------------------------------------------------------------------------------\n",
					stdout);
				FLAG = 1;
			}
			else
			{
				fputs(
					"\n"
					"	    The current account is not administrator account\n"
					"--------------------------------------------------------------------------------\n",
					stdout);
			}
			while (password_count <= 3)
			{
				fputs("Please input your password,", stdout);
				printf("Surplus %d chances!\n-->", 4 - password_count);
				scanf("%s", login_password);
				if (login_passworddata(manage_data[flag], login_password))
				{
					free(login_account);
					login_account = 0;
					if (1 == FLAG)
					{
						return 1;
					}
					return flag - 1;
				}
				else
				{
					fputs("Password input failure! ", stdout);
					if (password_count == 3)
					{
						fputs("Password error 3 times!\n", stdout);
						FLAG = 0;
					}
				}
				password_count++;
			}
		}
		else
		{
			fputs("Account exist!\n", stdout);
			FLAG = 0;
		}

	}
	return 0;
}
