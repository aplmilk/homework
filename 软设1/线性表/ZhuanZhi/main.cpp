#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100

using namespace std;

typedef struct Node //���������ͣ�������������������ֵ
{
    int row;
    int column;
    int number;
}Node1;

void Build(Node1 a[N][N],int m,int n) //��������
{
    int i,j,x,y;

    for (i = 0 ; i < m ; i++)
    {
        for (j = 0 ; j < n ; j++)
        {
            x = rand()%2;
            switch(x) //�����������������
            {
            case 0:
                a[i][j].number = 0;
                break;
            case 1:
                y = rand()%100;
                a[i][j].row = i;
                a[i][j].column = j;
                a[i][j].number = y;
                break;
            }
        }
    }
}


void Print(Node1 a[N][N],int m,int n) //��ӡ����
{
    int i,j;
    for (i = 0 ; i < m ; i++)
    {
        for (j = 0 ; j < n ; j++)
        {
            cout << a[i][j].number << " ";
        }
        cout << endl;
    }
}

void Print1(Node1 b1[N*N],int count) //��ӡ��Ԫ��
{
    int i;
    for (i = 0 ; i < count ; i++)
    {
        cout << b1[i].row << " " << b1[i].column << " " << b1[i].number << endl;
    }
}

int Triad(Node1 b1[N*N],Node1 a[N][N],int m,int n) //�����鴴����Ԫ��
{
    int i,j,count = 1;
    b1[0].row = m;
    b1[0].column = n;
    for (i = 0; i < m ; i++) //��������Ԫ�ص���ص���Ϣ���뵽��Ԫ����
    {
        for (j = 0 ; j < n ; j++)
        {
            if (a[i][j].number != 0)
            {
                b1[count].row = a[i][j].row;
                b1[count].column = a[i][j].column;
                b1[count].number = a[i][j].number;
                count++; //�������Ԫ�صĸ���
            }
        }
    }
    b1[0].number = count - 1;
    cout << "ԭ��Ԫ��:" << endl;
    Print1(b1,count); //���ú�����ӡ����Ԫ��
    return count;
}

void Trans(Node1 b1[N*N],Node1 b2[N*N],int count,int m,int n) //����Ԫ�����ת��
{
    int num[N],c1[N];
    int i,j,x,y;
    c1[1] = 1;
    b2[0].column = b1[0].row;
    b2[0].row = b1[0].column;
    b2[0].number = b1[0].number;
    for (i = 0;i <= n; i++) //����num�������ͬһ�з���Ԫ�صĸ���
    {
        num[i] = 0;
        for (j = 1 ; j < count ; j++)
        {
            if (b1[j].column == i)
                num[i]++;
        }
    }
    for (i = 2; i <= n ; i++) //����ÿһ�е�һ������Ԫ����ת�������еĸ���
    {
        c1[i] = c1[i-1] + num[i-2];
    }
    for (i = 1; i < count ; i++) //���������ת��
    {
        x = b1[i].column;
        y = c1[x+1];
        b2[y].column = b1[i].row;
        b2[y].row = b1[i].column;
        b2[y].number = b1[i].number;
        c1[x+1]++;
    }
    cout << "ת�ú����Ԫ��" << endl;
    Print1(b2,count); //��ӡת�ú����Ԫ��
}

int main()
{
    int m,n,count;
    Node1 a[N][N],b1[N*N],b2[N*N];
    srand(time(NULL));
    cout << "��������:" << endl;
    cin >> m;
    cout << "��������:" << endl;
    cin >> n;
    Build(a,m,n); //��������
    Print(a,m,n); //��ӡ����
    count = Triad(b1,a,m,n); //������Ԫ��
    Trans(b1,b2,count,m,n); //��Ԫ��ת��
    return 0;
}
