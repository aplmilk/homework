#include <iostream>

using namespace std;

//�߽ڵ�
typedef struct node
{
    int adjvex;
    struct node *next;
}node;

//ͷ���
typedef struct Vertexnode
{
    char vertex;
    node *firstedge;
}Vertexnode;

//���ӱ�
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
     //��ӡ���ӱ�
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
    cout<<"������ͼ�Ķ������ͱ�����";
    cin>>G.n>>G.e;
    cout<<"�����������Ϣ��";
    for(i=0; i<G.n; i++)
    {
        cin>>G.vexlist[i].vertex;
        G.vexlist[i].firstedge=NULL;  //��̳�ʼ��Ϊ��
    }
    cout<<"����������������Ϣ(��ű�ʾ):";
    for(i=0; i<G.e; i++)
    {
        cin>>head>>tail;
        node *p=new node;
        p->adjvex=tail;
        p->next=G.vexlist[head].firstedge;
        G.vexlist[head].firstedge=p; //cout<<"!!"<<p->adjvex<<endl;
        //����ͼ�������
        node *q=new node;
        q->adjvex=head;
        q->next=G.vexlist[tail].firstedge;
        G.vexlist[tail].firstedge=q;
    }
    //��ӡ���ӱ�
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
    /* ��ͨͼG ���ڽӱ����洢�ṹ�����Ҳ����G��ȫ���ؽڵ�*/
    int i;
    node *p=new node;
    int v;
    Count=2; /* ȫ�ֱ���count���ڶԷ��ʼ���*/
    dfn[0]=1; //�趨�ڽӱ���0�Ŷ���Ϊ�������ĸ�
    low[0]=1;
    for(i=1; i<G.n; ++i)
    {
        dfn[i]=0;   //δ���ʳ�ʼ��Ϊ0��dfn[]��ְvisited[]
    }

    p=G.vexlist[0].firstedge;
    v=p->adjvex;    //cout<<v<<"ts"<<p->adjvex<<"!!"<<endl;
    cout<<"�ؽڵ�Ϊ��";
    DFSArticul(G,v,dfn,low); //�Ӷ���v ����������Ȳ��ҹؽڵ�
    if(Count<=G.n)    /* �������ĸ���������������*/
    {
        cout<<G.vexlist[0].vertex; /* ���ǹؽڵ㣬���*/
        while(p->next!=NULL)
        {
            p=p->next;
            v=p->adjvex;
            if(dfn[v]==0)  DFSArticul(G,v,dfn,low);
            }
    }
}


/* �Ӷ���v0 ����������ȱ���ͼG������low [] �����Ҳ�����ؽڵ�*/
void DFSArticul(AdjGraph G,int v,int dfn[],int low[])
{
    int w,min;
    dfn[v]=Count;   //v0�ǵ�count�����ʵĶ���
    min=Count;    //��Сֵ��ʼ��Ϊ�������
    Count++;

    node *p=new node;
    for(p=G.vexlist[v].firstedge;p!=NULL;p=p->next)    // ��v0 ��ÿ���ڽӵ���
    {
        w=p->adjvex ;
        if(dfn[w]==0)       //��wδ�����ʣ���wΪv0�ĺ���(��Ϊ����ͼҲ�븸������)
        {
            DFSArticul(G,w,dfn,low);        //����ǰ���low[w]
            if(low[w]<min)    min=low[w];
            if(low[w]>=dfn[v]) cout<<G.vexlist[v].vertex; //����ؽڵ�
        }
        else if(dfn[w]<min)    min=dfn[w];   //�ѷ���Ϊ����
    }
    low[v]=min;
    }
