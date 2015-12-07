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

void Floyd()
{
    int begin,end;
    int i,j,k;
    int flag=0;
    int D[50][50]; //�����·������
    int P[50][50]; //����󾭹��ĵ�
 //   int S[50]; //�ж��Ƿ���룬TRUEΪ1FALSEΪ0
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)    //��ʼ��i��j��̾���
        {
            D[i][j]=c[i][j];
            P[i][j]=-1;
        }
    }

    for(k=0;k<n;k++)        //kΪ�ɳڵĵ�
    {
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)    //i,jΪ����
            {
                if(D[i][k]+D[k][j]<D[i][j])
                {
                    D[i][j]=D[i][k]+D[k][j];
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
        cout<<"����Ҫ���ҵ����·���������յ㣺";
        cin>>begin>>end;
        cout<<"·���ܺͣ�"<<D[begin][end]<<" ";
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

