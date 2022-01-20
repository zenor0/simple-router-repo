#ifndef LIST_H_
#define LIST_H_
#include <stdbool.h>

#define MAX_AIRLINE 10
#define MAX_CUSTOMER 1000
#define ADMIN_PASSWORD "admin"//����Ա����

typedef struct Airline
{
	char anum[10];//�����
	char pnum[10];//�ɻ���
	char to[20];//Ŀ�ĵ�
	int totalNum;//��Ʊ��
	int bookNum;//��Ʊ��
} AirlineItem;     //������Ϣ�ṹ��

typedef struct NodeAirline
{
	AirlineItem item;
	struct NodeAirline* next;
} AirlineNode;

typedef AirlineNode* AirlineList;

typedef struct Customer
{
	char cname[10];  //�ͻ���Ϣ
	char anum[10];  //�����
	int seatnum;  //��λ��
} CustomerItem;      //�ͻ���Ϣ�ṹ��

typedef struct NodeCustomer
{
	CustomerItem item;
	struct NodeCustomer* next;
} CustomerNode;

typedef CustomerNode* CustomerList;

/* function prototypes */

void InitializeAirlineList(AirlineList * plist);	//��ʼ������
bool AirlineListIsEmpty(const AirlineList *plist);	//�ж������Ƿ��
bool AirlineListIsFull(void);	//�ж������Ƿ���
unsigned int AirlineListItemCount(const AirlineList *plist);	//���������е�Ԫ�ظ���
bool AddAirlineItem(AirlineItem item, AirlineList * plist);	//�����������Ԫ��
void TraverseAirline (const AirlineList *plist, void (* pfun)(AirlineItem item) );	//�������ÿ��Ԫ��Ӧ�ú���pfun
void EmptyTheList(AirlineList * plist);	//�������
void DeleteAirlineItem(AirlineNode * delNode, AirlineList * plist);	//ɾ�������е�Ԫ��
AirlineNode* MatchCorrespondAirlineAnum(char * matchStr, AirlineList * plist);	//������ matchStr ƥ��ĺ�����Ϣ



void InitializeCustomerList(CustomerList * plist);	//��ʼ������
bool AddCustomerItem(CustomerItem item, CustomerList * plist);	//���Ԫ�ص�������
void EmptyCustomerList(CustomerList * plist);	//�������
void DeleteCustomerItem(CustomerNode * delNode, CustomerList * plist);	//ɾ�������е�Ԫ��
CustomerNode* MatchCorrespondCustomerName(char *matchStr, CustomerList * plist);	//������ matchStr ƥ��Ĺ˿���Ϣ
void DeleteAirlineCustomer(char * matchAnum, CustomerList * Clist);	//ɾ����Ӧ����Ĺ˿�
bool CheckIfBooked(char *matchName, char *matchAnum, CustomerList * CList);	//���˿��б����Ƿ������ matchAnum �� matchName ƥ�����Ϣ
int AllocateSeatNum(AirlineNode * ANode, CustomerList * CList);	//Ϊ�˿ͷ���һ����λ��(��0��ʼ)

#endif
