#include <iostream>

using namespace std;

char data[50]; //��¼������Ϣ
int n2,e;   //Kruskal

const int infinity=99999;

typedef struct EdgeSet
{
    int cost;
    int begin;
    int end;
}EdgeSet;

void Kruskal_Min_Tree(EdgeSet edge[],int n);
void CreateEdge(EdgeSet edge[]);
void Sort(EdgeSet edge[]);
void PrintE(EdgeSet edge[]);

int main()
{
    EdgeSet edge[50];
    CreateEdge(edge);
    PrintE(edge);
    Kruskal_Min_Tree(edge,n2);
    return 0;
}

void Kruskal_Min_Tree(EdgeSet edge[],int n)
{
    int i;
    int bnf,edf;
    int parents[100];
    Sort(edge);
    cout<<"�����";
    PrintE(edge);
    cout<<endl;
    //��ʼ��
    for(i=0;i<n;i++)
    {
        parents[i]=i;
    }
    cout<<"��С������:"<<endl;
    for(i=0;i<n;i++)
    {
        bnf=parents[edge[i].begin];
        edf=parents[edge[i].end];
        if(bnf!=edf)
        {
            parents[bnf]=edf;
            cout<<"("<<data[edge[i].begin]<<","<<data[edge[i].end]<<")";
            cout<<"--"<<edge[i].cost<<endl;
        }
    }
}

void CreateEdge(EdgeSet edge[])
{
    int i;
    cout<<"�����붥�����ͱ�����";
    cin>>n2>>e;
    cout<<"������������Ϣ��";
    for(i=0;i<n2;i++)
    {
        cin>>data[i];
    }
    cout<<"������ߵ���㡢�յ㡢Ȩֵ��";
    for(i=0;i<e;i++)
    {
        cin>>edge[i].begin>>edge[i].end>>edge[i].cost;
    }
}

void Sort(EdgeSet edge[])
{
    int i,j,min,k; //k��¼min�±�
    int a,b,c;  //�����м���
    for(i=0;i<e;i++)
    {
        min=edge[i].cost;
        k=i;
        for(j=i;j<e;j++)
        {
            if(edge[j].cost<min)
            {
                min=edge[j].cost;
                k=j;
            }
        }
        //����
        if(k!=i)
        {
            a=edge[i].cost;
            edge[i].cost=edge[k].cost;
            edge[k].cost=a;

            b=edge[i].begin;
            edge[i].begin=edge[k].begin;
            edge[k].begin=b;

            c=edge[i].end;
            edge[i].end=edge[k].end;
            edge[k].end=c;

        }
    }
}

void PrintE(EdgeSet edge[])
{
    int i;
    cout<<"����ϢΪ��"<<endl;
    for(i=0;i<n2;i++)
    {
     cout<<"("<<edge[i].begin<<","  <<edge[i].end<<")--" <<edge[i].cost<<endl;
    }
}
