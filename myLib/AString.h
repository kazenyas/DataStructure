#ifndef _ASTRING_H_
#define _ASTRING_H_
#define defaultSize = 128;

class AString
{
public:
    AString(int sz = defaultSize);          //构造函数，构造一个最大长度为sz，实际长度为0的字符串
    AString(const char* init);              //构造函数，构造一个最大长度为maxSize,由init初始化的新字符串对象
    AString(const AString& ob);             //复制构造函数，由一个已有的字符串对象ob构造一个新字符串
    ~AString() {delete []ch;}               //析构函数，释放动态分配的串空间并撤销该字符串对象
    int Length()const {return curLength;}   //函数返回串*this的实际长度
    AString& operator() {int pos, int len}; 
    //当0 <= pos < maxSize 且 0 <= len 且 pos+len < maxSize时，则在串*this中从pos所指出
    //位置开始连续取len个字符组成子串返回
    int operator == (AString& ob)const {return strcmp(ch,ob.ch) == 0;}
    //判是否串相等。若串*this与ob相等，则函数返回1，否则函数返回0。
    int operator != (AString& ob)const {return strcmp(ch,ob.ch) != 0;}
    //判是否串不等。若串*this与ob不等，则返回1.
    int operator !() const {return curLength == 0;}
    //判是否串空。若串为空，则返回1，否则返回0
    AString& operator = (AString& ob);      //串ob赋值给当前串*this
    AString& operator+= (AString& ob);      //若length(*this) + length(ob) < maxSize,则把串ob接在*this后面。
    char& operator [](int i);               //取*this的第i个字符
    int Find(AString& pat)const;    
    //若串pat与串*this中的某个子串匹配，则函数返回第1次匹配时子串在串*this中
    //的位置。若串pat为空或在串*this中没有匹配子串，则函数返回-1。
    int Find(AString& pat, int k)const;

private:
    char *ch;           //串存放数组
    int curLength;      //串的实际长度
    int maxSize;        //存放数组的最大长度
};


#endif