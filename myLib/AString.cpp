#include "AString.h"

AString::AString(int sz)    //串构造函数
{
    maxSize = sz;
    ch = new char[maxSize+1];
    if (ch == NULL) {cerr << "Allocation Error\n";exit(1);}
    curLength = 0; ch[0] = '\0';
}

AString::AString(const char *init)  //串构造函数
{
    int len = strlen(init);
    maxSize = (len>defaultSize)?len:defaultSize;
    ch = new char[maxSize+1];
    if (ch == NULL) { cerr << "Allocation Error\n"; exit(1);}
    curLength = len;
    strcpy(ch,init);
}

AString::AString(const AString& ob){    //串复制构造函数
    maxSize = ob.maxSize;
    ch = new char[maxSize+1];
    if (ch == NULL) {cerr << "存储分配失败\n"; exit(1);}
    curLength = ob.curLength;
    strcpy(ch,ob.ch);
}

AString AString::operator() (int pos, int len){ //求子串
    AString temp;
    if (pos < 0 || pos+len-1>=maxSize || len<0){
        temp.curLength = 0; temp.ch[0] = '\0';
    }
    else{
        if (pos+len-1 >= curLength) len = curLength-pos;
        temp.curLength = len;
        for (int i = 0, j = pos; i < len; i++,j++) temp.ch[i] = ch[j];
        temp.ch[len] = '\0';
    }
    return temp;
}

AString& AString::operator=(const AString& ob){     //串重载操作：串赋值
    if (&ob != this){
        delete[]ch;
        ch = new char[ob.maxSize];                  //重新分配
        if (ch == NULL) {cerr << "存储分配失败!\n"; exit(1);}
        curLength = ob.curLength;
        strcpy(ch,ob.ch);
    }
    else cout << "字符串自身赋值出错！\n";
    return *this;
}

AString& AString::operator+=(const AString& ob){    //串重载操作：串连接
    char *temp = ch;                //暂存原串数组
    int n = curLength + ob.curLength;   //串长度增加
    int m = (maxSize >= n)? maxSize:n;  
    ch = new char[m];
    if (ch == NULL) {cerr << "存储分配错！\n"; exit(1);}
    maxSize = m; curLength = n;
    strcpy(ch,temp);                    //复制原串数组
    strcat(ch,ob.ch);                   //连接ob串数组
    delete []temp; return *this;
}

AString& AString::operator+= (const AString& ob){   //串重载操作：串连接
    char *temp = ch;                    //暂存原串数组
    int n = curLength+ob.curLength;     //串长度增加
    int m = (maxSize >= n)?maxSize:n;
    ch = new char[m];
    if (ch == NULL) {cerr << "存储分配错！\n"; exit(1);}
    maxSize = m;    curLength = n;
    strcpy(ch,temp);                    //复制原串数组
    strcat(ch,ob.ch);                   //连接ob串数组
    delete []temp;  return *this;
}

char AString::operator[] (int i){       //串重载操作：取当前串*this的第i个字符
    if (i < 0 || i >= curLength)
    { cout << "字符串下标超界！\n"; exit(1);}
    return ch[i];
}

int AString::Find(AString& pat, int k)const{
    //在当前串（目标*this）中从第k个字符开始寻找模式pat在当前串中匹配的位置。若在
    //当前串（*this）中找不到与串pat匹配的子串，则函数返回-1，否则返回pat在当前
    //串（*this）中第一次匹配的位置
    int i,j;
    for (i = k; i <= curLength - pat.curLength; i++) {  //逐趟比较
        for (j = 0; j < pat.curLength; j++)
            //从ch[i]开始的子串与模式pat.ch进行比较
            if (ch[i+j]!=pat.ch[j]) break;
            if (j == pat.curLength) return i;           //pat扫描完，匹配成功
    }
    return -1;                              //pat为空或*this中找不到它
}