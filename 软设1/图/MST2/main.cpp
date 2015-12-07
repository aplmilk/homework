#include <iostream>

using namespace std;

char data[50]; //��¼������Ϣ
int c[50][50];//��¼����Ȩֵ
int n; //��¼����(prim)
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

//����Ȩֵ����
void Create()
{
    int a;
    int i,j;
    cout<<"�����붥������";
    cin>>n;
    cout<<"�������������Ϣ��";
    for(i=0;i<n;i++)
    {
        cin>>data[i];
    }
    cout<<"���������Ȩֵ����99999����ʾ����󣩣�"<<endl;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cin>>a;
            c[i][j]=a;
        }
    }
    //��ӡ����
    cout<<"����Ϊ��"<<endl;
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
    for(i=1;i<=n;i++)              //��ʼ��Ϊ��һ��
    {
        lowcost[i]=c[0][i];
        closset[i]=0;
    }

    for(i=1;i<n;i++)
    {
        min=lowcost[i];
        k=i;        //k��¼��С���±�
        for(j=1;j<n;j++)       //����С
        {
            if(lowcost[j]<min)
            {
                min=lowcost[j];
                k=j;
            }
        }//cout<<min;
        //cout<<"("<<k<<","<<closset[k]<<")"<<endl;
        cout<<"("<<closset[k]<<","<<k<<")"<<endl;
        lowcost[k]=infinity;   //����

        for(j=1;j<=n;j++)
        {
            if(c[k][j]<lowcost[j]&&lowcost[j]<infinity)    //��������С
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

    //��ʼ��
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
    cout<<"�����붥�����ͱ�����";
    cin>>n2>>e;
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
        for(j=0;j<e;j++)
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
