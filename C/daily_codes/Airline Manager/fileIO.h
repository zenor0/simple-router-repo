#include <stdio.h>
#include <stdlib.h>
#include "nodeFunction.h"

int InitializeSystem(AirlineList * AList, CustomerList * CList);	//系统初始化

int ReadAirlineDataFileToMemory(AirlineList * plist);	//从airline.dat文件读取信息存入内存
int ReadCustomerDataFileToMemory(CustomerList * plist);	//从customer.dat文件读取信息存入内存

int ExitSystem(AirlineList * AList, CustomerList * CList);	//退出 & 保存信息


