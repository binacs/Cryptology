#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <queue>
#include <set>
using namespace std;

typedef long long ll;
struct elgamal{
    ll a,b,p,g,d,x,y;
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
    ll mkpri(){
        for(;;){
            ll ans=rand()%32769+32768;//a属于2^15~2^16这个范围
            if((ans&1)&&MillerRabin(ans)) return ans;
        }
    }
    //求本原元
    bool notpri[100005];
    ll pri[100005],zyz[100005];
    void Shai(ll N){
        notpri[1]=1;
        for(ll i=2;i<=N;i++){
            if(!notpri[i])pri[++pri[0]]=i;
            for(ll j=1;j<=pri[0]&&i*pri[j]<=N;j++){
                notpri[i*pri[j]]=1;
                if(i%pri[j]==0) break;
            }
        }
    }
    ll FindRoot(ll x){//求素奇数的最小原根，倘若x不是奇数，但是也有原根的话，将质
                         //因子分解改成对phi(x)即可。倘若要求多个原根，直接接着暴力验证即可
        ll tmp=x-1;
        for(ll i=1;tmp && i<=pri[0];++i){
            if(tmp%pri[i]==0){
                zyz[++zyz[0]]=pri[i];
                while(tmp%pri[i]==0){
                    tmp/=pri[i];
                }
            }
        }
        for(ll g=2;g<=x-1;++g){
            bool flag=1;
            for(ll i=1;i<=zyz[0];++i){
                if(mod_pow((ll)g,(ll)((x-1)/zyz[i]),(ll)x)==1ll){
                    flag=0;break;
                }
            }
            if(flag) return g;
        }
        return -1;
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

    void init(){
        Shai(100000);
        //p p-1有大素数因子
        for(;;){
            p=mkpri();
            if(MillerRabin((p-1)/2)) break;
        }
        // 本原元 g
        g=FindRoot(p);
        // d 密钥
        d=rand()%(p-3)+2;
        // y 公钥
        y=mod_pow(g,d,p);
    }
    //选择会话密钥——随机整数k 1<k<p-1
    //计算 a = g^k (mod p) 和 b = y^k * M (mod p)
    // 其中M是明文 g即p的原根    ////x是解密钥
    //密文(a, b)
    void encode(ll m,ll &a,ll &b){
        ll pp=p-1;
        ll k;
        for(;;){
            k=rand()%pp;
            if(k>1) break;
        }
        a=mod_pow(g,k,p);   //密文第一部分
        b=mod_pow(y,k,p);
        b=(b*m)%p;      //密文第二部分
    }
    ll decode(ll a,ll b){
        x=mod_pow(a,d,p);
        x=inv(x,p);
        return (b*x)%p;
    }
};
elgamal ca;
int main(){
    int t=0;
    ll m;
    while(1){
        printf("Case %d:\n",++t);
        ca.init();
        printf("输入明文：");
        scanf("%lld",&m);
        printf("获取到的输入是%lld\n",m);
        ca.encode(m,ca.a,ca.b);
        printf("密文：%lld %lld\n",ca.a,ca.b);
        printf("明文：%lld\n",ca.decode(ca.a,ca.b));
        printf("a=%lld b=%lld p=%lld g=%lld d=%lld x=%lld y=%lld\n\n\n",ca.a,ca.b,ca.p,ca.g,ca.d,ca.x,ca.y);
    }
    return 0;
}


