#include "function.h"

int EditAirlineInfo(AirlineList * AList, CustomerList * CList)
{
	//使用编辑航线功能前需要验证管理员密码
	//验证密码
	system("cls");
	printf("\t请输入管理员密码: ");
	char password[10];
	scanf("%s", password);
	if (strcmp(password, ADMIN_PASSWORD) != 0)
	{
		printf("\n\t密码错误!返回上级菜单...\n");
		Sleep(1000);	
		return -1;
	}
	else
	{
		printf("\n\t认证成功!\n");
	}
	Sleep(500);	//延迟半秒显示提示信息
	//二级菜单-选择编辑功能

	system("cls");
	printf("\t\t\t*********************编辑航线*************************\n");
	printf("\t\t\t******************************************************\n");
	printf("\t\t\t*                修改航班信息--请按1                 *\n");
	printf("\t\t\t*                增加航班信息--请按2                 *\n");
	printf("\t\t\t*                删除航班信息--请按3                 *\n");
	printf("\t\t\t******************************************************\n");
	printf("\t\t\t 请选择服务(务必输入0~3): ");
	int op;
	scanf("%d", &op);

	if (op == 1)
	{
		ShowAllAirlineInfo(AList);
		printf("\t请输入你要修改的航班号(输入'q'退出): ");

		char anumChange[10];
		AirlineNode * opObject;

		while (1)
		{
			scanf("%s", anumChange);
			if (strcmp(anumChange, "q") == 0)
			{
				printf("退出中...\n");
				return 1;
				break;
			}
			if ((opObject = MatchCorrespondAirlineAnum(anumChange, AList)) != NULL)
			{
				printf("\t匹配成功\n");
				printf("\t\t请输入修改后的航班号: ");
				scanf("%s", opObject->item.anum);
				printf("\t\t请输入修改后的飞机号: ");
				scanf("%s", opObject->item.pnum);
				printf("\t\t请输入修改后的目的地: ");
				scanf("%s", opObject->item.to);
				printf("\t\t请输入修改后的总票数: ");
				scanf("%d", &opObject->item.totalNum);
				printf("\t\t请输入修改后的已订票数: ");
				scanf("%d", &opObject->item.bookNum);

				printf("修改成功\n");
				break;
			}
			printf("没有找到匹配的航班信息, 请重新输入正确的航班号: ");
		}
	}
	else if (op == 2)
	{
		if (AirlineListItemCount(AList) + 1 > MAX_AIRLINE)
		{
			printf("由于已达到最多航班限制, 无法再添加更多的航班信息");
			return -1;
		}
		if (AirlineListIsFull())
		{
			printf("系统内存满, 无法添加");
			return -2;
		}

		AirlineItem inputItem;
		printf("\t\t请输入航班号: ");
		scanf("%s", inputItem.anum);
		printf("\t\t请输入飞机号: ");
		scanf("%s", inputItem.pnum);
		printf("\t\t请输入目的地: ");
		scanf("%s", inputItem.to);
		printf("\t\t请输入总票数: ");
		scanf("%d", &inputItem.totalNum);
		printf("\t\t请输入已订票数: ");
		scanf("%d", &inputItem.bookNum);


		if (AddAirlineItem(inputItem, AList))
		{
			printf("添加成功!");
		}
		else
		{
			printf("发生错误, 内存分配失败");
			return -1;
		}
	}
	else if (op == 3)
	{
		ShowAllAirlineInfo(AList);
		printf("请输入你想要删除的航班号(输入'q'退出): ");

		char anumDel[10];
		AirlineNode * opObject;

		while (1)
		{
			scanf("%s", anumDel);
			if (strcmp(anumDel, "q") == 0)
			{
				printf("quit...\n");
				break;
			}

			if ((opObject = MatchCorrespondAirlineAnum(anumDel, AList)) != NULL)
			{
				DeleteAirlineItem(opObject, AList);
				DeleteAirlineCustomer(anumDel, CList);
				printf("删除成功!\n");
				break;
			}
			printf("没有找到匹配的航班信息, 请重新输入正确的航班号: ");
		}
	}
	return 0;
}
int ShowAllAirlineInfo(AirlineList * AList)
{
	system("cls");
	printf("\n为你列出当前所有航班信息: \n");
	printf("%-10s%-10s%-10s%-8s%-8s\n", "航班号", "飞机号","目的地","订票数","余票数");

	TraverseAirline(AList, *DisplayAAirlineItem);
	printf("请按任意键返回上级菜单...");
	getch();
	return 0;
}
int BookAFlight(AirlineList * AList, CustomerList * CList)
{
	system("cls");
	CustomerItem inputInfo;
	printf("请输入你的名字: ");
	scanf("%s", inputInfo.cname);

	ShowAllAirlineInfo(AList);
	printf("请输入你想要订购的航班号(输入'q'退出): ");


	while (1)
	{
		scanf("%s", inputInfo.anum);

		//检测是否直接退出
		if (strcmp(inputInfo.anum, "q") == 0)
		{
			printf("quit...\n");
			return 1;
			break;
		}

		//检测航班是否存在.已满.重复订购
		AirlineNode * matchNode = MatchCorrespondAirlineAnum(inputInfo.anum, AList);
		if (matchNode != NULL)
		{
			if (matchNode->item.totalNum - matchNode->item.bookNum <= 0)
			{
				printf("当前航班已满, 请选择其他航班\n");
			}
			else if (CheckIfBooked(inputInfo.cname, inputInfo.anum, CList))
			{
				printf("重复订购, 请选择其他航班\n");
			}
			else
			{
				//allocate seat
				inputInfo.seatnum = AllocateSeatNum(matchNode, CList);
				//write
				matchNode->item.bookNum++;
				AddCustomerItem(inputInfo, CList);

				printf("订购成功!\n");
				return 0;
				break;
			}

		}
		printf("错误, 请重新输入: ");
	}


}
int CancelAFlight(AirlineList * AList, CustomerList * CList)
{
	system("cls");
	printf("请输入你的名字: ");
	char inputName[10];
	scanf("%s", inputName);


	CustomerNode * opNode = MatchCorrespondCustomerName(inputName, CList);


	if (opNode != NULL)
	{

		AirlineNode * tempNode = MatchCorrespondAirlineAnum(opNode->item.anum, AList);
		
		if (tempNode == NULL)
		{
			printf("No match AirlineNumber!");
			return -1;
		}
		
		printf("Node address: %p", tempNode);
		tempNode->item.bookNum--;
		DeleteCustomerItem(opNode, CList);
		printf("取消成功! ");
	}
	else
	{
		printf("未找到你的信息");
		return -1;
	}
	return 0;
}

void QueryBookInfo(CustomerList * CList)
{
	system("cls");
	printf("请输入你的名字: ");
	char inputName[10];
	scanf("%s", inputName);

	printf("为您找到: ");

	bool isOutput = false;
	bool isFirstOutput = true;
	CustomerNode * tempNode = MatchCorrespondCustomerName(inputName, CList);
	while (tempNode != NULL)
	{
		if (isFirstOutput)
		{
			printf("\n%-10s%-10s%-10s\n", "客户姓名", "航班号", "座位号");
			isFirstOutput = false;
		}
		DisplayACustomeItem(tempNode->item);

		tempNode = tempNode->next;
		tempNode = MatchCorrespondCustomerName(inputName, &tempNode);

		isOutput = true;
	}

	if (isOutput == false)
	{
		printf("未找到任何匹配信息");
	}
}


void DisplayAAirlineItem(AirlineItem item)
{
	printf("%-10s%-10s%-10s%-8d%-8d\n", item.anum, item.pnum, item.to
		, item.bookNum, (item.totalNum - item.bookNum));
}

void DisplayACustomeItem(CustomerItem item)
{
	printf("%-10s%-10s%-10d\n", item.cname, item.anum, item.seatnum);
}
