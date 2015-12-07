#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int flag=0;

typedef struct Node
{
    int data;
    struct Node *lchild;
    struct Node *rchild;
    int height;
}*Position,*AvlTree;

AvlTree  Insert(AvlTree T,int x);
int Height(Position P);
Position LL(Position T);
Position RR(Position T);
Position LR(Position T);
Position RL(Position T);
void Search(AvlTree T,int x);
AvlTree  Delete(AvlTree T,int x);
AvlTree Rotate(AvlTree T);
void PrintTree(AvlTree T);

int main()
{
    AvlTree T=NULL;
    int data;
    int info,del;//cout<<"~"<<info;
    cout << "������ڵ���Ϣ����0�������룺" << endl;
   // freopen("avltree.txt", "r", stdin);
    cin>>data;
    while(data!=0)
    {
        T=Insert(T,data);
        cin>>data;
    }
    //cout<<"~"<<info;
    cout<<"������avl��Ϊ��";
    PrintTree(T);
    cout<<endl;

    cout<<"����Ҫ���ҵ�����:";
    cin>>info;
    //cout<<"!"<<info;
    Search(T,info);
    if(flag==0) cout<<"����������"<<endl;

    cout<<"����Ҫɾ�������֣�";
    cin>>del;
    T = Delete(T,del);
    cout<<"ɾ�����avl��Ϊ��";
    PrintTree(T);
    return 0;

}


AvlTree  Insert(AvlTree T,int x)
{
    //���T�����ڣ��򴴽�һ���ڵ���
    if(T == NULL)
    {
        T = (AvlTree)malloc(sizeof(struct Node));
        {
            T->data = x;
            T->height = 0;
            T->lchild = NULL;
            T->rchild = NULL;
        }
    }
    // ���Ҫ�����Ԫ��С�ڵ�ǰԪ��
    else if(x < T->data)
    {
        T->lchild=Insert(T->lchild,x);
        if(Height(T->lchild)-Height(T->rchild)==2)   //����֮������нڵ�ƽ������Ϊ2,(��Ϊ�Ǽӵ����)
        {
            if(x < T->lchild->data) T = LL(T);      //��x���뵽��T->lchild����ֻ࣬����൥��ת
            else    T =  LR(T); // x ���뵽��T->left���Ҳ࣬��Ҫ���˫��ת
        }
    }
    // ���Ҫ�����Ԫ�ش��ڵ�ǰԪ��
    else if(x > T->data)
    {
        T->rchild=Insert(T->rchild,x);
        if(Height(T->rchild)-Height(T->lchild)==2)   //����֮������нڵ�ƽ������Ϊ2,(��Ϊ�Ǽӵ��ұ�)
        {
            if(x > T->rchild->data)  T = RR(T);
            else  T =  RL(T);
        }
    }
    T->height=Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;
    return T;
}

int Height(Position P)
{
    if(P == NULL)               //����յ����
        return -1;
    else
        return P->height;
}

Position LL(Position T)     // LL��ת
{
    Position p;
    p=T->lchild;     //���任(ͬ��)
    T->lchild=p->rchild;
    p->rchild=T;  //��ת
    T->height=Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;        //�������ϵ�height����Ϊ�ڵ����������Ķ��������±ߣ�
    p->height=Height(p->lchild)>Height(p->rchild)?Height(p->lchild)+1:Height(p->rchild)+1;        //��Ϊ�Ǹ�������+1
    return p; //�滻�ڵ�
}

Position RR(Position T)  // RR��ת
{
    Position p;
    p=T->rchild;     //���任
    T->rchild=p->lchild;    //�Ȱѽڵ��������������������ڵ��������(����֮��ڵ�������������������ʧ)
    p->lchild=T;  //��ת
    T->height=Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;        //�������ϵ�height����Ϊ�ڵ����������Ķ��������±ߣ�
    p->height=Height(p->lchild)>Height(p->rchild)?Height(p->lchild)+1:Height(p->rchild)+1;        //��Ϊ�Ǹ�������+1
    return p; //�滻�ڵ�
}

Position LR(Position T)
{
    //�� T �����ӣ�ִ���Ҳ൥��ת
    T->lchild=RR(T->lchild);
    // �ٶ� T ���� ��൥��ת
    return LL(T);
}

Position RL(Position T)
{
    //�� T ���Һ��ӣ�ִ����൥��ת
    T->rchild = LL(T->rchild);
    // �ٶ� T ���� �Ҳ൥��ת
    return RR(T);
}

void Search(AvlTree T,int x)
{
    if(T!=NULL&&flag==0)
    {
        if(T->data==x) {cout<<"�鵽��Ԫ��"<<endl;flag=1;}
        else
        {
            Search(T->lchild,x);
            Search(T->rchild,x);
        }
    }
}

//��λҪɾ���Ľڵ㣬Ȼ���øýڵ���Һ��ӵ��������滻�ýڵ㣬
AvlTree  Delete(AvlTree T,int x)
{
    if(T == NULL)   return NULL;

    if(T->data<x)   T->rchild=Delete(T->rchild,x);
    else if(T->data>x)    T->lchild=Delete(T->lchild,x);
    else if(T->data == x)           // Ҫɾ���� x ���ڵ�ǰ�ڵ�Ԫ��
    {
        if(T->rchild == NULL )  // ����Ҫɾ���Ľڵ� T ���Һ���Ϊ��,��ֱ��ɾ��
        {
            AvlTree tmp = T;
            T = T->lchild;
            free(tmp);
        }
        else                 //�����ҵ� T->rchild ���������
        {
            AvlTree tmp = T->rchild;
            while(tmp->lchild)
            {
                tmp=tmp->lchild;  //�ҵ�����
            }

            T->data = tmp->data;  //ֱ���滻
            T->rchild = Delete(T->rchild,T->data);  //�ݹ�������Ȼ�����׿�ʼ��height��data�ѻ�
            T->height = Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;
        }
        return T;
    }

    // ��ɾ��Ԫ�غ����ƽ��
    T->height=Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;
    if(T->lchild != NULL)   T->lchild = Rotate(T->lchild);
    if(T->rchild != NULL)   T->rchild = Rotate(T->rchild);
    if(T)   T=Rotate(T);
    return T;
}


//�Ե����ڵ���е�AVL����
AvlTree Rotate(AvlTree T)
{

    if(Height(T->lchild)-Height(T->rchild)==2)
    {
        if(Height(T->lchild->lchild) >=Height(T->lchild->rchild))
            T = LL(T);  // LL��ת
        else
            T =  LR(T);     // LR��ת
    }
    if(Height(T->rchild)-Height(T->lchild)==2)
    {
        if(Height(T->rchild->rchild) >= Height(T->rchild->lchild))
            T = RR(T);  // RR��ת
        else
            T =  RL(T);     // RL��ת
    }
    return T;
}


void PrintTree(AvlTree T)
{
    if(T!=NULL)
    {
        PrintTree(T->lchild);
        cout<<T->data<<"    ";
        PrintTree(T->rchild);
    }
}

