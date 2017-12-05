#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <queue>
using namespace std;
typedef long long ll;
struct RSA{
    //------基础功能部分---------
    
    //快速乘
    ll mod_mul(ll a,ll b,ll mod){
        ll res=0;
        while(b){
            if(b&1) res=(res+a)%mod;
            a=(a+a)%mod;
            b>>=1;
        }
        return res;
    }
    //快速幂
    ll mod_pow(ll x,ll n,ll mod){
        ll res=1;
        while(n>0){
            if(n&1) res=res*x%mod;
            x=x*x%mod;
            n>>=1;
        }
        return res;
    }
    bool MillerRabin(ll n){
        if(n==1) return true;
        if(n<2||!(n&1)) return false;
        ll m=n-1,k=0;
        while(!(m&1)){
            k++;m>>=1;
        }
        for(int i=1;i<=20;i++){ //20为测试的迭代次数
            ll a=rand()%(n-1)+1;
            ll x=mod_pow(a,m,n),y;
            for(int j=1;j<=k;j++){
                y=mod_mul(x,x,n);
                if(y==1&&x!=1&&x!=n-1) return false;
                x=y;
            }
            if(y!=1) return false;
        }
        return true;
    }
    //  求整数x y 使得ax+by=d且|x|+|y|最小 其中d=gcd(a,b)
    void gcd(ll a,ll b,ll& d,ll& x,ll& y){
        if(!b){ d=a;x=1;y=0;}
        else{ gcd(b,a%b,d,y,x);y-=x*(a/b);}
    }
    //  计算模n下a的逆 若不存在返回-1
    ll inv(ll a,ll n){
        ll d,x,y;
        gcd(a,n,d,x,y);
        return d==1?(x+n)%n:-1;
    }
    ll mkpri(){
        for(;;){
            ll ans=rand()%32769+32768;//a属于2^15~2^16这个范围
            if((ans&1)&&MillerRabin(ans)) return ans;
        }
    }
    
    long long p,q,n,f,e=65537,d,s;
    void mked(ll eul){
        e=65537;
        d=inv(e,eul);
    }
    void init(){
        for(;;){
            p=mkpri();
            q=mkpri();
            n=p*q;
            f=(p-1)*(q-1);
            if(f>e) break;
        }
        mked(f);
        printf("p=%lld q=%lld n=%lld f=%lld e=%lld d=%lld\n",p,q,n,f,e,d);
    }
    
    //公钥加密
    ll encodepub(ll &m){
        return mod_pow(m,e,n);
    }
    //私钥解密
    ll decodepri(ll &c){
        return mod_pow(c,d,n);
    }
};

RSA ca;
int main(){
    ll m,s;
    int t=0;
    while(1){
        printf("Case %d:\n",++t);
        ca.init();
        printf("输入明文：");
        scanf("%lld",&m);
        printf("获取到的输入是%lld\n",m);
        s=ca.encodepub(m);
        printf("密文：%lld\n",s);
        printf("明文：%lld\n\n",ca.decodepri(s));
    }
    return 0;
}





