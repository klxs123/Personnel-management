#include "Bank management.h"


int Write_array_information(NodePtr pNode, char manage[][20])	//写入账号密码到数组
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
	return 0;
}

int Creat_node(NodePtr* ppNode, Node Data)
{
	NodePtr CarNode = *ppNode;
	if (*ppNode == 0)
	{
		//信息为空
		*ppNode = (Node*)malloc(sizeof(Node));
		memset(*ppNode, 0, sizeof(Node));
		CarNode = *ppNode;
	}
	else
	{
		Node* pNewNode = (Node*)malloc(sizeof(Node));
		memset(pNewNode, 0, sizeof(Node));
		pNewNode->next = CarNode;
		*ppNode = pNewNode;
		CarNode = pNewNode;
	}
	CarNode->acctNum = Data.acctNum;
	strcpy(CarNode->password, Data.password);
	strcpy(CarNode->data.Name, Data.data.Name);
	CarNode->data.balance = Data.data.balance;
	return 0;
}

NodePtr Read_Saved_information(NodePtr* ppNode)
{
	MYSQL *con = mysql_init(NULL);
	Node Data = { 0 };
	if (mysql_real_connect(con, "127.0.0.1", "root", "123qwe",
		"Bank", 0, NULL, 0) == NULL)
	{
		finish_with_error(con);
	}

	if (con == NULL)
	{
		fprintf(stderr, "mysql_init() failed\n");
		exit(1);
	}

	if (mysql_query(con, "SELECT * FROM Information LIMIT 0,3"))
	{
		finish_with_error(con);
	}

	MYSQL_RES *result = mysql_store_result(con);

	if (result == NULL)
	{
		finish_with_error(con);
	}

	//int num_fields = mysql_num_fields(result); //获取列的个数
	int num_fields = 4;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	while ((row = mysql_fetch_row(result)))
	{
		for (int i = 0; i < num_fields; i++)
		{
			switch (i)
			{
			case 0:
				Data.acctNum = atoi(row[i]);
				break;
			case 1:
				strcpy(Data.data.Name, row[i]);
				break;
			case 2:
				strcpy(Data.password, row[i]);
				break;
			case 3:
				Data.data.balance = atof(row[i]);
				break;
			}
		}
		Creat_node(ppNode, Data);
	}
	mysql_free_result(result);
	mysql_close(con);
	return 0;
}