#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100

using namespace std;

typedef struct Node //定义结点类型，包含行数、列数和数值
{
    int row;
    int column;
    int number;
}Node1;

void Build(Node1 a[N][N],int m,int n) //建立数列
{
    int i,j,x,y;

    for (i = 0 ; i < m ; i++)
    {
        for (j = 0 ; j < n ; j++)
        {
            x = rand()%2;
            switch(x) //利用随机数创造数列
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


void Print(Node1 a[N][N],int m,int n) //打印数列
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

void Print1(Node1 b1[N*N],int count) //打印三元组
{
    int i;
    for (i = 0 ; i < count ; i++)
    {
        cout << b1[i].row << " " << b1[i].column << " " << b1[i].number << endl;
    }
}

int Triad(Node1 b1[N*N],Node1 a[N][N],int m,int n) //由数组创造三元组
{
    int i,j,count = 1;
    b1[0].row = m;
    b1[0].column = n;
    for (i = 0; i < m ; i++) //将数组中元素的相关的信息输入到三元组中
    {
        for (j = 0 ; j < n ; j++)
        {
            if (a[i][j].number != 0)
            {
                b1[count].row = a[i][j].row;
                b1[count].column = a[i][j].column;
                b1[count].number = a[i][j].number;
                count++; //计算非零元素的个数
            }
        }
    }
    b1[0].number = count - 1;
    cout << "原三元组:" << endl;
    Print1(b1,count); //调用函数打印出三元组
    return count;
}

void Trans(Node1 b1[N*N],Node1 b2[N*N],int count,int m,int n) //将三元组进行转置
{
    int num[N],c1[N];
    int i,j,x,y;
    c1[1] = 1;
    b2[0].column = b1[0].row;
    b2[0].row = b1[0].column;
    b2[0].number = b1[0].number;
    for (i = 0;i <= n; i++) //利用num数组计算同一列非零元素的个数
    {
        num[i] = 0;
        for (j = 1 ; j < count ; j++)
        {
            if (b1[j].column == i)
                num[i]++;
        }
    }
    for (i = 2; i <= n ; i++) //计算每一列第一个非零元素在转置数组中的个数
    {
        c1[i] = c1[i-1] + num[i-2];
    }
    for (i = 1; i < count ; i++) //将数组进行转置
    {
        x = b1[i].column;
        y = c1[x+1];
        b2[y].column = b1[i].row;
        b2[y].row = b1[i].column;
        b2[y].number = b1[i].number;
        c1[x+1]++;
    }
    cout << "转置后的三元组" << endl;
    Print1(b2,count); //打印转置后的三元组
}

int main()
{
    int m,n,count;
    Node1 a[N][N],b1[N*N],b2[N*N];
    srand(time(NULL));
    cout << "输入行数:" << endl;
    cin >> m;
    cout << "输入列数:" << endl;
    cin >> n;
    Build(a,m,n); //建立数列
    Print(a,m,n); //打印数列
    count = Triad(b1,a,m,n); //建立三元组
    Trans(b1,b2,count,m,n); //三元组转置
    return 0;
}
