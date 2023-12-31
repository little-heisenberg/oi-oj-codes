#include <bits/stdc++.h>
using namespace std;
const int SIZE=4e5+10;
int read(){
    int x=0,w=1;
    char ch=0;
    while(ch<'0'||ch>'9'){
        if(ch=='-') w=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9'){
        x=x*10+(ch-'0');
        ch=getchar();
    }
    return x*w;
}
void print(int x){
    if(x<0) putchar('-'),print(-x);
    if(x>=10) print(x/10);
    putchar(x%10+'0');
}
int n,col[SIZE],loc[SIZE],m;
vector<int> G[SIZE];
int dep[SIZE],fh[SIZE],siz[SIZE];
int wson[SIZE],toch[SIZE],dfn[SIZE],dft;
void dfs(int u,int fa){
    siz[u]=1,dep[u]=dep[fa]+1,fh[u]=fa;
    for(int v:G[u]){
        if(v==fa) continue;
        dfs(v,u);
        siz[u]+=siz[v];
        if(siz[wson[u]]<siz[v]) wson[u]=v;
    }
}
void subd(int u,int top){
    toch[u]=top,dfn[u]=++dft;
    if(wson[u]==0) return;
    subd(wson[u],top);
    for(int v:G[u]){
        if(v==fh[u]||v==wson[u]) continue;
        subd(v,v);
    }
}
struct omg{
    int lf,rt;
    mutable int val;
    omg(int l,int r=-1,int v=0):lf(l),rt(r),val(v){}
    bool operator<(const omg &rhs)const{
        return lf<rhs.lf;
    }
};
set<omg> wtf;
typedef set<omg>::iterator iter;
iter split(int pos){
    iter it=wtf.lower_bound(omg(pos));
    if(it!=wtf.end()&&it->lf==pos) return it;
    it--;
    int lf=it->lf,rt=it->rt,val=it->val;
    wtf.erase(it);
    wtf.insert(omg(lf,pos-1,val));
    return wtf.insert(omg(pos,rt,val)).first;
}
void assign(int lf,int rt,int val){
    iter itr=split(rt+1),itl=split(lf);
    wtf.erase(itl,itr);
    wtf.insert(omg(lf,rt,val));
}
int main(){
    n=read(),m=read();
    for(int i=1;i<=n;i++) loc[i]=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        G[u].emplace_back(v);
        G[v].emplace_back(u);
    }
    dfs(1,1),subd(1,1);
    for(int i=1;i<=n;i++) col[dfn[i]]=loc[i];
    int st=1,cl=col[1];
    for(int i=2;i<=n;i++) if(col[i]!=cl){
        wtf.insert(omg(st,i-1,cl));
        st=i,cl=col[i];
    }
    wtf.insert(omg(st,n,cl));
    while(m--){
        int o=read(),u=read(),c;
        if(o==1){
            c=read();
            assign(dfn[u],dfn[u]+siz[u]-1,c);
        }else{
            int lf=dfn[u],rt=dfn[u]+siz[u]-1,ans=0;
            bool colt[70]={};
            iter itr=split(rt+1),itl=split(lf);
            for(iter it=itl;it!=itr;++it){
                if(!colt[it->val]) ++ans,colt[it->val]=true;
                if(ans==60) break;
            }
            print(ans),putchar('\n');
        }
    }
    return 0;
}