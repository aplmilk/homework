#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define TOP 5

typedef struct hufnode    // 哈夫曼树结点数据结构
{
    int weight,children[TOP],parent,choose;    // choose：辅助建立用的标记域
} HUFNODE;

int AddZero(int n,int k);    // 增添零元素
int Total(int m,int k);    // 统计总共的结点数
void CreateHuffmanTree(int n,int m,int l,int k);    // 构造哈夫曼树
int SeleceMin(HUFNODE huffmantree[],int m);    // 选取最小值
void SelectChildrren(HUFNODE huffmantree[],int m,int fc[],int k);    // 选取k个最小元素
void PrintHuf(HUFNODE huffmantree[],int n,int l,int k);    // 打印哈夫曼树

int main()
{
    int n,k,m,l;
    printf("Please enter the amount of the weighted nodes:");
    scanf("%d",&n);
    printf("Please enter k(<=%d): ",TOP);
    scanf("%d",&k);

    m = AddZero(n,k);    // 需添加的零元素的最少个数

    l = Total(m + n,k);    // 一共最少的结点数
    CreateHuffmanTree(n,m,l,k);    // 建立
    return 0;
}

int AddZero(int n,int k)    // 需添加的零元素的个数
{
    while(n > k)    // 直至至多再凑成一组（k个元素）
    {
        n = n / k + n % k;    // k个一组合并之后结点最少个数
    }
    n = k - n;    // 为凑成k个一组，缺少的个数
    return n;
}

int Total(int m,int k)    // 总共的结点数
{
    int l;
    l = m;
    while(m >= k)    // 直至至多再凑成一组（k个元素）
    {
        l += m / k;    // k 个一组而形成的新的结点数
        m = m / k + m % k;    // k个一组合并之后结点最少个数
    }
    return l;
}

void CreateHuffmanTree(int n,int m,int l,int k)    // 构造哈夫曼树
{
    int i,fc[k],j;
    HUFNODE huffmantree[l];
    for(i = 0; i < m + n; i ++)    // 初始化
    {
        if(i < n)    // 用户输入的带权结点
        {
            printf("The weight of number %d node:",i + 1);
            scanf("%d",&huffmantree[i].weight);
        }
        else    // 补充的无权结点
        {
            huffmantree[i].weight = 0;
        }
        huffmantree[i].parent = -1;    // 初始值
        for(j = 0; j < k; j ++)
        {
            huffmantree[i].children[j] = -1;
            fc[j] = 0;
        }
        huffmantree[i].choose = 0;
    }
    for(i = m + n; i < l; i ++)    // 构建哈夫曼树
    {
        SelectChildrren(huffmantree,i,fc,k);    // 取得k个具有最小权值的结点，下标存入下标数组
        huffmantree[i].weight = 0;    // 新结点初始化
        huffmantree[i].choose = 0;
        huffmantree[i].parent = -1;
        for(j = 0; j < k; j ++)
        {
            huffmantree[i].weight += huffmantree[fc[j]].weight;    // 新结点权值为孩子结点权值之和
            huffmantree[i].children[j] = fc[j];    // 孩子结点
            huffmantree[fc[j]].parent = i;    // 还子结点的父结点
        }
    }
    PrintHuf(huffmantree,m + n,l,k);    // 打印
}

void SelectChildrren(HUFNODE huffmantree[],int m,int fc[],int k)    // 选取k个具有最小权值的结点
{
    int i,j;
    for(i = 0; i < k; i ++)    // 循环k次，每次选一个具有最小权值的结点
    {
        j = SeleceMin(huffmantree,m);
        if(j != -1)
        {
            fc[i] = j;
        }
    }
}

int SeleceMin(HUFNODE huffmantree[],int m)    // 选取权值最小的结点
{
    int i = 0,j;
    while(huffmantree[i].choose == 1)    // 寻找第一个没有被选择过的结点
    {
        i ++;
        if(i == m)
        {
            return -1;
        }
    }
    for(j = i; j < m; j ++)    // 循环比较
    {
        if(huffmantree[j].choose == 0)    // 未被选择
        {
            if(huffmantree[j].weight < huffmantree[i].weight)    // 权值更小的结点
            {
                i = j;
            }
        }
    }
    huffmantree[i].choose = 1;    // 标记已选，不在以后的选择范围内
    return i;
}

void PrintHuf(HUFNODE huffmantree[],int n,int l,int k)    // 打印
{
    int i,j;
    for(i = n; i < l; i ++)    // 父结点开始遍历
    {
        printf("%d:",huffmantree[i].weight);
        for(j = 0; j < k; j ++)    // 孩子
        {
            printf(" %d(%d)",huffmantree[i].children[j],huffmantree[huffmantree[i].children[j]].weight);
        }
        printf("\n");
    }
}
