#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100

using namespace std;

typedef struct
{
    int key;
}Node;//����ڵ�

typedef struct
{
    Node a[N];
    int n;
}Heap; //�����
Heap h;

void Insert(Heap *h , Node n) //����в���Ԫ��
{
    int i,temp;
    i = h->n; //��Ԫ�ص�����
    while((i != 1) && (n.key < h->a[i/2].key)) //�۰뷨�ҵ�������Ԫ�ص�λ�ã�������С��
    {
        h->a[i] = h->a[i/2];
        i/=2;
    }
    h->a[i].key = n.key;
}

void Print(Heap *h) //��ӡ��
{
    int i;
    for (i = 1 ; i < h->n ; i++)
    {
        cout << h->a[i].key << " ";
    }
    cout << endl;
}

void Build(Heap *h) //��ʼ����
{
    int num,i,j;
    srand(time(NULL));
    for (i = 1 ; i <= h->n; i++)
    {
        num = rand()%100;
        h->a[i].key = num;
    }
    for (i = 1 ; i <= h->n ; i++) //ð������
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

void Delete(Heap *h) //ɾ�����е���Сֵ
{
    int p = 1,c = 2,t;
    Node temp;
    h->n--;
    t = h->n;
    temp.key = h->a[h->n--].key; //�����һ�����ֵ����
    h->a[1].key = temp.key;
    while (c <= h->n)
    {
        if ((c <= h->n) && (h->a[c].key > h->a[c+1].key)) //��������
            c++;
        if (h->a[p].key <= h->a[c].key)
            break;
        h->a[p].key = h->a[c].key;
        p = c;
        c *= 2; //ת�丸�ӹ�ϵ
    }
    h->a[p] = temp;
    h->n = t;
    Print(h);
}

int main()
{
    int count,num,de,flag,i,option;
    Node n;
    cout << "������д�С:" << endl;
    cin >> count;
    h.n = count + 1;
    Build(&h);
    for (i = 0 ; i < N ; i++)
    {
        cout << "����ѡ��:1.���� 2.ɾ��" <<endl;
        cin >> option;
        switch(option)
        {
        case 1:
            cout << "Ҫ��������ݣ�" << endl;
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
