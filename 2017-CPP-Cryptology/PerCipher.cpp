#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <sstream>
using namespace std;
struct PerCipher{   //置换密码
    char input[2005],output[2005];
    char mat[2005][2005];
    int sec[30]={0,6,5,3,1,4,2};  //数字序列 可由密钥简单处理得到 为简化流程在此直接使用数字序列653142
    int secsz=6;        //在此默认数字序列长度为6 与上述sec对应
    int matline;
    int inlen,outlen;
    
    void getinput(){cin.getline(input,2000);}
    void printout(){printf("%s\n",output);}
    void primat(){
        for(int i=1;i<=matline;i++){
            for(int j=1;j<=secsz;j++) printf("%c",mat[i][j]);
            printf("\n");
        }
    }
    void encode(){
        printf("数字序列:\n");
        for(int i=1;i<=secsz;i++) {printf("%d",sec[i]);if(i!=secsz)printf(" ");else printf("\n");}
        inlen=strlen(input);
        matline=1;
        int p=0;
        while(matline*secsz<inlen){
            for(int i=1;i<=secsz;i++,p++){
                mat[matline][i]=input[p];
            }
            matline++;
        }
        for(int i=1;i<=secsz;i++,p++){
            mat[matline][i]=p>=inlen?'@':input[p];
        }
        primat(); //输出矩阵
        p=0;
        for(int i=1;i<=secsz;i++)
            for(int j=1;j<=matline;j++,p++) output[p]=mat[j][sec[i]];
        outlen=p;
    }
    void decode(){
        printf("数字序列:\n");
        for(int i=1;i<=secsz;i++) {printf("%d",sec[i]);if(i!=secsz)printf(" ");else printf("\n");}
        inlen=strlen(input);
        matline=inlen/secsz;
        int p=0;
        for(int i=1;i<=secsz;i++){
            for(int j=1;j<=matline;j++,p++) mat[j][sec[i]]=input[p];
        }
        primat(); //输出矩阵
        p=0;
        for(int i=1;i<=matline;i++)
            for(int j=1;j<=secsz;j++,p++){
                if(mat[i][j]=='@') break;
                output[p]=mat[i][j];
            }
        outlen=p;
    }
};
PerCipher ca;
int main(){
    ca.getinput();
    ca.decode();
    ca.printout();
    return 0;
}
