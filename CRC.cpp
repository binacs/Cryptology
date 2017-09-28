#include <iostream>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <stack>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;
typedef long long ll;

const int crc_8=0x07; //crc-8 x^8+x^2+x+1;
char crc8(char* p,int len){
    char res=0;
    while(len--){
        for(char i=0x80;i;i>>1){
            if(res&0x80){
                //判断最高位是否为1
                res<<=1;res^=crc_8;
                //不需要异或 左移后与0x07(x^8+x^2+x+1)异或
            }else res<<=1;
                //最高位为0 不需要异或 整体数据左移一位
            
            //if(*p&i) res^=crc_8;
        }
        p++;
    }
    return res;
}
