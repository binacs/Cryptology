#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <sstream>
using namespace std;
struct Vigenre{   //置换密码
    char input[2005],output[2005];
    char sec[30]={'C','I','P','H','E','R',}; //密钥 在此将密钥字母设置为cipher
    int secsz=6;    //  密钥长度为6
    char table[26][26]={
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A',
        'C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B',
        'D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C',
        'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D',
        'F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E',
        'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F',
        'H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G',
        'I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H',
        'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I',
        'K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J',
        'L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K',
        'M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M',
        'O','P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N',
        'P','Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
        'Q','R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
        'R','S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q',
        'S','T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R',
        'T','U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S',
        'U','V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
        'V','W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U',
        'W','X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V',
        'X','Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W',
        'Y','Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X',
        'Z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y',
    };
    int matline;
    int inlen,outlen;
    
    void getinput(){cin.getline(input,2000);}
    void printout(){printf("%s\n",output);}
    
    void encode(){
        printf("密钥字母:\n");
        for(int i=0;i<secsz;i++) {printf("%c",sec[i]);if(i+1!=secsz) printf(" ");else printf("\n");}
        
        inlen=strlen(input);
        int p=0;
        for(p=0;p<inlen;p++){
            output[p]=table[sec[p%secsz]-'A'][input[p]-'A'];
        }
        outlen=p;
    }
    void decode(){
        printf("密钥字母:\n");
        for(int i=0;i<secsz;i++) {printf("%c",sec[i]);if(i+1!=secsz) printf(" ");else printf("\n");}
        
        inlen=strlen(input);
        int p=0;
        for(p=0;p<inlen;p++){
            int left=sec[p%secsz]-'A';  //相对表第0行的左偏移 得到应该在第几行寻找
            for(int i=0;i<26;i++)
                if(table[left][i]==input[p]){
                    output[p]='A'+i;break;
                }
        }
        outlen=p;
    }
};
Vigenre ca;
int main(){
    ca.getinput();
    ca.decode();
    ca.printout();
    return 0;
}
