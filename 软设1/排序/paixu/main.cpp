#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<ctime>

using namespace std;

int normal[1500],zheng[1500],ni[1500],bigdata[15000];  //һ������1500������,������15000������


void Create(int normal[],int zheng[],int ni[],int bigdata[]);   //�������ڴ�����
void CountingSort(int info[],int k,int n);  //kΪ���鳤�ȣ�nΪ���ݸ���
void radixsort(int data[], int n,int range,int k);


int main()
{
    //Create(normal,zheng,ni,bigdata);
    //��������
    cout << "��������" <<endl<<endl;
    cout << "һ�����ݣ�" ;
    CountingSort(normal,1000,1500);
    cout << "����" ;
    CountingSort(zheng,1000,1500);
    cout << "����" ;
    CountingSort(ni,1000,1500);
    cout << "�����ݣ�" ;
    CountingSort(bigdata,10000,15000);
    cout<<endl;

/*
    //Ͱ����
    cout << "Ͱ����" <<endl<<endl;
    cout << "һ�����ݣ�" ;
    cout << "����" ;
    cout << "����" ;
    cout << "�����ݣ�" ;
    cout<<endl;
*/
    //��������
    cout << "��������" <<endl<<endl;
    cout << "һ�����ݣ�" ;
    radixsort(normal,1500, 1000,3);
    cout << "����" ;
    radixsort(zheng, 1500, 1000,3);
    cout << "����" ;
    radixsort(ni,  1500, 1000,3);
    cout << "�����ݣ�" ;
    radixsort(bigdata, 15000, 10000,4);
    cout<<endl;
    return 0;
}

void Create(int normal[],int zheng[],int ni[],int bigdata[])
{
    int i;
    int data;
    srand(time(NULL));

    //�����ʼ��
    for(i=0;i<1500;i++)
    {
        normal[i]=0;
        zheng[i]=0;
        ni[i]=0;
        bigdata[i]=0;
    }
    for(;i<15000;i++)
    {
        bigdata[i]=0;
    }

    //һ������
    for(i=0;i<1500;i++)
    {
      data=rand()%1000;  //100�������ȡ150����
      normal[i]=data;//cout<<normal[i]<<" ";
    }
//cout<<endl;
    //����
    zheng[0]=rand()%2;  //��С����0-1֮��
    for(i=1;i<1500;i++)
    {
        data=rand()%2;
        zheng[i]=zheng[i-1]+data;//cout<<zheng[i]<<" ";
    }
//cout<<endl;
    //����
    ni[0]=rand()%50+950;     //�����������950-1000֮��
    for(i=1;i<1500;i++)
    {
        data=rand()%2;
        ni[i]=ni[i-1]-data;//cout<<ni[i]<<" ";
    }
//cout<<endl;
    //������
    for(i=0;i<15000;i++)
    {
      data=rand()%10000;  //10000�������ȡ15000����
      bigdata[i]=data;//cout<<bigdata[i]<<" ";
    }
}

void CountingSort(int info[],int k,int n)
{
    int e;
    int i,j;
    int a[k],c[k];  //��������
    double t1,t2,t;

    t1=clock();
for(e=0;e<1000;e++)
{
    for(i=0;i<n;i++)
    {
        info[i]=rand()%k;
    }

    //��ʼ��
    for(i=0;i<k;i++)
    {
        a[i]=0;
    }

    //��¼����
    for(i=0;i<n;i++)
    {
        a[info[i]]++;
    }

    //����仯
    for(i=1;i<k;i++)
    {
        a[i]=a[i-1]+a[i];
    }

    //����������
    for(i=0,j=0;i<k;i++)
    {
        for(;j<a[i]-1;j++)
        {
            c[j]=i;
        }

    }
}
    t2=clock();
    t=(t2-t1)/CLOCKS_PER_SEC;//cout<<t1<<"    "<<t2<<endl;
    cout<<"ʱ�䣺"<<t<<"s  "<<endl;
}


//��������
void radixsort(int data[], int n,int range,int d)   //nΪ���ݴ�С��kΪ��λ
{

    int tmp[n];
    int count[10];   //������(0-9)
    int i, j, k,e;
    int radix ;
    srand(time(NULL));
    double t1,t2,t;

    t1=clock();

for(e=0;e<1000;e++)
{
    radix=1;
    for(i=0;i<n;i++)
    {
        data[i]=rand()%range;
    }

    for(i = 1; i <= d; i++) //����d������
    {
        for(j = 0; j < 10; j++)
            {
              count[j] = 0; //��ʼ��������
            }

        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ

        for(j = n - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }

        for(j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�data��
            {
              data[j] = tmp[j];
            }
        radix = radix * 10;
    }
}
    t2=clock();
    t=(t2-t1)/CLOCKS_PER_SEC;   //cout<<t1<<"    "<<t2<<endl;
    cout<<"ʱ�䣺"<<t<<"s  "<<endl;
}
