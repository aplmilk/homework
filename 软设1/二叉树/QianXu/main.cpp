#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
struct node{       //定义结构体，其中ltag和rtag代表是儿子还是前驱后继，0代表儿子，1代表前后
    char val;
    int ltag,rtag;
    node *lc;
    node *rc;
    node(){
        rc=NULL;
        lc=NULL;
        ltag=0;
        rtag=0;
    }
}*root;
int n;


void creat(node *&T){
    char c;
    cin>>c;
    if(c=='*'){
        T=NULL;
        return;
    }
    T=new node;
    T->val=c;
    creat(T->lc);
    creat(T->rc);
}

node *pre;
void dfs(node *root){
    if(!root)
        return;
    if(!root->lc){
        root->ltag=1;
        root->lc=pre;
    }

    if(pre && !pre->rc){
        pre->rtag=1;
        pre->rc=root;
    }
    pre=root;
    if(!root->ltag)
        dfs(root->lc);
    if(!root->rtag)
        dfs(root->rc);
}

node *next(node *root){
    if(root->rtag)
        return root->rc;
    if(!root->ltag)
        return root->lc;
    return root->rc;
}
int main(){
    creat(root);
    pre=NULL;

    dfs(root);
    node *p=root;
    while(p){
        cout<<p->val<<endl;
        p=next(p);
    }
}
