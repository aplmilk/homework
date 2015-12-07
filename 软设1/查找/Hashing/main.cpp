#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<ctime>

using namespace std;

void Creat_Search(long Hash[],int n,int k,int choice);
void MakeNull(long Hash[],int n);

int main()
{
    long Hashlarge[100000];
    long Hash[10000];
    //1
     cout<<"������ӣ�30%     ���ݹ�ģ��3000    ���ݷֲ�������     ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,3000,1);
    //2
    cout<<"������ӣ�50%     ���ݹ�ģ��5000    ���ݷֲ�������     ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,5000,1);

    //3
    cout<<"������ӣ�70%     ���ݹ�ģ��7000    ���ݷֲ�������     ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,7000,1);
cout<<endl;

    //4
    cout<<"������ӣ�30%     ���ݹ�ģ��30000    ���ݷֲ�������   ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,30000,1);
    //5
    cout<<"������ӣ�50%     ���ݹ�ģ��50000    ���ݷֲ�������   ";
    Creat_Search(Hashlarge,100000,50000,1);
    //6
    cout<<"������ӣ�70%     ���ݹ�ģ��70000    ���ݷֲ�������   ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,70000,1);
cout<<endl;

    //7
    cout<<"������ӣ�30%     ���ݹ�ģ��3000    ���ݷֲ���������  ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,3000,2);
    //8
    cout<<"������ӣ�50%     ���ݹ�ģ��5000    ���ݷֲ���������  ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,5000,2);
    //9
    cout<<"������ӣ�70%     ���ݹ�ģ��7000    ���ݷֲ���������  ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,7000,2);
cout<<endl;

    //10
    cout<<"������ӣ�30%     ���ݹ�ģ��30000    ���ݷֲ���������  ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,30000,2);

    //11
    cout<<"������ӣ�50%     ���ݹ�ģ��50000    ���ݷֲ���������  ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,50000,2);
    //12
    cout<<"������ӣ�70%     ���ݹ�ģ��70000    ���ݷֲ���������  ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,70000,2);

    return 0;
}

void MakeNull(long Hash[],int n)  //nΪ��
{
    int i;
    for(i=0;i<n;i++)
    {
        Hash[i]=0;
    }
}

void Creat_Search(long Hash[],int n,int k,int choice)  //nΪ��,kΪ���ݸ���
{
    double t1,t2,t;
    int a,b;
    int i;
    srand(time(NULL));
     //����
     if(choice==1)
     {
        for(i=0;i<k;i++) //��һ��ȡ�������Ϊ30%,�ֲ����
        {
            a=rand()%n;
            if(Hash[a]==0) Hash[a]=a;
            else            //������ɢ�д����ͻ
            {
                b=a+1;
                while(Hash[b]!=0)
                {
                    if(b==n) b=0;
                    else b++;
                }
                Hash[b]=a;
            }
        }
     }
     else if(choice==2)
     {
         for(i=0;i<k;i++) //��һ��ȡ�������Ϊ30%,�ֲ����
        {
            if(i<k/3)   a=rand()%(n/2);    //��1/3�������ڱ��ǰ�벿��
            else    a=rand()%(n/2)+n/2;         //2/3�����ڱ�ĺ�벿��

            if(Hash[a]==0) Hash[a]=a;
            else            //������ɢ�д����ͻ
            {
                b=a+1;
                while(Hash[b]!=0) b++;
                Hash[b]=a;
            }
        }
     }
	//����
    t1=clock();
	for(i=0;i<1000;i++) //�����100����
	{
	  a=rand()%n;
	  if(Hash[a]==0) ;  //������
	  else if (Hash[a]==a) ; //�ҵ�
	  else
	  {
	      b=a+1;
	      while(Hash[b]!=a)  //b=a����ѭ������һȦ��������
	      {
	          if(b==a) break;
	          if(b==n) b=0;
	          else  b++;
	      }
	  }
	}
	t2=clock();
	t=(t2-t1)/CLOCKS_PER_SEC;
	cout<<"ʱ�䣺"<<t<<"s"<<endl;
}
