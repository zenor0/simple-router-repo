#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "nodeFunction.h"

int EditAirlineInfo(AirlineList * AList, CustomerList * CList);	//�༭������Ϣ
int ShowAllAirlineInfo(AirlineList * plist);	//��ѯ������Ϣ
int BookAFlight(AirlineList * AList, CustomerList * CList);	//������Ʊ
int CancelAFlight(AirlineList * AList, CustomerList * CList);	//ȡ����Ʊ
void QueryBookInfo(CustomerList * CList);	//��ѯ�ÿ���Ϣ

void DisplayAAirlineItem(AirlineItem item);	//���һ��������Ϣ
void DisplayACustomeItem(CustomerItem item);	//���һ���ͻ�
