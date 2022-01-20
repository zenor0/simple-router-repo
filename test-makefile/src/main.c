#include <stdio.h>
#include <conio.h>
#include "fileIO.h"
#include "function.h"


int main(void)
{
	CustomerList CList;
	AirlineList AList;
	InitializeSystem(&AList, &CList);
	
	//��ʾ�˵�
	while (1)
	{
                // printf("\n");
	        	// printf("\t\t\t   *- - - - - - - - - - - - - - - - - - - - - - - - - -*\n");
				// printf("\t\t\t  *|  ����1���༭������Ϣ  /Enter  flight information  |*\n");
				// printf("\t\t\t  |*  ����2����ѯ������Ϣ  /Search flight information  *|\n");
				// printf("\t\t\t  *|  ����3������    ��Ʊ  /Order  flight ticket       |*\n");
				// printf("\t\t\t  |*  ����4���˶�    ��Ʊ  /return flight ticket       *|\n");
				// printf("\t\t\t  *|  ����5����ѯ��Ʊ��Ϣ  /Search order  information  |*\n");
				// printf("\t\t\t  |*  ����0: �˳�    ϵͳ  /Exit   the    system       *|\n");
				// printf("\t\t\t   *- - - - - - - - - - - - - - - - - - - - - - - - - -*\n");
				// printf("\t\t\t   ������һ������ѡ����/Please enter a number to choose what you need:\n");
		int choice = getch();

		switch (choice)
		{
		case '1':
			EditAirlineInfo(&AList, &CList);
			break;
		case '2':
			ShowAllAirlineInfo(&AList);
			break;
		case'3':
			BookAFlight(&AList, &CList);
			break;
		case '4':
			CancelAFlight(&AList, &CList);
			break;
		case '5':
			QueryBookInfo(&CList);
			break;
		case '0':
			system("cls");
			printf("\t\t\t �ټ�");
			ExitSystem(&AList, &CList);
			return 0;
			break;

		default:
			printf("�������, ����������");
		}

		getch();
		system("cls");
	}


	return 0;
}
