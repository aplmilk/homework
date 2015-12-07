#include <iostream>

using namespace std;

//�߽ڵ�
typedef struct ArcBox
{
    int tailvex,headvex;
    struct ArcBox *hlink,*tlink;    //��ͷ��β��ͬ�Ļ�������
}ArcBox;

//ͷ���
typedef struct VexNode
{
    char data;
    ArcBox *firstin,*firstout;   //�ö����һ����/�뻡
}VexNode;

//ʮ������
typedef struct OLGraph
{
    VexNode xlist[50];
    int vexnum,arcnum;  //�������ͻ���
}OLGraph;

int dfn[50];
int Visited[50];      //1ΪTRUE,0ΪFALSE
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

//��������ͼ
void CreateGraph(OLGraph *G)
{
    int i,k;
    int head,tail;   //һ�����������յ�
    cout<<"����������ͼ�Ķ������ͱ�����";
    cin>>G->vexnum>>G->arcnum;
    cout<<"��������㶥��ֵ��";
    for(i=0;i<G->vexnum;i++)
    {
        cin>>G->xlist[i].data;
        G->xlist[i].firstin=NULL; //��ʼ��
        G->xlist[i].firstout=NULL;
    }
    cout<<"�����������㡢�յ�(��ű�ʾ)��";
    for(k=0;k<G->arcnum;k++)
    {
        cin>>head>>tail;
        //����
        ArcBox *p=new ArcBox;
        p->tailvex=tail;
        p->tlink=G->xlist[head].firstout;
        G->xlist[head].firstout=p;
        //����
        ArcBox *q=new ArcBox;
        q->headvex=head;
        q->hlink=G->xlist[tail].firstin;
        G->xlist[tail].firstin=q;
    }

    //��ӡ�������ӱ�
    cout<<"������"<<endl;
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

    //��ӡ�������ӱ�
    cout<<"������"<<endl;
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
        Visited[v]=0;          //��ʼ��
    }

    //��ͼ�������
    for(v=0;v<G->vexnum;v++)
    {
        if(Visited[v]==0) DFS(G,v);
    }

    for(v=0;v<G->vexnum;v++)
    {
        Visited[v]=0;           //���³�ʼ��
    }

    //��ͼ�������
    for(j=G->vexnum-1;j>=0;j--)
    {
        v=dfn[j];   //����������Ŀ�ʼ
        if(Visited[v]==0)
        {
            cout<<"��"<<k<<"����ͨ�������㣺";
            k++;
            Rev_DFS(G,v);
        }
    }
}


/* �����������������������dfn*/
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


/* ��ͼG�����������������*/
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




