#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#define MAXM 1000
#define MAXN 1000
using namespace std;
struct edge {
	int v, w;
	edge *next;
	void add(int y,edge *&head){ v = y; next = head; head = this; }
}Te[MAXM*2],*Pe=Te,*head[MAXN];

struct node{
    node *lc,*rc;
    int num;
    node(int i=0){
        num=i;
        lc=NULL;
        rc=NULL;
    }
}*tree[MAXN];
void add_edge(int x, int y) {
	Pe++->add(y, head[x]);
}
int n,m;
bool visit[MAXN];
void dfs(int i){
    visit[i]=true;
    if(head[i]==NULL){
        tree[i]->lc=NULL;
        //tree[i]->rc=NULL;
        return;
    }

    bool first=true;
    edge *tmp;
    for(edge *p=head[i];p;p=p->next){
        if(visit[p->v])
            continue;
        if(first){
            first=false;
            tree[i]->lc=tree[p->v];
            tmp=p;
        }
        else{
            tree[tmp->v]->rc=tree[p->v];
            tmp=p;
        }
    }
    if(!first)
        tree[tmp->v]->rc=NULL;
    for(edge *p=head[i];p;p=p->next){
        if(!visit[p->v])
            dfs(p->v);
    }
}
void solve1(){
    for(int i=1;i<=n;i++){
        tree[i]=new node(i);
    }
    bool first=true;
    int tmp;
    int root;
    for(int i=1;i<=n;i++){
        if(!visit[i]){
            if(first){
                tmp=i;
                root=i;
                first=false;
            }
            else{
                tree[tmp]->rc=tree[i];
                tmp=i;
            }
            dfs(i);
        }
    }
}
void solve2(){
    for(int i=1;i<=n;i++){
        if(tree[i]->lc){
            add_edge(i,tree[i]->lc->num);
            node *p=tree[i]->lc;
            while(p->rc){
                p=p->rc;
                add_edge(i,p->num);
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add_edge(x,y);
        add_edge(y,x);
    }
    solve1();
    for(int i=1;i<=n;i++){
        cout<<i<<' ';
        if(tree[i]->lc)
            cout<<tree[i]->lc->num<<' ';
        else
            cout<<"NULL ";
        if(tree[i]->rc)
            cout<<tree[i]->rc->num<<endl;
        else
            cout<<"NULL\n";


    }
    memset(head,0,sizeof(head));
    Pe=Te;
    solve2();
    for(int i=1;i<=n;i++){
        cout<<i<<' ';
        for(edge *p=head[i];p;p=p->next){
            cout<<p->v<<' ';
        }
        cout<<endl;
    }
}
