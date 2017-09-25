#include <cstdio>
#include <cstdbool>
#include <cstring>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>
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

int EnterChoice(bool);                   //输出界面用来选择
int Login_Enterchoice(void);
int Login_system(char[][20]);
int deleteRecord(NodePtr *, bool);
int updateData(NodePtr node,char[], bool);
int newRecord(NodePtr *, char[][20], bool);
int Creat_node(NodePtr* ppNode, Node Data);
int Data_synchronization(char[][20], NodePtr);
int Write_array_information(NodePtr ,char[][20]);
int login_accountdata(char manage[][20], char*);
void Creat_database();
void connect_database();
void OutputData(NodePtr );
void Enquiries_Data(NodePtr);
void deal_database(NodePtr, int, int);
void finish_with_error(MYSQL *con);
void Print_updated_information(NodePtr);
void Print_all_Data(Node *, char[], bool);
NodePtr Get_newdata(NodePtr );
NodePtr return_data(Node *);
NodePtr recordIndex(Node *, int);
NodePtr Read_Saved_information(NodePtr *, MYSQL *);
NodePtr changechoice(NodePtr, bool, int);
NodePtr Get_ordinary_newdata(NodePtr);
