#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define TOP 5

typedef struct hufnode    // ��������������ݽṹ
{
    int weight,children[TOP],parent,choose;    // choose�����������õı����
} HUFNODE;

int AddZero(int n,int k);    // ������Ԫ��
int Total(int m,int k);    // ͳ���ܹ��Ľ����
void CreateHuffmanTree(int n,int m,int l,int k);    // �����������
int SeleceMin(HUFNODE huffmantree[],int m);    // ѡȡ��Сֵ
void SelectChildrren(HUFNODE huffmantree[],int m,int fc[],int k);    // ѡȡk����СԪ��
void PrintHuf(HUFNODE huffmantree[],int n,int l,int k);    // ��ӡ��������

int main()
{
    int n,k,m,l;
    printf("Please enter the amount of the weighted nodes:");
    scanf("%d",&n);
    printf("Please enter k(<=%d): ",TOP);
    scanf("%d",&k);

    m = AddZero(n,k);    // ����ӵ���Ԫ�ص����ٸ���

    l = Total(m + n,k);    // һ�����ٵĽ����
    CreateHuffmanTree(n,m,l,k);    // ����
    return 0;
}

int AddZero(int n,int k)    // ����ӵ���Ԫ�صĸ���
{
    while(n > k)    // ֱ�������ٴճ�һ�飨k��Ԫ�أ�
    {
        n = n / k + n % k;    // k��һ��ϲ�֮�������ٸ���
    }
    n = k - n;    // Ϊ�ճ�k��һ�飬ȱ�ٵĸ���
    return n;
}

int Total(int m,int k)    // �ܹ��Ľ����
{
    int l;
    l = m;
    while(m >= k)    // ֱ�������ٴճ�һ�飨k��Ԫ�أ�
    {
        l += m / k;    // k ��һ����γɵ��µĽ����
        m = m / k + m % k;    // k��һ��ϲ�֮�������ٸ���
    }
    return l;
}

void CreateHuffmanTree(int n,int m,int l,int k)    // �����������
{
    int i,fc[k],j;
    HUFNODE huffmantree[l];
    for(i = 0; i < m + n; i ++)    // ��ʼ��
    {
        if(i < n)    // �û�����Ĵ�Ȩ���
        {
            printf("The weight of number %d node:",i + 1);
            scanf("%d",&huffmantree[i].weight);
        }
        else    // �������Ȩ���
        {
            huffmantree[i].weight = 0;
        }
        huffmantree[i].parent = -1;    // ��ʼֵ
        for(j = 0; j < k; j ++)
        {
            huffmantree[i].children[j] = -1;
            fc[j] = 0;
        }
        huffmantree[i].choose = 0;
    }
    for(i = m + n; i < l; i ++)    // ������������
    {
        SelectChildrren(huffmantree,i,fc,k);    // ȡ��k��������СȨֵ�Ľ�㣬�±�����±�����
        huffmantree[i].weight = 0;    // �½���ʼ��
        huffmantree[i].choose = 0;
        huffmantree[i].parent = -1;
        for(j = 0; j < k; j ++)
        {
            huffmantree[i].weight += huffmantree[fc[j]].weight;    // �½��ȨֵΪ���ӽ��Ȩֵ֮��
            huffmantree[i].children[j] = fc[j];    // ���ӽ��
            huffmantree[fc[j]].parent = i;    // ���ӽ��ĸ����
        }
    }
    PrintHuf(huffmantree,m + n,l,k);    // ��ӡ
}

void SelectChildrren(HUFNODE huffmantree[],int m,int fc[],int k)    // ѡȡk��������СȨֵ�Ľ��
{
    int i,j;
    for(i = 0; i < k; i ++)    // ѭ��k�Σ�ÿ��ѡһ��������СȨֵ�Ľ��
    {
        j = SeleceMin(huffmantree,m);
        if(j != -1)
        {
            fc[i] = j;
        }
    }
}

int SeleceMin(HUFNODE huffmantree[],int m)    // ѡȡȨֵ��С�Ľ��
{
    int i = 0,j;
    while(huffmantree[i].choose == 1)    // Ѱ�ҵ�һ��û�б�ѡ����Ľ��
    {
        i ++;
        if(i == m)
        {
            return -1;
        }
    }
    for(j = i; j < m; j ++)    // ѭ���Ƚ�
    {
        if(huffmantree[j].choose == 0)    // δ��ѡ��
        {
            if(huffmantree[j].weight < huffmantree[i].weight)    // Ȩֵ��С�Ľ��
            {
                i = j;
            }
        }
    }
    huffmantree[i].choose = 1;    // �����ѡ�������Ժ��ѡ��Χ��
    return i;
}

void PrintHuf(HUFNODE huffmantree[],int n,int l,int k)    // ��ӡ
{
    int i,j;
    for(i = n; i < l; i ++)    // ����㿪ʼ����
    {
        printf("%d:",huffmantree[i].weight);
        for(j = 0; j < k; j ++)    // ����
        {
            printf(" %d(%d)",huffmantree[i].children[j],huffmantree[huffmantree[i].children[j]].weight);
        }
        printf("\n");
    }
}
