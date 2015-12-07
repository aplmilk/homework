#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<ctime>

using namespace std;

int normal[1500],zheng[1500],ni[1500],bigdata[15000];  //一般数据1500个数据,大数据15000个数据


void Create(int normal[],int zheng[],int ni[],int bigdata[]);   //往数组内存数据
void CountingSort(int info[],int k,int n);  //k为数组长度，n为数据个数
void radixsort(int data[], int n,int range,int k);


int main()
{
    //Create(normal,zheng,ni,bigdata);
    //计数排序
    cout << "计数排序：" <<endl<<endl;
    cout << "一般数据：" ;
    CountingSort(normal,1000,1500);
    cout << "正序：" ;
    CountingSort(zheng,1000,1500);
    cout << "逆序：" ;
    CountingSort(ni,1000,1500);
    cout << "大数据：" ;
    CountingSort(bigdata,10000,15000);
    cout<<endl;

/*
    //桶排序
    cout << "桶排序：" <<endl<<endl;
    cout << "一般数据：" ;
    cout << "正序：" ;
    cout << "逆序：" ;
    cout << "大数据：" ;
    cout<<endl;
*/
    //基数排序
    cout << "基数排序：" <<endl<<endl;
    cout << "一般数据：" ;
    radixsort(normal,1500, 1000,3);
    cout << "正序：" ;
    radixsort(zheng, 1500, 1000,3);
    cout << "逆序：" ;
    radixsort(ni,  1500, 1000,3);
    cout << "大数据：" ;
    radixsort(bigdata, 15000, 10000,4);
    cout<<endl;
    return 0;
}

void Create(int normal[],int zheng[],int ni[],int bigdata[])
{
    int i;
    int data;
    srand(time(NULL));

    //数组初始化
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

    //一般数据
    for(i=0;i<1500;i++)
    {
      data=rand()%1000;  //100以内随机取150个数
      normal[i]=data;//cout<<normal[i]<<" ";
    }
//cout<<endl;
    //正序
    zheng[0]=rand()%2;  //最小数在0-1之间
    for(i=1;i<1500;i++)
    {
        data=rand()%2;
        zheng[i]=zheng[i-1]+data;//cout<<zheng[i]<<" ";
    }
//cout<<endl;
    //逆序
    ni[0]=rand()%50+950;     //最大数控制在950-1000之间
    for(i=1;i<1500;i++)
    {
        data=rand()%2;
        ni[i]=ni[i-1]-data;//cout<<ni[i]<<" ";
    }
//cout<<endl;
    //大数据
    for(i=0;i<15000;i++)
    {
      data=rand()%10000;  //10000以内随机取15000个数
      bigdata[i]=data;//cout<<bigdata[i]<<" ";
    }
}

void CountingSort(int info[],int k,int n)
{
    int e;
    int i,j;
    int a[k],c[k];  //辅助数组
    double t1,t2,t;

    t1=clock();
for(e=0;e<1000;e++)
{
    for(i=0;i<n;i++)
    {
        info[i]=rand()%k;
    }

    //初始化
    for(i=0;i<k;i++)
    {
        a[i]=0;
    }

    //记录数据
    for(i=0;i<n;i++)
    {
        a[info[i]]++;
    }

    //数组变化
    for(i=1;i<k;i++)
    {
        a[i]=a[i-1]+a[i];
    }

    //储存排序结果
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
    cout<<"时间："<<t<<"s  "<<endl;
}


//基数排序
void radixsort(int data[], int n,int range,int d)   //n为数据大小，k为数位
{

    int tmp[n];
    int count[10];   //计数器(0-9)
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

    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            {
              count[j] = 0; //初始化计数器
            }

        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶

        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }

        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            {
              data[j] = tmp[j];
            }
        radix = radix * 10;
    }
}
    t2=clock();
    t=(t2-t1)/CLOCKS_PER_SEC;   //cout<<t1<<"    "<<t2<<endl;
    cout<<"时间："<<t<<"s  "<<endl;
}
