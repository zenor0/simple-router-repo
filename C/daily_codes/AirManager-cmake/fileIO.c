#include <stdio.h>
#include <stdlib.h>
#include "nodeFunction.h"

int ReadAirlineDataFileToMemory(AirlineList * plist)
{
    //读取airline.dat文件, 如错误则退出
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
        //初始化pnew作为一个临时的结构体变量, 用于存储临时读入的一条信息
        pnew = (AirlineNode *) malloc(sizeof(AirlineNode));


        //读入airline.dat 的一行信息
        if (fscanf(fp, "%s %s %s %d %d\n", pnew->item.anum, pnew->item.pnum, pnew->item.to,
                   &(pnew->item.totalNum), &(pnew->item.bookNum)) == EOF)
        {
            //判断是否已经读到文件尾, 将读取到的信息存入pnew
            break;
        }

        //将航班信息存入链表当中
        pnew->next = NULL;
        if (scan == NULL)	//若链表为空, 则将该信息作为链表的头
        {
            *plist = pnew;
            scan = *plist;
        }
        else	//若链表非空, 则将信息追加到链表的尾部
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
        printf("写入 airline_write.dat 文件时出错, 退出中...");
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
        printf("写入 customer.dat 文件时出错, 退出中...");
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

