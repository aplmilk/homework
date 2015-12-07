#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MaxLevel 10

using namespace std;

typedef struct Node //定义结点类型
{
	int x;
	struct Node *next; //指向下一个结点的指针
	struct Node *down; //指向下方节点的指针
}Node1;

typedef struct Level //定义层数的类型
{
	struct Node *next;
}Level1;

Level1 Sl[MaxLevel]; //建立层数的数组

Node1 *SnCreate(int number) //建立第一层的链表
{
    Node1 *head,*p,*pre,*pre1,*np;
    int i,temp;
    head = (Node1*)malloc(sizeof(Node1)); //头指针
    np = (Node1*)malloc(sizeof(Node1)); //新结点

    head->next = NULL;
    head->down = NULL;
    pre = head;
    srand(time(NULL));

    for (i = 0 ; i < number ; i++)
    {
        p = (Node1*)malloc(sizeof(Node1));
        p->x = rand()%100; //随机确定结点的值
        p->down = NULL;
        pre->next = p; //前一个结点指向下一个结点
        pre = p;
    }

    p->next = NULL; //尾结点指向空
    pre->next = NULL;
    pre1 = head->next;
    p = pre1;

    while(p->next) //利用双层循环将结点排序
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

    for (i = 1; i < MaxLevel ; i++) //将每一层的过渡结点和下一层连起来
    {
        np = (Node1*)malloc(sizeof(Node1));
        np->x = i;
        np->down = Sl[i-1].next;
        Sl[i].next = np;
    }
    return head;
}

void SlCreate(int j) //建立整个跳表
{
    int i;
    Node1 *p,*pre,*np,*tra;
    pre = (Node1*)malloc(sizeof(Node1));
    pre = Sl[j].next;
    pre->down = NULL;
    pre->next = NULL;
    tra = (Node1*)malloc(sizeof(Node1)); //过渡结点
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
        switch(i) //利用随机数，选择是否往上传
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
    if (j < MaxLevel) //利用循环层层建立
        SlCreate(j);
}

void Print1(Level1 Sl[]) //打印跳表
{
    int i = MaxLevel;
    Node1 *p,*np;
    np = (Node1*)malloc(sizeof(Node1));
    p = (Node1*)malloc(sizeof(Node1));
    do
    {
        i--;
    }while(Sl[i].next->next == NULL); //找到有数据的层数
    for (; i >= 0 ; i--)
    {
        cout << "Level" << i << "   ";
        np = Sl[i].next;
        p = np->next;
        while(p)
        {
            cout << p->x << " "; //利用每层的链表层层打印
            p = p->next;
        }
        cout << endl;
    }
}

int Find(Node1 *head,int x) //寻找用户需要查找的数据
{
    Node1 *p;
    p = head->next;
    while(p) //利用链表进行查找
    {
        if (p->x == x)
            return 1;
        else
            p = p->next;
    }
    return 0;
}

void Insert(int y) //插入用户需要的数据
{
    Node1 *p,*pre,*np,*nnp;
    p = (Node1*)malloc(sizeof(Node1));
    pre = (Node1*)malloc(sizeof(Node1));
    int i = MaxLevel;
    int j = 0;
    do
    {
        i--;
    }while(Sl[i].next->next == NULL); //找到有数据的层数
    pre = Sl[i].next;
    p = pre->next;
    while(p)
    {
        if (p->x > y && j == 0) //当前一位比要求数据小，后一位比要求数据大时
        {
            np = (Node1*)malloc(sizeof(Node1));
            np->x = y;
            pre->next = np;
            np->next = p;
            pre = pre->down;
            while(pre) //根据向下指针，逐层插入
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
        else if (p->next == NULL && j == 0) //整层元素都比要求数据小时
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
                while (p->x <= y && p->next != NULL) //找到适当的插入位置
                {
                    pre = p;
                    p = p->next;
                }
                if (p->x > y) //在本层结束之前找到了插入位置的情况
                {
                    nnp = (Node1*)malloc(sizeof(Node1));
                    nnp->x = np->x;
                    np->down = nnp;
                    pre->next = nnp;
                    nnp->next = p;
                    np = nnp;
                }
                else if (p->next == NULL) //数据比本层数据都大的情况
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

void Delete(int z) //删除用户不需要的数据
{
    int i,flag;
    Node1 *p,*pre;
    p = (Node1*)malloc(sizeof(Node1));
    pre = (Node1*)malloc(sizeof(Node1));
    i = MaxLevel;
    do
    {
        i--;
    }while(Sl[i].next->next == NULL); //找到有数据的一层
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
        pre->next = p->next; //将前一元素的指针和本元素的指针链接，删除本元素
        p = p->down;
        pre = pre->down;
        while(p) //利用向下指针，逐层删除
        {
            while(pre->next !=p)
                pre = pre->next;
            pre->next = p->next;
            pre = pre->down;
            p = p->down;
        }
        Print1(Sl); //打印删除后的跳表
    }
    else if (i < 0) //跳表中没有要求数据
    {
        cout << z << " 不存在." << endl;
    }
}

int main()
{
    int number,x,y,z,answer,flag,m = 100,n;
    Node1 *head;
    head = (Node1*)malloc(sizeof(Node1));
	cout << "输入数据:" << endl; //手动输入最大层的容量
	cin >> number;
	head = SnCreate(number);//建立第一层
	SlCreate(1);//建立跳表
	Print1(Sl);//打印跳表
	for (;m >=0;m--)//根据用户的需求，进行下一步的操作
    {
        cout << "功能选择：1.查询 2.插入 3.删除:" << endl;
        cin >> n;
        if (n == 1)//进行寻找操作
        {
            cout << "输入你要查的数字:" << endl;
            cin >> x;
            answer = Find(head,x);
            if (!answer)
                cout << x << "不存在" << endl;
            else
                cout << " 查到 " <<x  << endl;
        }
        else if (n == 2)//进行插入操作
        {
            cout << "插入的数字:" << endl;
            cin >> y;
            Insert(y);
            Print1(Sl);
        }
        else if (n == 3)//进行删除操作
        {
           	cout << "删除的数字:" << endl;
            cin >> z;
            Delete(z);
        }
        else//用户进行非法操作时
            cout << "错误的输入！" << endl;
    }
    return 0;
}
