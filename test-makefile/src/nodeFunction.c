#include <stdlib.h>
#include <string.h>
#include "nodeFunction.h"


//局部函数原型
static void CopyToNodeAirline(AirlineItem item, AirlineNode * pnode);
static void CopyToNodeCustomer(CustomerItem item, CustomerNode * pnode);


//初始化链表
void InitializeAirlineList(AirlineList * plist)
{
	* plist = NULL;
}

bool AirlineListIsEmpty(const AirlineList *plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
}


bool AirlineListIsFull(void)
{
	AirlineNode * pt;
	bool full;

	pt = (AirlineNode *) malloc(sizeof(AirlineNode));
	if (pt == NULL)
		full = true;
	else
		full = false;
	free(pt);

	return full;
}

unsigned int AirlineListItemCount(const AirlineList *plist)
{
	unsigned int count = 0;
	AirlineNode * pnode = *plist;

	while (pnode != NULL)
	{
		++count;
		pnode = pnode->next;
	}

	return count;
}


bool AddAirlineItem(AirlineItem item, AirlineList * plist)
{
	AirlineNode * pnew;
	AirlineNode * scan = *plist;

	pnew = (AirlineNode *) malloc(sizeof(AirlineNode));
	if (pnew == NULL)
		return false;

	CopyToNodeAirline(item, pnew);
	pnew->next = NULL;
	if (scan == NULL)
		*plist = pnew;
	else
	{
		while (scan->next != NULL)
			scan = scan->next;
		scan->next = pnew;
	}

	return true;
}

void TraverseAirline (const AirlineList *plist, void (* pfun)(AirlineItem item) )
{
	AirlineNode * pnode = *plist;

	while (pnode != NULL)
	{
		(*pfun)(pnode->item);
		pnode = pnode->next;
	}
}

void EmptyTheList(AirlineList * plist)
{
	AirlineNode * psave;

	while (*plist != NULL)
	{
		psave = (*plist)->next;
		free(*plist);
		*plist = psave;
	}
}

static void CopyToNodeAirline(AirlineItem item, AirlineNode * pnode)
{
	pnode->item = item;
}

void DeleteAirlineItem(AirlineNode * delNode, AirlineList * plist)
{
	AirlineNode *prevNode = *plist;
	if (*plist == delNode)
	{
		*plist = delNode->next;
		free(delNode);
	}
	else
	{
		while (prevNode->next != delNode)
		{
			prevNode = prevNode->next;
		}
		prevNode->next = delNode->next;
		free(delNode);
	}
}

AirlineNode* MatchCorrespondAirlineAnum(char * matchStr, AirlineList * plist)
{
	AirlineNode * output = *plist;
	while (output != NULL)
	{
		if (strcmp(matchStr, output->item.anum) == 0)
		{
			return output;
		}
		output = output->next;
	}
	return NULL;
}



void InitializeCustomerList(CustomerList * plist)
{
	* plist = NULL;
}

bool CustomerListIsEmpty(const CustomerList *plist)
{
	if (*plist == NULL)
		return true;
	else
		return false;
}

bool CustomerListIsFull(void)
{
	CustomerNode * pt;
	bool full;

	pt = (CustomerNode *) malloc(sizeof(CustomerNode));
	if (pt == NULL)
		full = true;
	else
		full = false;
	free(pt);

	return full;
}

unsigned int CustomerListItemCount(const CustomerList *plist)
{
	unsigned int count = 0;
	CustomerNode * pnode = *plist;

	while (pnode != NULL)
	{
		++count;
		pnode = pnode->next;
	}

	return count;
}

bool AddCustomerItem(CustomerItem item, CustomerList * plist)
{
	CustomerNode * pnew;
	CustomerNode * scan = *plist;

	pnew = (CustomerNode *) malloc(sizeof(CustomerNode));
	if (pnew == NULL)
		return false;

	CopyToNodeCustomer(item, pnew);
	pnew->next = NULL;
	if (scan == NULL)
		*plist = pnew;
	else
	{
		while (scan->next != NULL)
			scan = scan->next;
		scan->next = pnew;
	}

	return true;
}


void TraverseCustomer (const CustomerList *plist, void (* pfun)(CustomerItem item) )
{
	CustomerNode * pnode = *plist;

	while (pnode != NULL)
	{
		(*pfun)(pnode->item);
		pnode = pnode->next;
	}
}


void EmptyCustomerList(CustomerList * plist)
{
	CustomerNode * psave;

	while (*plist != NULL)
	{
		psave = (*plist)->next;
		free(*plist);
		*plist = psave;
	}
}

static void CopyToNodeCustomer(CustomerItem item, CustomerNode * pnode)
{
	pnode->item = item;
}

void DeleteCustomerItem(CustomerNode * delNode, CustomerList * plist)
{
	CustomerNode *prevNode = *plist;
	if (*plist == delNode)
	{
		*plist = delNode->next;
		free(delNode);
	}
	else
	{
		while (prevNode->next != delNode)
		{
			prevNode = prevNode->next;
		}
		prevNode->next = delNode->next;
		free(delNode);
	}
}

CustomerNode* MatchCorrespondCustomerName(char *matchStr, CustomerList * plist)//匹配合适的顾客名字
{
	CustomerNode * output = *plist;
	while (output != NULL)
	{
		if (strcmp(matchStr, output->item.cname) == 0)
		{
			return output;
		}
		output = output->next;
	}
	return NULL;
}

bool CheckIfBooked(char *matchName, char *matchAnum, CustomerList * CList)
{
	CustomerNode * temp = *CList;
	while (temp != NULL)
	{
		if (strcmp(matchName, temp->item.cname) == 0 && strcmp(matchAnum, temp->item.anum) == 0)
		{
			return true;
		}

		temp = temp->next;
	}

	return false;
}



int AllocateSeatNum(AirlineNode * ANode, CustomerList * CList)
{
	//使用布尔类型数组存已定座位表

	//初始化座位表数组
	bool isSeatBooked[ANode->item.totalNum];
	memset(isSeatBooked, false, sizeof(isSeatBooked));
	
	//temp是用来遍历Clist的
	CustomerNode * temp = *CList;
	
	//while循环遍历乘客链表
	//若CList为空, 则temp == NULL, 不执行该循环
	while (temp != NULL)
	{
		if (strcmp(ANode->item.anum, temp->item.anum) == 0)	//将待分配航班号和所有乘客的航班号进行匹配
		{
			//将匹配到的座位号标记为true
			isSeatBooked[temp->item.seatnum]=true;
		}
		temp = temp->next;
	}

	//从0开始按顺序遍历已定座位表
	for (int i = 0; i < ANode->item.totalNum; i++)
	{
		if (isSeatBooked[i] == false)	//若碰到第一个为false的标记, 返回分配到的座位号结束该函数
		{
			return i;
		}
	}
	return -1;
}

void DeleteAirlineCustomer(char * matchAnum, CustomerList * CList)
{
	CustomerNode * delNode = *CList;
	while (delNode != NULL)
	{
		if (strcmp(delNode->item.anum, matchAnum) == 0)
		{
			DeleteCustomerItem(delNode, CList);
		}
		delNode = delNode->next;
	}
}
