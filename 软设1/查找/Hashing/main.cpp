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
     cout<<"填充因子：30%     数据规模：3000    数据分布：均匀     ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,3000,1);
    //2
    cout<<"填充因子：50%     数据规模：5000    数据分布：均匀     ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,5000,1);

    //3
    cout<<"填充因子：70%     数据规模：7000    数据分布：均匀     ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,7000,1);
cout<<endl;

    //4
    cout<<"填充因子：30%     数据规模：30000    数据分布：均匀   ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,30000,1);
    //5
    cout<<"填充因子：50%     数据规模：50000    数据分布：均匀   ";
    Creat_Search(Hashlarge,100000,50000,1);
    //6
    cout<<"填充因子：70%     数据规模：70000    数据分布：均匀   ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,70000,1);
cout<<endl;

    //7
    cout<<"填充因子：30%     数据规模：3000    数据分布：不均匀  ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,3000,2);
    //8
    cout<<"填充因子：50%     数据规模：5000    数据分布：不均匀  ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,5000,2);
    //9
    cout<<"填充因子：70%     数据规模：7000    数据分布：不均匀  ";
    MakeNull(Hash,10000);
    Creat_Search(Hash,10000,7000,2);
cout<<endl;

    //10
    cout<<"填充因子：30%     数据规模：30000    数据分布：不均匀  ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,30000,2);

    //11
    cout<<"填充因子：50%     数据规模：50000    数据分布：不均匀  ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,50000,2);
    //12
    cout<<"填充因子：70%     数据规模：70000    数据分布：不均匀  ";
    MakeNull(Hashlarge,100000);
    Creat_Search(Hashlarge,100000,70000,2);

    return 0;
}

void MakeNull(long Hash[],int n)  //n为表长
{
    int i;
    for(i=0;i<n;i++)
    {
        Hash[i]=0;
    }
}

void Creat_Search(long Hash[],int n,int k,int choice)  //n为表长,k为数据个数
{
    double t1,t2,t;
    int a,b;
    int i;
    srand(time(NULL));
     //建表
     if(choice==1)
     {
        for(i=0;i<k;i++) //第一个取填充因子为30%,分步随机
        {
            a=rand()%n;
            if(Hash[a]==0) Hash[a]=a;
            else            //线性再散列处理冲突
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
         for(i=0;i<k;i++) //第一个取填充因子为30%,分步随机
        {
            if(i<k/3)   a=rand()%(n/2);    //有1/3的数据在表的前半部分
            else    a=rand()%(n/2)+n/2;         //2/3数据在表的后半部分

            if(Hash[a]==0) Hash[a]=a;
            else            //线性再散列处理冲突
            {
                b=a+1;
                while(Hash[b]!=0) b++;
                Hash[b]=a;
            }
        }
     }
	//查找
    t1=clock();
	for(i=0;i<1000;i++) //随机找100个数
	{
	  a=rand()%n;
	  if(Hash[a]==0) ;  //不存在
	  else if (Hash[a]==a) ; //找到
	  else
	  {
	      b=a+1;
	      while(Hash[b]!=a)  //b=a则已循环找了一圈，不存在
	      {
	          if(b==a) break;
	          if(b==n) b=0;
	          else  b++;
	      }
	  }
	}
	t2=clock();
	t=(t2-t1)/CLOCKS_PER_SEC;
	cout<<"时间："<<t<<"s"<<endl;
}
