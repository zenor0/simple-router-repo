#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "nodeFunction.h"

int EditAirlineInfo(AirlineList * AList, CustomerList * CList);	//编辑航班信息
int ShowAllAirlineInfo(AirlineList * plist);	//查询航班信息
int BookAFlight(AirlineList * AList, CustomerList * CList);	//订购机票
int CancelAFlight(AirlineList * AList, CustomerList * CList);	//取消机票
void QueryBookInfo(CustomerList * CList);	//查询旅客信息

void DisplayAAirlineItem(AirlineItem item);	//输出一条航线信息
void DisplayACustomeItem(CustomerItem item);	//输出一条客户
