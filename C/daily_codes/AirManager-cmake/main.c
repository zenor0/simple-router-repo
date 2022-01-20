#include <stdio.h>
#include <conio.h>
#include "fileIO.h"
#include "function.h"


int main(void)
{
	CustomerList CList;
	AirlineList AList;
	InitializeSystem(&AList, &CList);

	//显示菜单
	while (1)
	{
                printf("\n");
	        	printf("\t\t\t   *- - - - - - - - - - - - - - - - - - - - - - - - - -*\n");
				printf("\t\t\t  *|  输入1：编辑航班信息  /Enter  flight information  |*\n");
				printf("\t\t\t  |*  输入2：查询航班信息  /Search flight information  *|\n");
				printf("\t\t\t  *|  输入3：订购    机票  /Order  flight ticket       |*\n");
				printf("\t\t\t  |*  输入4：退订    机票  /return flight ticket       *|\n");
				printf("\t\t\t  *|  输入5：查询订票信息  /Search order  information  |*\n");
				printf("\t\t\t  |*  输入0: 退出    系统  /Exit   the    system       *|\n");
				printf("\t\t\t   *- - - - - - - - - - - - - - - - - - - - - - - - - -*\n");
				printf("\t\t\t   请输入一个数字选择功能/Please enter a number to choose what you need:\n");
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
			printf("\t\t\t 再见");
			ExitSystem(&AList, &CList);
			return 0;
			break;

		default:
			printf("输入错误, 请重新输入");
		}

		getch();
		system("cls");
	}


	return 0;
}
