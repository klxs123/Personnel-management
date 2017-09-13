#include "Bank management.h"


int login_read_information(char data_manage[][20]) //∂¡»Î’À∫≈√‹¬Î
{
	FILE *file = fopen("D:\\github Project\\Personnel management\\password.txt", "r+");
	int data_amount = 0;
	while (!feof(file))
	{
		fseek(file, data_amount * 20, SEEK_SET);
		fread(data_manage[data_amount], 20, 1, file);
		data_amount++;
	}
	if (data_manage[0][0] == 0)
	{
		memcpy(data_manage[0], "admin", sizeof("admin"));
		memcpy(data_manage[1], "666666", sizeof("666666"));
	}
	fclose(file);
	return 0;
}

int login_accountdata(char managedata[][20], char* input_manage_data)
{
	for (int amount = 0; amount <= MAX_MANAGE; amount += 2)
	{
		if (managedata[amount][0] == 0)
		{
			return 0;
		}
		if (!strcmp(managedata[amount], input_manage_data))
		{
			return amount + 1;
		}
	}
}

int login_passworddata(char manage[], char login_password[])
{
	if (!strcmp(manage, login_password))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
