#include <iostream>

using namespace std;

//边节点
typedef struct node
{
    int adjvex;
    struct node *next;
}node;

//头结点
typedef struct Vertexnode
{
    char vertex;
    node *firstedge;
}Vertexnode;

//链接表
typedef struct AdjGraph
{
    Vertexnode vexlist[50];
    int n,e;
} AdjGraph;

int Count;
int dfn[50];
int low[50];

AdjGraph CreateGraph(AdjGraph G);
void FindArticul(AdjGraph G,int dfn[]);
void DFSArticul(AdjGraph G,int v,int dfn[],int low[]);

int main()
{
    int i;
    AdjGraph *G=new AdjGraph;
    *G=CreateGraph(*G);
     //打印链接表
    for(i=0;i<G->n;i++)
    {
        node *t=new node;
        t=G->vexlist[i].firstedge;
        cout<<G->vexlist[i].vertex<<"->";
        //cout<<"ts";
        //cout<<t->adjvex;
        while(t!=NULL)
        {
            cout<<t->adjvex<<"->";
            t=t->next;
        }
        cout<<"NULL"<<endl;
    }
    FindArticul(*G,dfn);
    return 0;
}


AdjGraph CreateGraph(AdjGraph G)
{
    int i;
    int head,tail;
    cout<<"请输入图的顶点数和边数：";
    cin>>G.n>>G.e;
    cout<<"请输入各点信息：";
    for(i=0; i<G.n; i++)
    {
        cin>>G.vexlist[i].vertex;
        G.vexlist[i].firstedge=NULL;  //后继初始化为空
    }
    cout<<"请输入各点的链接信息(序号表示):";
    for(i=0; i<G.e; i++)
    {
        cin>>head>>tail;
        node *p=new node;
        p->adjvex=tail;
        p->next=G.vexlist[head].firstedge;
        G.vexlist[head].firstedge=p; //cout<<"!!"<<p->adjvex<<endl;
        //无向图反向加入
        node *q=new node;
        q->adjvex=head;
        q->next=G.vexlist[tail].firstedge;
        G.vexlist[tail].firstedge=q;
    }
    //打印链接表
 /*   for(i=0;i<G.n;i++)
    {
        node *t=new node;
        t=G.vexlist[i].firstedge;
        cout<<G.vexlist[i].vertex<<"->";
        //cout<<"ts";
        //cout<<t->adjvex;
        while(t!=NULL)
        {
            cout<<t->adjvex<<"->";
            t=t->next;
        }
        cout<<"NULL"<<endl;
    }*/
    return G;
}



void FindArticul(AdjGraph G,int dfn[])
{
    /* 连通图G 以邻接表作存储结构，查找并输出G上全部关节点*/
    int i;
    node *p=new node;
    int v;
    Count=2; /* 全局变量count用于对访问计数*/
    dfn[0]=1; //设定邻接表上0号顶点为生成树的根
    low[0]=1;
    for(i=1; i<G.n; ++i)
    {
        dfn[i]=0;   //未访问初始化为0，dfn[]兼职visited[]
    }

    p=G.vexlist[0].firstedge;
    v=p->adjvex;    //cout<<v<<"ts"<<p->adjvex<<"!!"<<endl;
    cout<<"关节点为：";
    DFSArticul(G,v,dfn,low); //从顶点v 出发深度优先查找关节点
    if(Count<=G.n)    /* 生成树的根至少有两棵子树*/
    {
        cout<<G.vexlist[0].vertex; /* 根是关节点，输出*/
        while(p->next!=NULL)
        {
            p=p->next;
            v=p->adjvex;
            if(dfn[v]==0)  DFSArticul(G,v,dfn,low);
            }
    }
}


/* 从顶点v0 出发深度优先遍历图G，计算low [] ，查找并输出关节点*/
void DFSArticul(AdjGraph G,int v,int dfn[],int low[])
{
    int w,min;
    dfn[v]=Count;   //v0是第count个访问的顶点
    min=Count;    //最小值初始化为先深次序
    Count++;

    node *p=new node;
    for(p=G.vexlist[v].firstedge;p!=NULL;p=p->next)    // 对v0 的每个邻接点检查
    {
        w=p->adjvex ;
        if(dfn[w]==0)       //若w未曾访问，则w为v0的孩子(因为无向图也与父亲相连)
        {
            DFSArticul(G,w,dfn,low);        //返回前求得low[w]
            if(low[w]<min)    min=low[w];
            if(low[w]>=dfn[v]) cout<<G.vexlist[v].vertex; //输出关节点
        }
        else if(dfn[w]<min)    min=dfn[w];   //已访问为祖先
    }
    low[v]=min;
    }
