#include "function.h"

int EditAirlineInfo(AirlineList * AList, CustomerList * CList)
{
	//ʹ�ñ༭���߹���ǰ��Ҫ��֤����Ա����
	//��֤����
	system("cls");
	printf("\t���������Ա����: ");
	char password[10];
	scanf("%s", password);
	if (strcmp(password, ADMIN_PASSWORD) != 0)
	{
		printf("\n\t�������!�����ϼ��˵�...\n");
		Sleep(1000);	
		return -1;
	}
	else
	{
		printf("\n\t��֤�ɹ�!\n");
	}
	Sleep(500);	//�ӳٰ�����ʾ��ʾ��Ϣ
	//�����˵�-ѡ��༭����

	system("cls");
	printf("\t\t\t*********************�༭����*************************\n");
	printf("\t\t\t******************************************************\n");
	printf("\t\t\t*                �޸ĺ�����Ϣ--�밴1                 *\n");
	printf("\t\t\t*                ���Ӻ�����Ϣ--�밴2                 *\n");
	printf("\t\t\t*                ɾ��������Ϣ--�밴3                 *\n");
	printf("\t\t\t******************************************************\n");
	printf("\t\t\t ��ѡ�����(�������0~3): ");
	int op;
	scanf("%d", &op);

	if (op == 1)
	{
		ShowAllAirlineInfo(AList);
		printf("\t��������Ҫ�޸ĵĺ����(����'q'�˳�): ");

		char anumChange[10];
		AirlineNode * opObject;

		while (1)
		{
			scanf("%s", anumChange);
			if (strcmp(anumChange, "q") == 0)
			{
				printf("�˳���...\n");
				return 1;
				break;
			}
			if ((opObject = MatchCorrespondAirlineAnum(anumChange, AList)) != NULL)
			{
				printf("\tƥ��ɹ�\n");
				printf("\t\t�������޸ĺ�ĺ����: ");
				scanf("%s", opObject->item.anum);
				printf("\t\t�������޸ĺ�ķɻ���: ");
				scanf("%s", opObject->item.pnum);
				printf("\t\t�������޸ĺ��Ŀ�ĵ�: ");
				scanf("%s", opObject->item.to);
				printf("\t\t�������޸ĺ����Ʊ��: ");
				scanf("%d", &opObject->item.totalNum);
				printf("\t\t�������޸ĺ���Ѷ�Ʊ��: ");
				scanf("%d", &opObject->item.bookNum);

				printf("�޸ĳɹ�\n");
				break;
			}
			printf("û���ҵ�ƥ��ĺ�����Ϣ, ������������ȷ�ĺ����: ");
		}
	}
	else if (op == 2)
	{
		if (AirlineListItemCount(AList) + 1 > MAX_AIRLINE)
		{
			printf("�����Ѵﵽ��ຽ������, �޷�����Ӹ���ĺ�����Ϣ");
			return -1;
		}
		if (AirlineListIsFull())
		{
			printf("ϵͳ�ڴ���, �޷����");
			return -2;
		}

		AirlineItem inputItem;
		printf("\t\t�����뺽���: ");
		scanf("%s", inputItem.anum);
		printf("\t\t������ɻ���: ");
		scanf("%s", inputItem.pnum);
		printf("\t\t������Ŀ�ĵ�: ");
		scanf("%s", inputItem.to);
		printf("\t\t��������Ʊ��: ");
		scanf("%d", &inputItem.totalNum);
		printf("\t\t�������Ѷ�Ʊ��: ");
		scanf("%d", &inputItem.bookNum);


		if (AddAirlineItem(inputItem, AList))
		{
			printf("��ӳɹ�!");
		}
		else
		{
			printf("��������, �ڴ����ʧ��");
			return -1;
		}
	}
	else if (op == 3)
	{
		ShowAllAirlineInfo(AList);
		printf("����������Ҫɾ���ĺ����(����'q'�˳�): ");

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
				printf("ɾ���ɹ�!\n");
				break;
			}
			printf("û���ҵ�ƥ��ĺ�����Ϣ, ������������ȷ�ĺ����: ");
		}
	}
	return 0;
}
int ShowAllAirlineInfo(AirlineList * AList)
{
	system("cls");
	printf("\nΪ���г���ǰ���к�����Ϣ: \n");
	printf("%-10s%-10s%-10s%-8s%-8s\n", "�����", "�ɻ���","Ŀ�ĵ�","��Ʊ��","��Ʊ��");

	TraverseAirline(AList, *DisplayAAirlineItem);
	printf("�밴����������ϼ��˵�...");
	getch();
	return 0;
}
int BookAFlight(AirlineList * AList, CustomerList * CList)
{
	system("cls");
	CustomerItem inputInfo;
	printf("�������������: ");
	scanf("%s", inputInfo.cname);

	ShowAllAirlineInfo(AList);
	printf("����������Ҫ�����ĺ����(����'q'�˳�): ");


	while (1)
	{
		scanf("%s", inputInfo.anum);

		//����Ƿ�ֱ���˳�
		if (strcmp(inputInfo.anum, "q") == 0)
		{
			printf("quit...\n");
			return 1;
			break;
		}

		//��⺽���Ƿ����.����.�ظ�����
		AirlineNode * matchNode = MatchCorrespondAirlineAnum(inputInfo.anum, AList);
		if (matchNode != NULL)
		{
			if (matchNode->item.totalNum - matchNode->item.bookNum <= 0)
			{
				printf("��ǰ��������, ��ѡ����������\n");
			}
			else if (CheckIfBooked(inputInfo.cname, inputInfo.anum, CList))
			{
				printf("�ظ�����, ��ѡ����������\n");
			}
			else
			{
				//allocate seat
				inputInfo.seatnum = AllocateSeatNum(matchNode, CList);
				//write
				matchNode->item.bookNum++;
				AddCustomerItem(inputInfo, CList);

				printf("�����ɹ�!\n");
				return 0;
				break;
			}

		}
		printf("����, ����������: ");
	}


}
int CancelAFlight(AirlineList * AList, CustomerList * CList)
{
	system("cls");
	printf("�������������: ");
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
		printf("ȡ���ɹ�! ");
	}
	else
	{
		printf("δ�ҵ������Ϣ");
		return -1;
	}
	return 0;
}

void QueryBookInfo(CustomerList * CList)
{
	system("cls");
	printf("�������������: ");
	char inputName[10];
	scanf("%s", inputName);

	printf("Ϊ���ҵ�: ");

	bool isOutput = false;
	bool isFirstOutput = true;
	CustomerNode * tempNode = MatchCorrespondCustomerName(inputName, CList);
	while (tempNode != NULL)
	{
		if (isFirstOutput)
		{
			printf("\n%-10s%-10s%-10s\n", "�ͻ�����", "�����", "��λ��");
			isFirstOutput = false;
		}
		DisplayACustomeItem(tempNode->item);

		tempNode = tempNode->next;
		tempNode = MatchCorrespondCustomerName(inputName, &tempNode);

		isOutput = true;
	}

	if (isOutput == false)
	{
		printf("δ�ҵ��κ�ƥ����Ϣ");
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
