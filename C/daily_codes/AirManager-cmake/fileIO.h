#include <stdio.h>
#include <stdlib.h>
#include "nodeFunction.h"

int InitializeSystem(AirlineList * AList, CustomerList * CList);	//ϵͳ��ʼ��

int ReadAirlineDataFileToMemory(AirlineList * plist);	//��airline.dat�ļ���ȡ��Ϣ�����ڴ�
int ReadCustomerDataFileToMemory(CustomerList * plist);	//��customer.dat�ļ���ȡ��Ϣ�����ڴ�

int ExitSystem(AirlineList * AList, CustomerList * CList);	//�˳� & ������Ϣ


