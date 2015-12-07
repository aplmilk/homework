#include <iostream>

using namespace std;

char data[50];
int c[50][50];
int n;

void Create();
void Floyd();

int main()
{

    Create();
    Floyd();
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

void Floyd()
{
    int begin,end;
    int i,j,k;
    int flag=0;
    int D[50][50]; //存最短路径长度
    int P[50][50]; //存最后经过的点
 //   int S[50]; //判断是否加入，TRUE为1FALSE为0
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)    //初始化i到j最短距离
        {
            D[i][j]=c[i][j];
            P[i][j]=-1;
        }
    }

    for(k=0;k<n;k++)        //k为松弛的点
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)    //i,j为两点
            {
                if(D[i][k]+D[k][j]<D[i][j])
                {
                    D[i][j]=D[i][k]+D[k][j];
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
        cout<<"输入要查找的最短路径的起点和终点：";
        cin>>begin>>end;
        cout<<"路径总和："<<D[begin][end]<<" ";
        cout<<end<<"<-";
        i=begin;
        j=end;
        while(P[i][j]!=-1)
        {
            cout<<P[i][j];
            j=k;
        }
        cout<<begin<<endl;
    }
}

