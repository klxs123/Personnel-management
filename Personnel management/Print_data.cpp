#include "Bank management.h"

void Printf_updata(NodePtr findPtr)
{
	if (findPtr)
	{
		fprintf(stdout, "%-s\t\t%-s\t\t%s\t%s\n",
			"AcctNum", "Name", "Password", "Balance");
		printf("%-d\t\t%s\t\t%s\t\t%.2f\t\n",
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
			"		* * * * * * * * * * * * * * * *\n"
			"		* Enter your choice           *\n"
			"		* 1 - add an account          *\n"
			"		* 2 - updata a account        *\n"
			"		* 3 - delete an account       *\n"
			"		* 4 - print accounts          *\n"
			"		* 5 - end program             *\n"
			"		* * * * * * * * * * * * * * * *\n? "
		);
	}
	else
	{
		printf(
			"		* * * * * * * * * * * * * * * *\n"
			"		* Enter your choice           *\n"
			"		* 1 - updata a account        *\n"
			"		* 2 - print accounts          *\n"
			"		* 3 - end program             *\n"
			"		* * * * * * * * * * * * * * * *\n? "
		);
	}
	scanf("%d", &menuChoice);
	return menuChoice;
}