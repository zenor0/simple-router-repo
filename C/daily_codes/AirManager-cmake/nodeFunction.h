#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h>

#define MAX_AIRLINE 10
#define MAX_CUSTOMER 1000
#define ADMIN_PASSWORD "admin"//管理员密码

typedef struct Airline
{
	char anum[10];//航班号
	char pnum[10];//飞机号
	char to[20];//目的地
	int totalNum;//总票数
	int bookNum;//订票数
} AirlineItem;     //航线信息结构体

typedef struct NodeAirline
{
	AirlineItem item;
	struct NodeAirline* next;
} AirlineNode;

typedef AirlineNode* AirlineList;

typedef struct Customer
{
	char cname[10];  //客户信息
	char anum[10];  //航班号
	int seatnum;  //座位号
} CustomerItem;      //客户信息结构体

typedef struct NodeCustomer
{
	CustomerItem item;
	struct NodeCustomer* next;
} CustomerNode;

typedef CustomerNode* CustomerList;

/* function prototypes */

void InitializeAirlineList(AirlineList * plist);	//初始化链表
bool AirlineListIsEmpty(const AirlineList *plist);	//判断链表是否空
bool AirlineListIsFull(void);	//判断链表是否满
unsigned int AirlineListItemCount(const AirlineList *plist);	//计算链表中的元素个数
bool AddAirlineItem(AirlineItem item, AirlineList * plist);	//向链表中添加元素
void TraverseAirline (const AirlineList *plist, void (* pfun)(AirlineItem item) );	//对链表的每个元素应用函数pfun
void EmptyTheList(AirlineList * plist);	//清空链表
void DeleteAirlineItem(AirlineNode * delNode, AirlineList * plist);	//删除链表中的元素
AirlineNode* MatchCorrespondAirlineAnum(char * matchStr, AirlineList * plist);	//查找与 matchStr 匹配的航班信息



void InitializeCustomerList(CustomerList * plist);	//初始化链表
bool AddCustomerItem(CustomerItem item, CustomerList * plist);	//添加元素到链表中
void EmptyCustomerList(CustomerList * plist);	//清空链表
void DeleteCustomerItem(CustomerNode * delNode, CustomerList * plist);	//删除链表中的元素
CustomerNode* MatchCorrespondCustomerName(char *matchStr, CustomerList * plist);	//查找与 matchStr 匹配的顾客信息
void DeleteAirlineCustomer(char * matchAnum, CustomerList * Clist);	//删除对应航班的顾客
bool CheckIfBooked(char *matchName, char *matchAnum, CustomerList * CList);	//检测顾客列表中是否存在与 matchAnum 与 matchName 匹配的信息
int AllocateSeatNum(AirlineNode * ANode, CustomerList * CList);	//为乘客分配一个座位号(从0开始)

#endif
