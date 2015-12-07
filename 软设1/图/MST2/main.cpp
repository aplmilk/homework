#include <iostream>

using namespace std;

char data[50]; //记录各点信息
int c[50][50];//记录各边权值
int n; //记录边数(prim)
int n2,e;   //Kruskal
const int infinity=99999;

typedef struct EdgeSet
{
    int cost;
    int begin;
    int end;
}EdgeSet;

void Create();
void Prim();
void Kruskal_Min_Tree(EdgeSet edge[],int n);
void CreateEdge(EdgeSet edge[]);
void Sort(EdgeSet edge[]);

int main()
{
   // EdgeSet edge[50];

    Create();
    Prim();

  //  CreateEdge(edge);
  //  Kruskal_Min_Tree(edge,n2);

    return 0;
}

//输入权值矩阵
void Create()
{
    int a;
    int i,j;
    cout<<"请输入顶点数：";
    cin>>n;
    cout<<"请输入各顶点信息：";
    for(i=0;i<n;i++)
    {
        cin>>data[i];
    }
    cout<<"请输入各边权值（“99999”表示无穷大）："<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>a;
            c[i][j]=a;
        }
    }
    //打印矩阵
    cout<<"矩阵为："<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cout<<c[i][j]<<"    ";
        }
        cout<<endl;
    }
}

void Prim()
{
    int lowcost[n];
    int closset[n];
    int i,j,k;
    int min;
    for(i=1;i<=n;i++)              //初始化为第一个
    {
        lowcost[i]=c[0][i];
        closset[i]=0;
    }

    for(i=1;i<n;i++)
    {
        min=lowcost[i];
        k=i;        //k记录最小的下标
        for(j=1;j<n;j++)       //找最小
        {
            if(lowcost[j]<min)
            {
                min=lowcost[j];
                k=j;
            }
        }//cout<<min;
        //cout<<"("<<k<<","<<closset[k]<<")"<<endl;
        cout<<"("<<closset[k]<<","<<k<<")"<<endl;
        lowcost[k]=infinity;   //加入

        for(j=1;j<=n;j++)
        {
            if(c[k][j]<lowcost[j]&&lowcost[j]<infinity)    //更新找最小
            {
                lowcost[j]=c[k][j];
                closset[j]=k;
            }
        }
    }
}


void Kruskal_Min_Tree(EdgeSet edge[],int n)
{
    int i;
    int bnf,edf;
    int parents[100];
    CreateEdge(edge);
    Sort(edge);

    //初始化
    for(i=0;i<n;i++)
    {
        parents[i]=i;
    }

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
        for(j=0;j<e;j++)
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
