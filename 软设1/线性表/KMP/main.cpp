#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20

using namespace std;

void CNext(char *a,int *next,int l) //����next����
{
    next[0] = -1;
    int k = -1,j = 0;
    while (j < l - 1)
    {
        if (k == -1 || a[k] == a[j]) //����ǵ�һ��Ԫ�ػ���ǰ׺���ں�׺
        {
            ++k;
            ++j;
            next[j] = k;
        }
        else
            k = next[k]; //��ǰѰ��
    }
}

int Search(char *a,char *b,int *next,int l) //Ѱ���ַ������ֵĵ�ַ
{
    int i = 0,j = 0;
    while (i < N && j < l)
    {
        if (j == -1 || a[i] == b[j]) //���j==-1����ƥ��ɹ�
        {
            i++;
            j++;
        }
        else
        {
            j = next[j]; //ƥ�䲻�ɹ����ƶ���ƥ���ַ���
        }
    }
    if (j == l) //����λ��
        return i-j;
    else
        return -1;
}

void Build(char *a) //�������ԭ����
{
    int i;
    srand(time(NULL));
    for (i = 0 ; i < N ; i++)
    {
        a[i] = 'A' + rand()%5; //����Ԫ��ֻ��ABCDE֮��
    }
}

void Print(char *a) //��ӡ�ı���
{
    int i;
    for (i = 0 ; i < N ; i++)
    {
        cout << a[i];
    }
    cout << endl;
}

int Enter(char *b) //�û���������ַ���
{
    int i;
    cin >> b;
    for (i = 0 ; i < N ;)
    {
        if (b[i] == '\0')
        {
            return i; //�����ַ������ַ��ĸ���
        }
        else
            i++;
    }
    return 0;
}

int main()
{
    char a[N],b[N];
    int l,s,next[N];
    cout << "�������ַ���:" << endl;
    Build(a);
    Print(a);
    cout << "����Ҫ���ҵ��ַ���:" << endl;
    l = Enter(b);
    CNext(a,next,l);
    s = Search(a,b,next,l);
    if (s == -1)
        cout << "���ַ���������." << endl;
    else
        cout << "�ַ�����ԭ�ַ����ĵ�" << s + 1 << " ��λ��." << endl;
    return 0;
}
