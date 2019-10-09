#include<bits/stdc++.h>
#define ll long long
#define lb long double
#define mp make_pair
#define pb push_back
#define loop(i,start,n) for(i=start;i<n;i++)
#define rloop(i,n,start)for(i=n;i>=start;i--)
#define mod 1000000007
#define endl "\n"
#define INF     1000000000
#define NEG_INF -1000000000
#define pll pair<ll,ll>
#define x first
#define y second
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define trace1(x)                cerr << #x << ": " << x << "\n";
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << "\n";
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << "\n";
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << "\n";

using namespace std;
ll build(ll tree[],ll a[],ll start,ll size,ll node)
{
    if(start==size)
    {
        tree[node]=a[start];
    }
    else
    {   
        ll mid;
        mid=(start+size)/2;
        tree[node]=max(build(tree,a,start,mid,node*2),build(tree,a,mid+1,size,node*2+1));
    }
    return tree[node];
}

ll query(ll tree[],ll l,ll r,ll L,ll R,ll node)
{   
    
    if(l<=L&&R<=r)//full overlap
    {
        return tree[node];
    }
    else if(r<L||R<l)
        return 0;
    else
    {
        ll mid;
        mid=(L+R)/2;
        return query(tree,l,r,L,mid,node*2)+query(tree,l,r,mid+1,R,node*2+1);
    }
}


void update(ll tree[],ll pos,ll L,ll R,ll node)
{   
    //cout<<L<<" "<<R<<" "<<pos<<endl;
    if(L==R&&R==pos)
    {
        tree[node]++;
        return ;
    }
    else
    {   
        ll mid;
        mid=(L+R)/2;
        if(pos<=mid)
            update(tree,pos,L,mid,node*2);
        else
            update(tree,pos,mid+1,R,node*2+1);
        
        tree[node]++;
        return ;
    }
}
/*
#include<bits/stdc++.h>
#define ll long long
#define lb long double
#define mp make_pair
#define pb push_back
#define loop(i,start,n) for(i=start;i<n;i++)
#define rloop(i,n,start)for(i=n;i>=start;i--)
#define mod 1000000007
#define endl "\n"
#define INF     1000000000
#define NEG_INF -1000000000
#define pll pair<ll,ll>
#define x first
#define y second
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define trace1(x)                cerr << #x << ": " << x << "\n";
#define trace2(x, y)             cerr << #x << ": " << x << " | " << #y << ": " << y << "\n";
#define trace3(x, y, z)          cerr << #x << ": " << x << " | " << #y << ": " << y << " | " << #z << ": " << z << "\n";
#define trace4(a, b, c, d)       cerr << #a << ": " << a << " | " << #b << ": " << b << " | " << #c << ": " << c << " | " << #d << ": " << d << "\n";

using namespace std;
ll build(ll tree[],ll a[],ll start,ll size,ll node)
{
    if(start==size)
    {
        tree[node]=a[start];
    }
    else
    {   
        ll mid;
        mid=(start+size)/2;
        tree[node]=max(build(tree,a,start,mid,node*2),build(tree,a,mid+1,size,node*2+1));
    }
    return tree[node];
}

ll query(ll tree[],ll l,ll r,ll L,ll R,ll node)
{   
    
    if(l<=L&&R<=r)//full overlap
    {
        return tree[node];
    }
    else if(r<L||R<l)
        return 0;
    else
    {
        ll mid;
        mid=(L+R)/2;
        return query(tree,l,r,L,mid,node*2)+query(tree,l,r,mid+1,R,node*2+1);
    }
}


void update(ll tree[],ll pos,ll L,ll R,ll node)
{   
    //cout<<L<<" "<<R<<" "<<pos<<endl;
    if(L==R&&R==pos)
    {
        tree[node]++;
        return ;
    }
    else
    {   
        ll mid;
        mid=(L+R)/2;
        if(pos<=mid)
            update(tree,pos,L,mid,node*2);
        else
            update(tree,pos,mid+1,R,node*2+1);
        
        tree[node]++;
        return ;
    }
}

*/ segm
