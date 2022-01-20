#include <stdio.h>
#include <stdlib.h>
#include "nodeFunction.h"

int ReadAirlineDataFileToMemory(AirlineList * plist)
{
    //��ȡairline.dat�ļ�, ��������˳�
    FILE* fp = fopen("airline.dat", "r");
    if (fp == NULL)
    {
        printf("Read airline.dat ERROR, exiting...");
        return -1;
    }

    AirlineNode *pnew;	//pointer to a node
    AirlineNode * scan = *plist;

    for (int i = 0; i < MAX_AIRLINE; i++)
    {
        //��ʼ��pnew��Ϊһ����ʱ�Ľṹ�����, ���ڴ洢��ʱ�����һ����Ϣ
        pnew = (AirlineNode *) malloc(sizeof(AirlineNode));


        //����airline.dat ��һ����Ϣ
        if (fscanf(fp, "%s %s %s %d %d\n", pnew->item.anum, pnew->item.pnum, pnew->item.to,
                   &(pnew->item.totalNum), &(pnew->item.bookNum)) == EOF)
        {
            //�ж��Ƿ��Ѿ������ļ�β, ����ȡ������Ϣ����pnew
            break;
        }

        //��������Ϣ����������
        pnew->next = NULL;
        if (scan == NULL)	//������Ϊ��, �򽫸���Ϣ��Ϊ�����ͷ
        {
            *plist = pnew;
            scan = *plist;
        }
        else	//������ǿ�, ����Ϣ׷�ӵ������β��
        {
            while (scan->next != NULL)
                scan = scan->next;  /* find end of list    */
            scan->next = pnew;      /* add pnew to end     */
        }
    }
    fclose(fp);
    return 0;
}

int ReadCustomerDataFileToMemory(CustomerList * plist)
{
    FILE* fp = fopen("customer.dat", "r");
    if (fp == NULL)
    {
        printf("Read airline.dat ERROR, exiting...");
        return -1;
    }

	CustomerNode *pnew;	//pointer to a node
    CustomerNode * scan = *plist;

    for (int i = 0; i < MAX_CUSTOMER; i++)
    {
        pnew = (CustomerNode *) malloc(sizeof(CustomerNode));
        if (fscanf(fp, "%s %s %d\n", pnew->item.cname, pnew->item.anum, &(pnew->item.seatnum)) == EOF)
        {
            break;
        }

        pnew->next = NULL;
        if (scan == NULL)
        {
            *plist = pnew;
            scan = *plist;
        }
        else
        {
            while (scan->next != NULL)
                scan = scan->next;  /* find end of list    */
            scan->next = pnew;      /* add pnew to end     */
        }
    }
    fclose(fp);
    return 0;
}

int SaveAirlineDataToFile(AirlineList * plist)
{
    FILE* fp = fopen("airline.dat", "w");
    if (fp == NULL)
    {
        printf("д�� airline_write.dat �ļ�ʱ����, �˳���...");
        return -1;
    }

    AirlineNode * pnode = *plist;    /* set to start of list   */
    while (pnode != NULL)
    {
        fprintf(fp, "%s %s %s %d %d\n", pnode->item.anum, pnode->item.pnum, pnode->item.to
                , pnode->item.totalNum, pnode->item.bookNum);
        pnode = pnode->next;
    }

    fclose(fp);
    return 0;
}

int SaveCustomerDataToFile(CustomerList * plist)
{
    FILE* fp = fopen("customer.dat", "w");
    if (fp == NULL)
    {
        printf("д�� customer.dat �ļ�ʱ����, �˳���...");
        return -1;
    }

    CustomerNode * pnode = *plist;    /* set to start of list   */
    while (pnode != NULL)

    {
        fprintf(fp, "%s %s %d\n", pnode->item.cname, pnode->item.anum, pnode->item.seatnum);
        pnode = pnode->next;
    }
    fclose(fp);
    return 0;
}

int InitializeSystem(AirlineList * AList, CustomerList * CList)
{
    InitializeAirlineList(AList);
    InitializeCustomerList(CList);
    ReadAirlineDataFileToMemory(AList);
    ReadCustomerDataFileToMemory(CList);

    return 0;
}

int ExitSystem(AirlineList * AList, CustomerList * CList)
{
    SaveAirlineDataToFile(AList);
    SaveCustomerDataToFile(CList);
    EmptyTheList(AList);
    EmptyCustomerList(CList);
    return 0;
}

