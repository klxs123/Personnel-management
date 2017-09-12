#include <cstdio>
#include <cstdbool>
#include <cstring>
#include <stdlib.h>
#include <stdbool.h>
#define ture 1
#define false 0

const int MAX_MANAGE = 20;

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

int updateData(NodePtr node,char[]);
int enterChoice(bool);                   //输出界面用来选择
int deleteRecord(NodePtr *);
int login(char[][20]);
int login_accountdata(char manage[][20], char[]);
int login_passworddata(char[], char[]);
int Login_system(char[][20]);
void Datacopy(char[][20], NodePtr);
void Print_Data(Node *, char[]);
void newRecord(NodePtr *, char[][20]);
void Writedata(Node *, char manage[][20]);
void Printf_data(NodePtr);
void initialize(FILE *);
void read_data(Node *);
void Printf_updata(NodePtr);
Node* GetData(void);
Node* readdata(NodePtr *, char[][20]);
Node* return_data(Node *);
Node* recordIndex(Node *, int);
NodePtr changechoice(NodePtr);