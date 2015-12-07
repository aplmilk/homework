#include <iostream>

using namespace std;

//边节点
typedef struct ArcBox
{
    int tailvex,headvex;
    struct ArcBox *hlink,*tlink;    //弧头或弧尾相同的弧的链域
}ArcBox;

//头结点
typedef struct VexNode
{
    char data;
    ArcBox *firstin,*firstout;   //该顶点第一条出/入弧
}VexNode;

//十字链表
typedef struct OLGraph
{
    VexNode xlist[50];
    int vexnum,arcnum;  //顶点数和弧数
}OLGraph;

int dfn[50];
int Visited[50];      //1为TRUE,0为FALSE
int Count=0;

void CreateGraph(OLGraph *G);
void DFS(OLGraph *G,int v);
void Rev_DFS(OLGraph *G,int v);
void Strongly_Connected_Component(OLGraph *G);


int main()
{
    OLGraph *G=new OLGraph;
    CreateGraph(G);
    Strongly_Connected_Component(G);

    return 0;
}

//建立有向图
void CreateGraph(OLGraph *G)
{
    int i,k;
    int head,tail;   //一条弧的起点和终点
    cout<<"请输入有向图的顶点数和边数：";
    cin>>G->vexnum>>G->arcnum;
    cout<<"请输入各点顶点值：";
    for(i=0;i<G->vexnum;i++)
    {
        cin>>G->xlist[i].data;
        G->xlist[i].firstin=NULL; //初始化
        G->xlist[i].firstout=NULL;
    }
    cout<<"请输入各弧起点、终点(序号表示)：";
    for(k=0;k<G->arcnum;k++)
    {
        cin>>head>>tail;
        //正向
        ArcBox *p=new ArcBox;
        p->tailvex=tail;
        p->tlink=G->xlist[head].firstout;
        G->xlist[head].firstout=p;
        //逆向
        ArcBox *q=new ArcBox;
        q->headvex=head;
        q->hlink=G->xlist[tail].firstin;
        G->xlist[tail].firstin=q;
    }

    //打印正向链接表
    cout<<"正链表："<<endl;
    for(i=0;i<G->vexnum;i++)
    {
        ArcBox *t=new ArcBox;
        t=G->xlist[i].firstout;
        cout<<G->xlist[i].data<<"->";
        while(t!=NULL)
        {
            cout<<t->tailvex<<"->";
            t=t->tlink;
        }
        cout<<"NULL"<<endl;
    }

    //打印逆向链接表
    cout<<"逆链表："<<endl;
    for(i=0;i<G->vexnum;i++)
    {
        ArcBox *t=new ArcBox;
        t=G->xlist[i].firstin;
        cout<<G->xlist[i].data<<"->";
        while(t!=NULL)
        {
            cout<<t->headvex<<"->";
            t=t->hlink;
        }
        cout<<"NULL"<<endl;
    }
}

void Strongly_Connected_Component(OLGraph *G)
{
    int k=1,v,j;
    for(v=0;v<G->vexnum;v++)
    {
        Visited[v]=0;          //初始化
    }

    //对图正向遍历
    for(v=0;v<G->vexnum;v++)
    {
        if(Visited[v]==0) DFS(G,v);
    }

    for(v=0;v<G->vexnum;v++)
    {
        Visited[v]=0;           //重新初始化
    }

    //对图逆向遍历
    for(j=G->vexnum-1;j>=0;j--)
    {
        v=dfn[j];   //从最晚结束的开始
        if(Visited[v]==0)
        {
            cout<<"第"<<k<<"个连通分量顶点：";
            k++;
            Rev_DFS(G,v);
        }
    }
}


/* 按弧的正向先深遍历，计算dfn*/
void DFS(OLGraph *G,int v)
{
    ArcBox *p=new ArcBox;
    Visited[v]=1 ;
    for (p=G->xlist[v].firstout;p!=NULL;p=p->tlink)
    {
        if(Visited[p->headvex]==0)  DFS(G,p->headvex);
    }
    dfn[Count++]=v ;
}


/* 对图G按弧的逆向进行搜索*/
void Rev_DFS(OLGraph *G,int v)
{
    ArcBox *p=new ArcBox;
    Visited[v]=1;
    cout<<v;
    for(p=G->xlist[v].firstin;p!=NULL;p=p->hlink)
    {
        if(Visited[p->tailvex]==0) Rev_DFS(G,p->tailvex);
    }
}




