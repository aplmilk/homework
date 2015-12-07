#include <iostream>

using namespace std;

char data[50]; //记录各点信息
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
    cout<<"排序后";
    PrintE(edge);
    cout<<endl;
    //初始化
    for(i=0;i<n;i++)
    {
        parents[i]=i;
    }
    cout<<"最小生成树:"<<endl;
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
    cout<<"请输入顶点数和边数：";
    cin>>n2>>e;
    cout<<"请输入各结点信息：";
    for(i=0;i<n2;i++)
    {
        cin>>data[i];
    }
    cout<<"请输入边的起点、终点、权值：";
    for(i=0;i<e;i++)
    {
        cin>>edge[i].begin>>edge[i].end>>edge[i].cost;
    }
}

void Sort(EdgeSet edge[])
{
    int i,j,min,k; //k记录min下标
    int a,b,c;  //用作中间量
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
        //交换
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
    cout<<"边信息为："<<endl;
    for(i=0;i<n2;i++)
    {
     cout<<"("<<edge[i].begin<<","  <<edge[i].end<<")--" <<edge[i].cost<<endl;
    }
}
