#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<ctime>

using namespace std;

int Partition(int data[], int low, int high);
int Qsort(int data[], int low, int high);
int PrePartition(int data[], int low, int high);
int PreQsort(int data[], int low, int high);


int main()
{
    int data[100000];
    int i;
    int x;
    double t1,t2,t;
    srand(time(NULL));

    for(i=0;i<100000;i++)
    {
        data[i]=0;    //��ʼ��
    }

    for(i=0;i<100000;i++)
    {
        data[i]=rand()%200000;    //100���ڵ���
    }

    cout<<"ԭ����";
    t1=clock();
    for(x=0;x<10;x++)
    {
    PreQsort(data, 0,19999);
    }
    t2=clock();
    t=(t2-t1)/CLOCKS_PER_SEC;
    cout<<"ʱ�䣺"<<t<<"s  "<<endl;

    cout<<"�Ľ���";
    t1=clock();
    for(x=0;x<10;x++)
    {
    Qsort(data, 0, 19999);
    }
    t2=clock();
    t=(t2-t1)/CLOCKS_PER_SEC;
    cout<<"ʱ�䣺"<<t<<"s  "<<endl;


    return 0;
}


int Qsort(int data[], int low, int high)
{
    int pivot;
    while (low < high)
    {
        pivot = Partition(data, low, high); //�һ�׼�����ֳ����飬���ػ�׼���м�ֵ��
        Qsort(data, low, pivot - 1);
        low = pivot + 1;
        //Qsort(data, pivot + 1, high);
    }

    return 0;
}


int Partition(int data[], int low, int high)  //ѡ��׼
{
    int pivot;
    int k,temp;

    //��ƽ������ѡ��С
    k=(high-low)/2+low; //�м���
    if(data[k]<data[low])
    {
        temp=data[low];
        data[low]=data[k];
        data[k]=temp;
    }
    if(data[high]<data[low])  //data[low]��С
    {
        temp=data[low];
        data[low]=data[high];
        data[high]=temp;
    }

    if(data[k]<data[high])  //data[k]Ϊ��ֵ
    {
        temp=data[low];
        data[low]=data[k];
        data[k]=temp;
    }
    else            //data[high]Ϊ��ֵ
    {
        temp=data[low];
        data[low]=data[high];
        data[high]=temp;
    }
//cout<<data[low]<<"  "<<data[k]<<"  "<<data[high]<<endl;
    pivot=data[low];

    while (low < high)
    {
        while(low < high && data[high] >= pivot)    //(����)�ҵ�һ��С�ڻ�׼����
        {
            high--;
        }
        data[low] = data[high]; //��Ϊ��ʱlow�ǻ�׼ֵ���ѱ������ֱ�Ӹģ�=�����С�൱�ڽ�����

        while(low < high && data[low] <= pivot)     //(����)�ҵ�һ�����ڻ�׼����
        {
            low++;
        }
        data[high] = data[low];
    }
    data[low] = pivot;          //��׼ֵ���м��

    return low;
}

int PreQsort(int data[], int low, int high)
{
    int pivot;
    while (low < high)
    {
        pivot = PrePartition(data, low, high); //�һ�׼�����ֳ����飬���ػ�׼���м�ֵ��
        Qsort(data, low, pivot - 1);
        low=pivot+1;
        //Qsort(data, pivot+1,high);
    }

    return 0;
}


int PrePartition(int data[], int low, int high)  //ѡ��׼
{
    int pivot;
    //int temp;
    pivot=data[low];

    while (low < high)
    {
        while(low < high && data[high] >= pivot)    //(����)�ҵ�һ��С�ڻ�׼����
        {
            high--;
        }
        data[low] = data[high];

        while(low < high && data[low] <= pivot)     //(����)�ҵ�һ�����ڻ�׼����
        {
            low++;
        }
        data[high] = data[low];
    }
    data[low] = pivot;          //��׼ֵ���м��

    return low;
}

