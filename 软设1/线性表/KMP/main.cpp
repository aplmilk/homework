#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20

using namespace std;

void CNext(char *a,int *next,int l) //建立next数组
{
    next[0] = -1;
    int k = -1,j = 0;
    while (j < l - 1)
    {
        if (k == -1 || a[k] == a[j]) //如果是第一个元素或者前缀等于后缀
        {
            ++k;
            ++j;
            next[j] = k;
        }
        else
            k = next[k]; //向前寻找
    }
}

int Search(char *a,char *b,int *next,int l) //寻找字符串出现的地址
{
    int i = 0,j = 0;
    while (i < N && j < l)
    {
        if (j == -1 || a[i] == b[j]) //如果j==-1或者匹配成功
        {
            i++;
            j++;
        }
        else
        {
            j = next[j]; //匹配不成功则移动待匹配字符串
        }
    }
    if (j == l) //返回位置
        return i-j;
    else
        return -1;
}

void Build(char *a) //随机建立原数组
{
    int i;
    srand(time(NULL));
    for (i = 0 ; i < N ; i++)
    {
        a[i] = 'A' + rand()%5; //数组元素只在ABCDE之间
    }
}

void Print(char *a) //打印文本串
{
    int i;
    for (i = 0 ; i < N ; i++)
    {
        cout << a[i];
    }
    cout << endl;
}

int Enter(char *b) //用户输入查找字符串
{
    int i;
    cin >> b;
    for (i = 0 ; i < N ;)
    {
        if (b[i] == '\0')
        {
            return i; //返回字符串中字符的个数
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
    cout << "产生的字符串:" << endl;
    Build(a);
    Print(a);
    cout << "输入要查找的字符串:" << endl;
    l = Enter(b);
    CNext(a,next,l);
    s = Search(a,b,next,l);
    if (s == -1)
        cout << "该字符串不存在." << endl;
    else
        cout << "字符串在原字符串的第" << s + 1 << " 个位置." << endl;
    return 0;
}
