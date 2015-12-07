#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MaxLevel 10

using namespace std;

typedef struct Node //����������
{
	int x;
	struct Node *next; //ָ����һ������ָ��
	struct Node *down; //ָ���·��ڵ��ָ��
}Node1;

typedef struct Level //�������������
{
	struct Node *next;
}Level1;

Level1 Sl[MaxLevel]; //��������������

Node1 *SnCreate(int number) //������һ�������
{
    Node1 *head,*p,*pre,*pre1,*np;
    int i,temp;
    head = (Node1*)malloc(sizeof(Node1)); //ͷָ��
    np = (Node1*)malloc(sizeof(Node1)); //�½��

    head->next = NULL;
    head->down = NULL;
    pre = head;
    srand(time(NULL));

    for (i = 0 ; i < number ; i++)
    {
        p = (Node1*)malloc(sizeof(Node1));
        p->x = rand()%100; //���ȷ������ֵ
        p->down = NULL;
        pre->next = p; //ǰһ�����ָ����һ�����
        pre = p;
    }

    p->next = NULL; //β���ָ���
    pre->next = NULL;
    pre1 = head->next;
    p = pre1;

    while(p->next) //����˫��ѭ�����������
    {
        for (pre1 = p->next ; pre1 != NULL ; pre1 = pre1->next)
        {
            if(p->x > pre1->x)
            {
                temp = p->x;
                p->x = pre1->x;
                pre1->x = temp;
            }
        }
        p = p->next;
    }

    head->x = 0;
    head->down = NULL;
    Sl[0].next = head;

    for (i = 1; i < MaxLevel ; i++) //��ÿһ��Ĺ��ɽ�����һ��������
    {
        np = (Node1*)malloc(sizeof(Node1));
        np->x = i;
        np->down = Sl[i-1].next;
        Sl[i].next = np;
    }
    return head;
}

void SlCreate(int j) //������������
{
    int i;
    Node1 *p,*pre,*np,*tra;
    pre = (Node1*)malloc(sizeof(Node1));
    pre = Sl[j].next;
    pre->down = NULL;
    pre->next = NULL;
    tra = (Node1*)malloc(sizeof(Node1)); //���ɽ��
    np = (Node1*)malloc(sizeof(Node1));
    p = (Node1*)malloc(sizeof(Node1));
    tra = Sl[j-1].next;
    p = tra->next;
    pre->down = tra;
    srand(time(NULL));
    while(p)
    {
        i = rand()%2;
        if (p->next == NULL)
            break;
        switch(i) //�����������ѡ���Ƿ����ϴ�
        {
        case 0:
            break;
        case 1:
            np = (Node1*)malloc(sizeof(Node1));
            np->x = p->x;
            np->down = p;
            pre->next = np;
            pre = np;
        }
        p = p->next;
    }
    np->next = NULL;
    pre->next = NULL;
    j++;
    if (j < MaxLevel) //����ѭ����㽨��
        SlCreate(j);
}

void Print1(Level1 Sl[]) //��ӡ����
{
    int i = MaxLevel;
    Node1 *p,*np;
    np = (Node1*)malloc(sizeof(Node1));
    p = (Node1*)malloc(sizeof(Node1));
    do
    {
        i--;
    }while(Sl[i].next->next == NULL); //�ҵ������ݵĲ���
    for (; i >= 0 ; i--)
    {
        cout << "Level" << i << "   ";
        np = Sl[i].next;
        p = np->next;
        while(p)
        {
            cout << p->x << " "; //����ÿ����������ӡ
            p = p->next;
        }
        cout << endl;
    }
}

int Find(Node1 *head,int x) //Ѱ���û���Ҫ���ҵ�����
{
    Node1 *p;
    p = head->next;
    while(p) //����������в���
    {
        if (p->x == x)
            return 1;
        else
            p = p->next;
    }
    return 0;
}

void Insert(int y) //�����û���Ҫ������
{
    Node1 *p,*pre,*np,*nnp;
    p = (Node1*)malloc(sizeof(Node1));
    pre = (Node1*)malloc(sizeof(Node1));
    int i = MaxLevel;
    int j = 0;
    do
    {
        i--;
    }while(Sl[i].next->next == NULL); //�ҵ������ݵĲ���
    pre = Sl[i].next;
    p = pre->next;
    while(p)
    {
        if (p->x > y && j == 0) //��ǰһλ��Ҫ������С����һλ��Ҫ�����ݴ�ʱ
        {
            np = (Node1*)malloc(sizeof(Node1));
            np->x = y;
            pre->next = np;
            np->next = p;
            pre = pre->down;
            while(pre) //��������ָ�룬������
            {
                p = pre->next;
                while(p->x <= y)
                {
                    pre = p;
                    p = p->next;
                }
                nnp = (Node1*)malloc(sizeof(Node1));
                nnp->x = y;
                pre->next = nnp;
                nnp->next = p;
                np->down = nnp;
                np = nnp;
                pre = pre->down;
            }
            p = NULL;
            j++;
        }
        else if (p->next == NULL && j == 0) //����Ԫ�ض���Ҫ������Сʱ
        {
            np = (Node1*)malloc(sizeof(Node1));
            np->x = y;
            np->next = NULL;
            p->next = np;
            p = p->down;
            pre = pre->down;
            while(p && pre)
            {
                p = pre->next;
                while (p->x <= y && p->next != NULL) //�ҵ��ʵ��Ĳ���λ��
                {
                    pre = p;
                    p = p->next;
                }
                if (p->x > y) //�ڱ������֮ǰ�ҵ��˲���λ�õ����
                {
                    nnp = (Node1*)malloc(sizeof(Node1));
                    nnp->x = np->x;
                    np->down = nnp;
                    pre->next = nnp;
                    nnp->next = p;
                    np = nnp;
                }
                else if (p->next == NULL) //���ݱȱ������ݶ�������
                {
                    nnp = (Node1*)malloc(sizeof(Node1));
                    nnp->x = y;
                    nnp->next = NULL;
                    np->down = nnp;
                    p->next = nnp;
                    np = nnp;

                }
                pre = pre->down;
                p = p->down;
            }
            p = NULL;
            j++;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
}

void Delete(int z) //ɾ���û�����Ҫ������
{
    int i,flag;
    Node1 *p,*pre;
    p = (Node1*)malloc(sizeof(Node1));
    pre = (Node1*)malloc(sizeof(Node1));
    i = MaxLevel;
    do
    {
        i--;
    }while(Sl[i].next->next == NULL); //�ҵ������ݵ�һ��
    do
    {
        pre = Sl[i].next;
        flag = Find(pre,z);
        i--;
    }while(i >= 0 && flag == 0);
    if (flag == 1)
    {
        i++;
        pre = Sl[i].next;
        p = pre->next;
        while(p->next != NULL && p->x != z)
        {
            pre = p;
            p = p->next;
        }
        pre->next = p->next; //��ǰһԪ�ص�ָ��ͱ�Ԫ�ص�ָ�����ӣ�ɾ����Ԫ��
        p = p->down;
        pre = pre->down;
        while(p) //��������ָ�룬���ɾ��
        {
            while(pre->next !=p)
                pre = pre->next;
            pre->next = p->next;
            pre = pre->down;
            p = p->down;
        }
        Print1(Sl); //��ӡɾ���������
    }
    else if (i < 0) //������û��Ҫ������
    {
        cout << z << " ������." << endl;
    }
}

int main()
{
    int number,x,y,z,answer,flag,m = 100,n;
    Node1 *head;
    head = (Node1*)malloc(sizeof(Node1));
	cout << "��������:" << endl; //�ֶ��������������
	cin >> number;
	head = SnCreate(number);//������һ��
	SlCreate(1);//��������
	Print1(Sl);//��ӡ����
	for (;m >=0;m--)//�����û������󣬽�����һ���Ĳ���
    {
        cout << "����ѡ��1.��ѯ 2.���� 3.ɾ��:" << endl;
        cin >> n;
        if (n == 1)//����Ѱ�Ҳ���
        {
            cout << "������Ҫ�������:" << endl;
            cin >> x;
            answer = Find(head,x);
            if (!answer)
                cout << x << "������" << endl;
            else
                cout << " �鵽 " <<x  << endl;
        }
        else if (n == 2)//���в������
        {
            cout << "���������:" << endl;
            cin >> y;
            Insert(y);
            Print1(Sl);
        }
        else if (n == 3)//����ɾ������
        {
           	cout << "ɾ��������:" << endl;
            cin >> z;
            Delete(z);
        }
        else//�û����зǷ�����ʱ
            cout << "��������룡" << endl;
    }
    return 0;
}
