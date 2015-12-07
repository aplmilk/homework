#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100

using namespace std;

typedef struct
{
    int key;
}Node;//定义节点

typedef struct
{
    Node a[N];
    int n;
}Heap; //定义堆
Heap h;

void Insert(Heap *h , Node n) //向堆中插入元素
{
    int i,temp;
    i = h->n; //堆元素的总数
    while((i != 1) && (n.key < h->a[i/2].key)) //折半法找到插入新元素的位置，满足最小堆
    {
        h->a[i] = h->a[i/2];
        i/=2;
    }
    h->a[i].key = n.key;
}

void Print(Heap *h) //打印堆
{
    int i;
    for (i = 1 ; i < h->n ; i++)
    {
        cout << h->a[i].key << " ";
    }
    cout << endl;
}

void Build(Heap *h) //初始化堆
{
    int num,i,j;
    srand(time(NULL));
    for (i = 1 ; i <= h->n; i++)
    {
        num = rand()%100;
        h->a[i].key = num;
    }
    for (i = 1 ; i <= h->n ; i++) //冒泡排序
    {
        for (j = i ; j <= h->n ; j++)
        {
            if (h->a[i].key > h->a[j].key)
            {
                num = h->a[i].key;
                h->a[i].key = h->a[j].key;
                h->a[j].key = num;
            }
        }
    }
    Print(h);
}

void Delete(Heap *h) //删除堆中的最小值
{
    int p = 1,c = 2,t;
    Node temp;
    h->n--;
    t = h->n;
    temp.key = h->a[h->n--].key; //将最后一个数字调到最顶
    h->a[1].key = temp.key;
    while (c <= h->n)
    {
        if ((c <= h->n) && (h->a[c].key > h->a[c+1].key)) //重新排序
            c++;
        if (h->a[p].key <= h->a[c].key)
            break;
        h->a[p].key = h->a[c].key;
        p = c;
        c *= 2; //转变父子关系
    }
    h->a[p] = temp;
    h->n = t;
    Print(h);
}

int main()
{
    int count,num,de,flag,i,option;
    Node n;
    cout << "输入队列大小:" << endl;
    cin >> count;
    h.n = count + 1;
    Build(&h);
    for (i = 0 ; i < N ; i++)
    {
        cout << "功能选择:1.插入 2.删除" <<endl;
        cin >> option;
        switch(option)
        {
        case 1:
            cout << "要插入的数据：" << endl;
            cin >> num;
            n.key = num;
            Insert(&h,n);
            h.n++;
            Print(&h);
            break;
        case 2:
            Delete(&h);
            break;
        }
    }
    return 0;
}
