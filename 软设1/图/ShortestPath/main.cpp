#include <iostream>

using namespace std;

char data[50];
int c[50][50];
int n;  //顶点数

const int infinity=99999;

void Create();
void Dijkstra(int D[],int P[],int S[]);
int MinCost(int D[],int S[]);
void Floyd(int D[],int P[]);


int main()
{
    int D[50]; //存最短路径长度
    int P[50]; //存最后经过的点
    int S[50]; //判断是否加入，TRUE为1FALSE为0
    Create();
    Dijkstra(D,P,S);
//    Floyd(D,P);
    return 0;
}

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

void Dijkstra(int D[],int p[],int S[])
{
    int w;
    int sum;
    int i,v;
    for(i=0;i<n;i++)       //初始化最短距离为0到各个点
    {
        D[i]=c[0][i];
        p[i]=0;
        S[i]=0;
    }
    S[0]=1;         //加入第一个结点

    for(i=1;i<n;i++)
    {
        w=MinCost(D,S);
        S[w]=1;     //标记为已加入
        for(v=1;v<n;v++)
        {
            if(S[v]==0)     //点v未加入，更新D[]
            {
                sum=D[w]+c[w][v];
                if(sum<D[v])
                {
                    D[v]=sum;
                    p[v]=w;     //通过了新的点更新P[]
                }
            }
        }
    }
    //打印最短距离
    cout<<"各点最短距离："<<endl;
    for(i=1;i<n;i++)
    {
        cout<<i<<"点： "<<D[i]<<"   ";
        v=i;
        cout<<v<<"<-";
        while(p[v]!=0)
        {
            v=p[v];
            cout<<v<<"<-";
        }
        cout<<p[v]<<endl;
    }
}

int MinCost(int D[],int S[])
{
    int i;
    int w=1;
    int temp=infinity;
    for(i=1;i<=n;i++)
    {
        if(S[i]==0&&D[i]<temp)
        {
            temp=D[i];
            w=i;
        }
    }
    return w;   //返回最小值的下标
}
/*
void Floyd(int D[],int P[])
{
    int i,j,k;
    int flag=0;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            D[i][j]=c[i][j];
            P[i][j]=-1;
        }
    }

    for(k=0;k<n;k++)
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(D[i][k]+D[k][j]<D[i][j])
                {
                    D[i]][j]=D[i][k]+A[k][j];
                    P[i][j]=k;
                }
            }
        }
    }

    //判断负环
    for(k=0;k<n;k++)
    {
        if(D[k][k]<0)
        {
            flag=1;
            cout<<"存在负环"<<endl;
            break;
        }
    }
    if(flag==0)
    {

    }
}
*/
