#include "Bank management.h"

void Print_updated_information(NodePtr findPtr)
{
	if (findPtr)
	{
		fprintf(stdout, "%-12s%-12s%-12s%-10s\n",
			"AcctNum", "Name", "Password", "Balance");
		printf("%-12d%12s%12s%10.2f\n",
			findPtr->acctNum, findPtr->data.Name,
			findPtr->password, findPtr->data.balance);
	}
}
int enterChoice(bool flag)
{
	int menuChoice;
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
	scanf("%d", &menuChoice);
	return menuChoice;
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
				"	* * * * * * * * * * * * * * * * * * * * * \n"
				"	*       Select The Data To Updated      * \n"
				"	*---------------------------------------* \n"
				"	*        1 - to change name             * \n"
				"	*        2 - to change password         * \n"
				"	*        3 - to change balance          * \n"
				"	*        0 - to change complete         * \n"
				"	* * * * * * * * * * * * * * * * * * * * *\n--> "
			);
		}
		else
		{
			printf(
				"	* * * * * * * * * * * * * * * * * * * * *\n"
				"	*       Select The Data To Updated      * \n"
				"	*---------------------------------------* \n"
				"	*        1 - to change name             * \n"
				"	*        2 - to change password         * \n"
				"	*        0 - to change complete         * \n"
				"	* * * * * * * * * * * * * * * * * * * * *\n--> "
			);
		}
		scanf("%d", &choice);
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
			if (0 == Flag)
				break;
			fputs("Input change (+) or (-) balance: \n-->", stdout);
			scanf("%lf", &balance);
			findPtr->data.balance += balance;
			break;
		default:
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
			"	   ___________________________________________________\n"
			"	  |                                                   | \n"
		);
		fputs("	  | Please choice login account (1) or exit system(0) |\n", stdout);
		printf(
			"	  |___________________________________________________|\n--> "
		);
		scanf("%d", &choice);
		if (choice == 1 || choice == 0)
			break;
	}
	return choice;
}