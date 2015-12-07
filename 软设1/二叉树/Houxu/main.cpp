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
    node *fa;
    node(){
        rc=NULL;
        lc=NULL;
        fa=NULL;
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
    T->val=c;
    T->lc=new node;
    T->rc=new node;
    T->lc->fa=T;
    T->rc->fa=T;

    creat(T->lc);
    creat(T->rc);
}

node *pre;
bool first=true;;
node *start;
void dfs(node *root){
    if(!root)
        return;
    if(!root->ltag)
        dfs(root->lc);
    if(!root->rtag)
        dfs(root->rc);

    if(first){
        first=false;
        start=root;
    }
    if(!root->lc){
        root->ltag=1;
        root->lc=pre;
    }

    if(pre && !pre->rc){
        pre->rtag=1;
        pre->rc=root;
    }
    pre=root;

}

node *next(node *root){
    if(root->rtag)
        return root->rc;
    node *f=root->fa;

    if(!f->ltag && root==f->lc){
        if(!f->rtag)
            f=f->rc;
        else
            return f;

        while(!f->ltag){
            f=f->lc;
        }
        return f;
    }
    else
        return f;
}
int main(){
    root=new node;
    creat(root);
    pre=NULL;
    dfs(root);
    if(!pre->rtag){
        pre->rtag=1;
        pre->rc=NULL;
    }
    //cout<<root->lc->fa->val<<endl;
    node *p=start;

    while(p!=root){
     //   cout<<"ss"<<endl;
        cout<<p->val<<endl;
        p=next(p);
    //    cout<<"hh"<<endl;
    }

    cout<<p->val<<endl;
}
