#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
/*二叉树的数据结构*/
typedef struct tree
{
    struct tree *left,*right;    // 左右子树
    char data;
} BTREE;
/*森林的数据结构*/
typedef struct childnode
{
    int index;    // 表头下标
    struct childnode *nextnode;    // 兄弟
} CHILDNODE;
typedef struct rootnode
{
    char data;    // 结点数据
    CHILDNODE *firstchild;    // 第一个孩子
} ROOTNODE;
typedef struct atree    // 森林中的树
{
    ROOTNODE par[MAXSIZE];    // 所有节点组成表头
    int n;    // 结点数
    struct atree *nexttree;
} ATREE;

BTREE* CreatBinaryTree(BTREE *root);    // 普通二叉树的建立
void InOrderPrint(BTREE *root);    // 普通二叉树的中序遍历
int FindIndex(ROOTNODE par[],char c);    // 寻找元素在头表中的位置
void BiTrToFr(ATREE *temp,BTREE *root);    // 二叉树转化为森林
void PrintForest(ATREE *forest);    // 打印森林
BTREE* FrToBiTr(BTREE *root,ATREE *forest);    // 森林转化为二叉树

int amount =  0;    // 结点数

int main()
{
    BTREE *root = NULL,*root1 = NULL;    // 二叉树的根
    ATREE *forest = NULL;
    printf("前序构造二叉树:\n");
    root = CreatBinaryTree(root);
    printf("中序遍历二叉树:\n");
    InOrderPrint(root);    // 中序
    /*二叉树转化为森林*/
    forest = (ATREE *)malloc(sizeof(ATREE));
    BiTrToFr(forest,root);
    printf("\n二叉树转化为森林 :\n");
    PrintForest(forest);
    /*森林转化为二叉树*/
    root1 = FrToBiTr(root1,forest);
    printf("\n森林转化为二叉树 （中序）:\n");
    InOrderPrint(root1);    // 中序

    return 0;
}

BTREE* CreatBinaryTree(BTREE *root)    // 普通二叉树的建立
{
    char in;
    //fflush(stdin);
    scanf("%c",&in);    // 获得节点数据
    if(in == '#')
    {
        root = NULL;
    }
    else
    {
        amount ++;
        root = (BTREE*)malloc(sizeof(BTREE));
        (*root).data = in;
        root->left = CreatBinaryTree(root->left);    // 递归建立左右树
        root->right = CreatBinaryTree(root->right);
    }
    return root;
}

void InOrderPrint(BTREE *root)    // 中序打印普通二叉树
{
    if(root != NULL)
    {
        InOrderPrint(root -> left);
        printf("%c",root -> data);
        InOrderPrint(root -> right);
    }
}

int FindIndex(ROOTNODE par[],char c)    // 寻找结点在头表中的下标
{
    int i;
    for(i = 0; i < amount; i ++)  // 遍历
    {
        if(par[i].data == c)
        {
            return i;
        }
    }
    return -1;
}

void BiTrToFr(ATREE *temp,BTREE *root)     // 二叉树转化为森林
{
    int i = 0,index,number = 0;
    BTREE *parti;
    CHILDNODE *c;
    ROOTNODE *p;
    char data;
    parti = root;
    if(root == NULL)    // 空
    {
        temp = NULL;
        return;
    }
    else
    {
        number ++;    // 记录树中结点数:控制打印森林用
        temp -> par[i].data = parti->data;    // 新结点加入头表
        temp -> par[i].firstchild = NULL;
        p = &(temp -> par[i]);    // 当前父结点
        if(parti -> left != NULL)    // 有左子则森林中当前树有孩子
        {
            p -> firstchild = (CHILDNODE *)malloc(sizeof(CHILDNODE));    // 有子：根的左子

            parti = parti -> left;
            data = parti-> data;
            index = FindIndex(temp -> par,data);    // 寻找其在头表中的位置
            if(index == -1)    // 不在头表中，加入头表
            {
                i ++;
                number ++;
                temp -> par[i].data = data;
                temp -> par[i].firstchild = NULL;
                p -> firstchild -> index = i;    // 第一子，直接链入父结点之后的孩子链
            }
            else
            {
                p -> firstchild -> index = index;    // 已在在头表中，直接链入父结点之后的孩子链
            }
            p -> firstchild -> nextnode = NULL;
            c = p -> firstchild;    // 用以指示下一子的插入位置
            while(parti -> right != NULL)    // 有其他子：二叉树连续的右链
            {
                c -> nextnode = (CHILDNODE *)malloc(sizeof(CHILDNODE));
                c = c -> nextnode;    // 确定插入位置为孩子链尾
                parti = parti -> right;
                data = parti -> data;
                index = FindIndex(temp -> par,data);    // 寻找其在头表中的位置
                if(index == -1)    // 不在头表中，加入头表
                {
                    i ++;
                    number ++;
                    temp -> par[i].data = data;
                    temp -> par[i].firstchild = NULL;
                    c -> index = i;
                }
                else    // 在头表中
                {
                    c -> index = index;
                }
                c -> nextnode = NULL;
            }
        }
    }
    temp -> n = number;    // 该树的结点数
    temp -> nexttree = (ATREE *)malloc(sizeof(ATREE));    // 下一棵树
    temp = temp -> nexttree;
    BiTrToFr(temp,root -> right);
}

void PrintForest(ATREE *forest)     // 打印森林
{
    int i;
    CHILDNODE *child;
    while(forest != NULL)
    {
        for(i = 0; i < forest -> n; i ++)  // 打印树
        {
            printf("%c->",forest->par[i].data);
            child = forest->par[i].firstchild;
            while(child != NULL)
            {
                printf("%c->",forest->par[child->index].data);
                child = child->nextnode;
            }
            printf("NULL\n");
        }
        forest = forest -> nexttree;    // 下一棵树
    }
}

BTREE* FrToBiTr(BTREE *root,ATREE *forest)
{
    int i = 0;
    BTREE *temp;
    CHILDNODE *c;

    if(forest == NULL || forest -> n == 0)    // 森林为空
    {
        return NULL;
    }
    else
    {
        root = (BTREE *)malloc(sizeof(BTREE));
        root -> data = forest -> par[i].data;    // 初始化
        root-> right = NULL;
        root -> left = NULL;
        c = forest->par[i].firstchild;
        if(c != NULL)    // 树有长子
        {
            root -> left = (BTREE*)malloc(sizeof(BTREE));
            root -> left -> right = NULL;
            root -> left -> left = NULL;
            root -> left -> data = forest -> par[c->index].data;    // 长子为二叉树根的左子
            temp = root -> left;    // 与建立的方式类似，看左子的右子的情况
            c = c -> nextnode;
            while(c != NULL)    // 长子有兄弟
            {
                temp -> right = (BTREE*)malloc(sizeof(BTREE));
                temp -> right -> right = NULL;
                temp -> right -> left = NULL;
                temp -> right -> data = forest -> par[c->index].data;    // 兄弟为前一个兄弟的右子
                temp = temp -> right;
                c = c -> nextnode;    // 所有连续的兄弟
            }
        }
    }
    root -> right = FrToBiTr(root -> right,forest -> nexttree);    // 递归其他树，构造右树
    return root;
}
