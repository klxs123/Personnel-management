#include <cstdio>
#include <cstdbool>
#include <cstring>
#include <stdlib.h>
#define ture 1
#define false 0

const int MAX_MANAGE = 20;
const char ADMIN_ACCOUNT[] = "admin";
const char ADMIIN_PASSWORD[] = "666666";

typedef struct _manage
{
	char Name[20];
	double balance;
}Manage, *ManagePtr;

typedef struct _Node
{
	int acctNum;
	char password[20];
	Manage data;
	struct _Node* next;
}Node, *NodePtr;

int enterChoice(bool);                   //输出界面用来选择
int Login_Enterchoice(void);
int Login_system(char[][20]);
int deleteRecord(NodePtr *, bool);
int updateData(NodePtr node,char[], bool);
int newRecord(NodePtr *, char[][20], bool);
int Data_synchronization(char[][20], NodePtr);
int Write_array_information(NodePtr ,char[][20]);
int login_accountdata(char manage[][20], char*);
void To_heavy(NodePtr);
void Enquiries_Data(NodePtr);
void Print_updated_information(NodePtr);
void Print_all_Data(Node *, char[], bool);
void Writedata(Node *, char manage[][20]);
NodePtr Get_newdata(void);
NodePtr return_data(Node *);
NodePtr recordIndex(Node *, int);
NodePtr changechoice(NodePtr, bool);
NodePtr Get_ordinary_newdata(NodePtr);
NodePtr Read_Saved_information(NodePtr *);