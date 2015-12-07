#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20
/*�����������ݽṹ*/
typedef struct tree
{
    struct tree *left,*right;    // ��������
    char data;
} BTREE;
/*ɭ�ֵ����ݽṹ*/
typedef struct childnode
{
    int index;    // ��ͷ�±�
    struct childnode *nextnode;    // �ֵ�
} CHILDNODE;
typedef struct rootnode
{
    char data;    // �������
    CHILDNODE *firstchild;    // ��һ������
} ROOTNODE;
typedef struct atree    // ɭ���е���
{
    ROOTNODE par[MAXSIZE];    // ���нڵ���ɱ�ͷ
    int n;    // �����
    struct atree *nexttree;
} ATREE;

BTREE* CreatBinaryTree(BTREE *root);    // ��ͨ�������Ľ���
void InOrderPrint(BTREE *root);    // ��ͨ���������������
int FindIndex(ROOTNODE par[],char c);    // Ѱ��Ԫ����ͷ���е�λ��
void BiTrToFr(ATREE *temp,BTREE *root);    // ������ת��Ϊɭ��
void PrintForest(ATREE *forest);    // ��ӡɭ��
BTREE* FrToBiTr(BTREE *root,ATREE *forest);    // ɭ��ת��Ϊ������

int amount =  0;    // �����

int main()
{
    BTREE *root = NULL,*root1 = NULL;    // �������ĸ�
    ATREE *forest = NULL;
    printf("ǰ���������:\n");
    root = CreatBinaryTree(root);
    printf("�������������:\n");
    InOrderPrint(root);    // ����
    /*������ת��Ϊɭ��*/
    forest = (ATREE *)malloc(sizeof(ATREE));
    BiTrToFr(forest,root);
    printf("\n������ת��Ϊɭ�� :\n");
    PrintForest(forest);
    /*ɭ��ת��Ϊ������*/
    root1 = FrToBiTr(root1,forest);
    printf("\nɭ��ת��Ϊ������ ������:\n");
    InOrderPrint(root1);    // ����

    return 0;
}

BTREE* CreatBinaryTree(BTREE *root)    // ��ͨ�������Ľ���
{
    char in;
    //fflush(stdin);
    scanf("%c",&in);    // ��ýڵ�����
    if(in == '#')
    {
        root = NULL;
    }
    else
    {
        amount ++;
        root = (BTREE*)malloc(sizeof(BTREE));
        (*root).data = in;
        root->left = CreatBinaryTree(root->left);    // �ݹ齨��������
        root->right = CreatBinaryTree(root->right);
    }
    return root;
}

void InOrderPrint(BTREE *root)    // �����ӡ��ͨ������
{
    if(root != NULL)
    {
        InOrderPrint(root -> left);
        printf("%c",root -> data);
        InOrderPrint(root -> right);
    }
}

int FindIndex(ROOTNODE par[],char c)    // Ѱ�ҽ����ͷ���е��±�
{
    int i;
    for(i = 0; i < amount; i ++)  // ����
    {
        if(par[i].data == c)
        {
            return i;
        }
    }
    return -1;
}

void BiTrToFr(ATREE *temp,BTREE *root)     // ������ת��Ϊɭ��
{
    int i = 0,index,number = 0;
    BTREE *parti;
    CHILDNODE *c;
    ROOTNODE *p;
    char data;
    parti = root;
    if(root == NULL)    // ��
    {
        temp = NULL;
        return;
    }
    else
    {
        number ++;    // ��¼���н����:���ƴ�ӡɭ����
        temp -> par[i].data = parti->data;    // �½�����ͷ��
        temp -> par[i].firstchild = NULL;
        p = &(temp -> par[i]);    // ��ǰ�����
        if(parti -> left != NULL)    // ��������ɭ���е�ǰ���к���
        {
            p -> firstchild = (CHILDNODE *)malloc(sizeof(CHILDNODE));    // ���ӣ���������

            parti = parti -> left;
            data = parti-> data;
            index = FindIndex(temp -> par,data);    // Ѱ������ͷ���е�λ��
            if(index == -1)    // ����ͷ���У�����ͷ��
            {
                i ++;
                number ++;
                temp -> par[i].data = data;
                temp -> par[i].firstchild = NULL;
                p -> firstchild -> index = i;    // ��һ�ӣ�ֱ�����븸���֮��ĺ�����
            }
            else
            {
                p -> firstchild -> index = index;    // ������ͷ���У�ֱ�����븸���֮��ĺ�����
            }
            p -> firstchild -> nextnode = NULL;
            c = p -> firstchild;    // ����ָʾ��һ�ӵĲ���λ��
            while(parti -> right != NULL)    // �������ӣ�����������������
            {
                c -> nextnode = (CHILDNODE *)malloc(sizeof(CHILDNODE));
                c = c -> nextnode;    // ȷ������λ��Ϊ������β
                parti = parti -> right;
                data = parti -> data;
                index = FindIndex(temp -> par,data);    // Ѱ������ͷ���е�λ��
                if(index == -1)    // ����ͷ���У�����ͷ��
                {
                    i ++;
                    number ++;
                    temp -> par[i].data = data;
                    temp -> par[i].firstchild = NULL;
                    c -> index = i;
                }
                else    // ��ͷ����
                {
                    c -> index = index;
                }
                c -> nextnode = NULL;
            }
        }
    }
    temp -> n = number;    // �����Ľ����
    temp -> nexttree = (ATREE *)malloc(sizeof(ATREE));    // ��һ����
    temp = temp -> nexttree;
    BiTrToFr(temp,root -> right);
}

void PrintForest(ATREE *forest)     // ��ӡɭ��
{
    int i;
    CHILDNODE *child;
    while(forest != NULL)
    {
        for(i = 0; i < forest -> n; i ++)  // ��ӡ��
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
        forest = forest -> nexttree;    // ��һ����
    }
}

BTREE* FrToBiTr(BTREE *root,ATREE *forest)
{
    int i = 0;
    BTREE *temp;
    CHILDNODE *c;

    if(forest == NULL || forest -> n == 0)    // ɭ��Ϊ��
    {
        return NULL;
    }
    else
    {
        root = (BTREE *)malloc(sizeof(BTREE));
        root -> data = forest -> par[i].data;    // ��ʼ��
        root-> right = NULL;
        root -> left = NULL;
        c = forest->par[i].firstchild;
        if(c != NULL)    // ���г���
        {
            root -> left = (BTREE*)malloc(sizeof(BTREE));
            root -> left -> right = NULL;
            root -> left -> left = NULL;
            root -> left -> data = forest -> par[c->index].data;    // ����Ϊ��������������
            temp = root -> left;    // �뽨���ķ�ʽ���ƣ������ӵ����ӵ����
            c = c -> nextnode;
            while(c != NULL)    // �������ֵ�
            {
                temp -> right = (BTREE*)malloc(sizeof(BTREE));
                temp -> right -> right = NULL;
                temp -> right -> left = NULL;
                temp -> right -> data = forest -> par[c->index].data;    // �ֵ�Ϊǰһ���ֵܵ�����
                temp = temp -> right;
                c = c -> nextnode;    // �����������ֵ�
            }
        }
    }
    root -> right = FrToBiTr(root -> right,forest -> nexttree);    // �ݹ�����������������
    return root;
}
