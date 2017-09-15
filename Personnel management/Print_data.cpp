#include "Bank management.h"

void Print_updated_information(NodePtr findPtr)
{
	if (findPtr)
	{
		fprintf(stdout, "%-12s%-12s%-12s%-10s\n",
			"AcctNum", "Name", "Password", "Balance");
		printf("%-12d%-12s%-12s%-10.2f\n",
			findPtr->acctNum, findPtr->data.Name,
			findPtr->password, findPtr->data.balance);
	}
}
int enterChoice(bool flag)
{
	int menuChoice;
	while (1)
	{
		if (1 == flag)
		{
			printf(
				"		* * * * * * * * * * * * * * * * * * * * * \n"
				"		*           Enter Your Choice           * \n"
				"		*---------------------------------------* \n"
				"		*         1 - add an account            * \n"
				"		*         2 - updata a account          * \n"
				"		*         3 - delete an account         * \n"
				"		*         4 - print all accounts        * \n"
				"		*         5 - seek Specify the account  * \n"
				"		*         6 - end program and save      * \n"
				"		* * * * * * * * * * * * * * * * * * * * *\n--> "
			);
		}
		else
		{
			printf(
				"		* * * * * * * * * * * * * * * * * * * * *\n"
				"		*           Enter your choice           *\n"
				"		*---------------------------------------*\n"
				"		*         1 - updata a account          *\n"
				"		*         2 - print accounts            *\n"
				"		*         3 - end program               *\n"
				"		* * * * * * * * * * * * * * * * * * * * *\n--> "
			);
		}
		if (scanf("%d", &menuChoice) == 1)
		{
			if (menuChoice <= 6 && menuChoice >= 1)
			return menuChoice;
		}
		getchar();
	}
}

NodePtr changechoice(NodePtr findPtr, bool Flag)
{
	int choice = -1;
	double balance = 0;
	while (choice != 0)
	{
		if (1 == Flag)
		{
			printf(
				"		* * * * * * * * * * * * * * * * * * * * * \n"
				"		*       Select The Data To Updated      * \n"
				"		*---------------------------------------* \n"
				"		*        1 - to change name             * \n"
				"		*        2 - to change password         * \n"
				"		*        3 - to change balance          * \n"
				"		*        0 - to change complete         * \n"
				"		* * * * * * * * * * * * * * * * * * * * *\n--> "
			);
		}
		else
		{
			printf(
				"		* * * * * * * * * * * * * * * * * * * * *\n"
				"		*       Select The Data To Updated      * \n"
				"		*---------------------------------------* \n"
				"		*        1 - to change name             * \n"
				"		*        2 - to change password         * \n"
				"		*        0 - to change complete         * \n"
				"		* * * * * * * * * * * * * * * * * * * * *\n--> "
			);
		}
		if (scanf("%d", &choice) == 1)
		{
			if (choice <= 3 && choice >= 1)
			;
		}
		else
		{
			getchar();
			break;
		}
		double Balance = 0;// 判断余额取出之后是否为负
		switch (choice)
		{
		case 1:
			fputs("Input name:\n-->", stdout);
			scanf("%s", findPtr->data.Name);
			break;
		case 2:
			fputs("Input password:\n-->", stdout);
			scanf("%s", findPtr->password);
			break;
		case 3:
			fputs("Input change (+) or (-) balance: \n-->", stdout);
			scanf("%lf", &balance);
			Balance = findPtr->data.balance+balance;
			if (Balance < 0)
			{
				fputs("Lack of balance!\n",stdout);
				break;
			}
			findPtr->data.balance += balance;
			break;
		default:
			fputs("Input Error!\n", stdout);
			break;
		}
	}
	return findPtr;
}

int Login_Enterchoice(void)
{
	int choice = 0;
	while (1)
	{
		printf(
			"	     ___________________________________________________\n"
			"	    |                                                   | \n"
		);
		fputs("	    |                 Please Choice                     |\n", stdout);
		fputs("	    |---------------------------------------------------|\n", stdout);
		fputs("	    | 1  ************   Login account                   |\n", stdout);
		fputs("	    | 2  ************   Creat Ordinary account          |\n", stdout);
		fputs("	    | 3  ************   Exit system                     |\n", stdout);
		printf(
			"	    |___________________________________________________|\n--> "
		);
		if (scanf("%d", &choice) == 1)
		{
			if(choice <= 3 && choice >= 1)
			return choice;
		}
		getchar();
	}
}