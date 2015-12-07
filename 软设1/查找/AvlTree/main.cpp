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
    cout << "输入各节点信息并以0结束输入：" << endl;
   // freopen("avltree.txt", "r", stdin);
    cin>>data;
    while(data!=0)
    {
        T=Insert(T,data);
        cin>>data;
    }
    //cout<<"~"<<info;
    cout<<"建立的avl树为：";
    PrintTree(T);
    cout<<endl;

    cout<<"输入要查找的数字:";
    cin>>info;
    //cout<<"!"<<info;
    Search(T,info);
    if(flag==0) cout<<"该数不存在"<<endl;

    cout<<"输入要删除的数字：";
    cin>>del;
    T = Delete(T,del);
    cout<<"删除后的avl树为：";
    PrintTree(T);
    return 0;

}


AvlTree  Insert(AvlTree T,int x)
{
    //如果T不存在，则创建一个节点树
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
    // 如果要插入的元素小于当前元素
    else if(x < T->data)
    {
        T->lchild=Insert(T->lchild,x);
        if(Height(T->lchild)-Height(T->rchild)==2)   //加入之后如果有节点平衡因子为2,(因为是加到左边)
        {
            if(x < T->lchild->data) T = LL(T);      //把x插入到了T->lchild的左侧，只需左侧单旋转
            else    T =  LR(T); // x 插入到了T->left的右侧，需要左侧双旋转
        }
    }
    // 如果要插入的元素大于当前元素
    else if(x > T->data)
    {
        T->rchild=Insert(T->rchild,x);
        if(Height(T->rchild)-Height(T->lchild)==2)   //加入之后如果有节点平衡因子为2,(因为是加到右边)
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
    if(P == NULL)               //处理空的情况
        return -1;
    else
        return P->height;
}

Position LL(Position T)     // LL旋转
{
    Position p;
    p=T->lchild;     //作变换(同上)
    T->lchild=p->rchild;
    p->rchild=T;  //再转
    T->height=Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;        //从下往上调height（因为节点变成左子树的儿子了在下边）
    p->height=Height(p->lchild)>Height(p->rchild)?Height(p->lchild)+1:Height(p->rchild)+1;        //因为是父亲所以+1
    return p; //替换节点
}

Position RR(Position T)  // RR旋转
{
    Position p;
    p=T->rchild;     //作变换
    T->rchild=p->lchild;    //先把节点左子树的右子树赋给节点的左子树(否则之后节点左子树的右子树会损失)
    p->lchild=T;  //再转
    T->height=Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;        //从下往上调height（因为节点变成左子树的儿子了在下边）
    p->height=Height(p->lchild)>Height(p->rchild)?Height(p->lchild)+1:Height(p->rchild)+1;        //因为是父亲所以+1
    return p; //替换节点
}

Position LR(Position T)
{
    //在 T 的左孩子，执行右侧单旋转
    T->lchild=RR(T->lchild);
    // 再对 T 进行 左侧单旋转
    return LL(T);
}

Position RL(Position T)
{
    //在 T 的右孩子，执行左侧单旋转
    T->rchild = LL(T->rchild);
    // 再对 T 进行 右侧单旋转
    return RR(T);
}

void Search(AvlTree T,int x)
{
    if(T!=NULL&&flag==0)
    {
        if(T->data==x) {cout<<"查到该元素"<<endl;flag=1;}
        else
        {
            Search(T->lchild,x);
            Search(T->rchild,x);
        }
    }
}

//定位要删除的节点，然后用该节点的右孩子的最左孩子替换该节点，
AvlTree  Delete(AvlTree T,int x)
{
    if(T == NULL)   return NULL;

    if(T->data<x)   T->rchild=Delete(T->rchild,x);
    else if(T->data>x)    T->lchild=Delete(T->lchild,x);
    else if(T->data == x)           // 要删除的 x 等于当前节点元素
    {
        if(T->rchild == NULL )  // 若所要删除的节点 T 的右孩子为空,则直接删除
        {
            AvlTree tmp = T;
            T = T->lchild;
            free(tmp);
        }
        else                 //否则找到 T->rchild 的最左儿子
        {
            AvlTree tmp = T->rchild;
            while(tmp->lchild)
            {
                tmp=tmp->lchild;  //找到最左
            }

            T->data = tmp->data;  //直接替换
            T->rchild = Delete(T->rchild,T->data);  //递归找最左，然后从最底开始调height，data已换
            T->height = Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;
        }
        return T;
    }

    // 当删除元素后调整平衡
    T->height=Height(T->lchild)>Height(T->rchild)?Height(T->lchild)+1:Height(T->rchild)+1;
    if(T->lchild != NULL)   T->lchild = Rotate(T->lchild);
    if(T->rchild != NULL)   T->rchild = Rotate(T->rchild);
    if(T)   T=Rotate(T);
    return T;
}


//对单个节点进行的AVL调整
AvlTree Rotate(AvlTree T)
{

    if(Height(T->lchild)-Height(T->rchild)==2)
    {
        if(Height(T->lchild->lchild) >=Height(T->lchild->rchild))
            T = LL(T);  // LL旋转
        else
            T =  LR(T);     // LR旋转
    }
    if(Height(T->rchild)-Height(T->lchild)==2)
    {
        if(Height(T->rchild->rchild) >= Height(T->rchild->lchild))
            T = RR(T);  // RR旋转
        else
            T =  RL(T);     // RL旋转
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

