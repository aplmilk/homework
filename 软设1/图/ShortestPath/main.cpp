#include <iostream>

using namespace std;

char data[50];
int c[50][50];
int n;  //������

const int infinity=99999;

void Create();
void Dijkstra(int D[],int P[],int S[]);
int MinCost(int D[],int S[]);
void Floyd(int D[],int P[]);


int main()
{
    int D[50]; //�����·������
    int P[50]; //����󾭹��ĵ�
    int S[50]; //�ж��Ƿ���룬TRUEΪ1FALSEΪ0
    Create();
    Dijkstra(D,P,S);
//    Floyd(D,P);
    return 0;
}

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

void Dijkstra(int D[],int p[],int S[])
{
    int w;
    int sum;
    int i,v;
    for(i=0;i<n;i++)       //��ʼ����̾���Ϊ0��������
    {
        D[i]=c[0][i];
        p[i]=0;
        S[i]=0;
    }
    S[0]=1;         //�����һ�����

    for(i=1;i<n;i++)
    {
        w=MinCost(D,S);
        S[w]=1;     //���Ϊ�Ѽ���
        for(v=1;v<n;v++)
        {
            if(S[v]==0)     //��vδ���룬����D[]
            {
                sum=D[w]+c[w][v];
                if(sum<D[v])
                {
                    D[v]=sum;
                    p[v]=w;     //ͨ�����µĵ����P[]
                }
            }
        }
    }
    //��ӡ��̾���
    cout<<"������̾��룺"<<endl;
    for(i=1;i<n;i++)
    {
        cout<<i<<"�㣺 "<<D[i]<<"   ";
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
    return w;   //������Сֵ���±�
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

    //�жϸ���
    for(k=0;k<n;k++)
    {
        if(D[k][k]<0)
        {
            flag=1;
            cout<<"���ڸ���"<<endl;
            break;
        }
    }
    if(flag==0)
    {

    }
}
*/
