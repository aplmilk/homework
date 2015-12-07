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
        data[i]=0;    //初始化
    }

    for(i=0;i<100000;i++)
    {
        data[i]=rand()%200000;    //100以内的数
    }

    cout<<"原来：";
    t1=clock();
    for(x=0;x<10;x++)
    {
    PreQsort(data, 0,19999);
    }
    t2=clock();
    t=(t2-t1)/CLOCKS_PER_SEC;
    cout<<"时间："<<t<<"s  "<<endl;

    cout<<"改进：";
    t1=clock();
    for(x=0;x<10;x++)
    {
    Qsort(data, 0, 19999);
    }
    t2=clock();
    t=(t2-t1)/CLOCKS_PER_SEC;
    cout<<"时间："<<t<<"s  "<<endl;


    return 0;
}


int Qsort(int data[], int low, int high)
{
    int pivot;
    while (low < high)
    {
        pivot = Partition(data, low, high); //找基准，并分成两组，返回基准（中间值）
        Qsort(data, low, pivot - 1);
        low = pivot + 1;
        //Qsort(data, pivot + 1, high);
    }

    return 0;
}


int Partition(int data[], int low, int high)  //选基准
{
    int pivot;
    int k,temp;

    //三平均分区选最小
    k=(high-low)/2+low; //中间数
    if(data[k]<data[low])
    {
        temp=data[low];
        data[low]=data[k];
        data[k]=temp;
    }
    if(data[high]<data[low])  //data[low]最小
    {
        temp=data[low];
        data[low]=data[high];
        data[high]=temp;
    }

    if(data[k]<data[high])  //data[k]为中值
    {
        temp=data[low];
        data[low]=data[k];
        data[k]=temp;
    }
    else            //data[high]为中值
    {
        temp=data[low];
        data[low]=data[high];
        data[high]=temp;
    }
//cout<<data[low]<<"  "<<data[k]<<"  "<<data[high]<<endl;
    pivot=data[low];

    while (low < high)
    {
        while(low < high && data[high] >= pivot)    //(从右)找第一个小于基准的数
        {
            high--;
        }
        data[low] = data[high]; //因为此时low是基准值，已保存可以直接改（=最高最小相当于交换）

        while(low < high && data[low] <= pivot)     //(从左)找第一个大于基准的数
        {
            low++;
        }
        data[high] = data[low];
    }
    data[low] = pivot;          //基准值往中间调

    return low;
}

int PreQsort(int data[], int low, int high)
{
    int pivot;
    while (low < high)
    {
        pivot = PrePartition(data, low, high); //找基准，并分成两组，返回基准（中间值）
        Qsort(data, low, pivot - 1);
        low=pivot+1;
        //Qsort(data, pivot+1,high);
    }

    return 0;
}


int PrePartition(int data[], int low, int high)  //选基准
{
    int pivot;
    //int temp;
    pivot=data[low];

    while (low < high)
    {
        while(low < high && data[high] >= pivot)    //(从右)找第一个小于基准的数
        {
            high--;
        }
        data[low] = data[high];

        while(low < high && data[low] <= pivot)     //(从左)找第一个大于基准的数
        {
            low++;
        }
        data[high] = data[low];
    }
    data[low] = pivot;          //基准值往中间调

    return low;
}

