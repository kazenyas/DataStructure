#include <iostream.h>
#include <stdlib.h>

const int defaultSize = 100;
template <class T>
class SeqList
{
    protected:
        T *data;        //存放数组
        int maxSize;    //最大可容纳表项的项数
        int last;       //当前已存表项的最后位置（从0开始）
        void reSize(int newSize);   //改变data数组空间的大小
    public:
        SeqList(int sz = defaultSize);      //构造函数
        SeqList(SeqList<T>& L);             //复制构造函数
        ~SeqList(){delete[] data;}          //析构函数
        int Size()const{return maxSize;}    //计算表最大可容纳表项个数
        int Length()const{return last + 1;} //计算表长度
        int Search(T& x)const;              //搜索 x 在表中位置，函数返回表项序号
        int Locate(int i)const;             //定位第 i 个表项，函数返回表项序号
        bool getData(int i, T& x)const      //取第i个表项的值
        { if(i > 0 && i <= last+1)  {x = data[i-1]; return true;}   else return false;}
        void setData(int i, T& x)           //用 x 修改第 i 个表项的值
        { if(i > 0 && i <= last+1)  data[i-1] = x;}
        bool Insert(int i, T& x);           //插入x 在第i个表项之后
        bool Remove(int i,T& x);            //删除第i个表项，通过x返回表项的值
        bool IsEmpty(){return (last == -1)?true:false;}
                                            //判断表空否，空则返回true;
        bool IsFull(){return (last == maxSize-1)?true:false;}
                                            //判断表满否，满则返回true;
        void input();                       //输入
        void output();                      //输出
        SeqList<T> operator=(SeqList<T>& L);    //表整体赋值

};

template <class T>
SeqList<T>::SeqList(int sz)             //构造函数，通过指定参数sz定义数组的长度
{
    if (sz > 0)
    {
        maxSize = sz; last = -1;            //置表的实际长度为空
        data = new T[maxSize];              //创建顺序表存储数组
        if (data == NULL)                   //动态分配失败
        { cerr << "存储分配失败！" << endl; exit(1);}
    }
}

template <class T>
SeqList<T>::SeqList(SeqList<T>& L)          //复制构造函数，用参数表中给出的已有顺序表初始化新建的顺序表
{
    maxSize = L.Size(); last = L.Length()-1; T value;
    data = new T[maxSize];                  //创建顺序表存储数组
    if (data == NULL)                       //动态分配失败
    { cerr << "存储分配错误！" << endl; exit(1);}
    for (int i = 1; i <= last+1; i++)
    {L.getData(i,value); data[i-1] = value;}
}

template <class T>
void SeqList<T>::reSize(int newSize)    //私有函数：扩充顺序表的存储数组空间大小，新数组的元素个数为 newSize。
{
    if (newSize <= 0)
    { cerr << "无效的数组大小" << endl; return;}
    if (newSize != maxSize)             //建立新数组
    {
        T* newarray = new T[newSize];
        if (newarray == NULL)
        { cerr << "存储分配错误"<< endl; exit(1);}
        int n = last+1;                
        T *srcptr = data;               //源数组首地址
        T *destptr = newarray;          //目标数组首地址
        while(n--) *destptr++ = *destptr++;     //复制
        delete []data;
        data = newarray; maxSize = newSize;
    }
}

template <class T>
int SeqList<T>::Search(T &x)const       //搜索函数：在表中顺序搜索与给定值 x 相匹配的表项，找到则返回该表项是第几个元素。
{
    for (int i = 0; i <= last; i++)     //顺序搜索
        if (data[i] == x) return i+1;   //搜索成功
    return 0;
}

template <class T>
int SeqList<T>::Locate(int i)const      //定位函数：返回第i个表项的位置，否则函数返回0，表示定位失败
{
    if (i >= 1&& i <= last+1) return i;
    else return 0;
}

template <class T>
bool SeqList<T>::Insert(int i, T& x)     
//将新元素x插入到表中第i（0<=i<=last+1）个表项之后。函数返回插入成功的信息，若插入成功则返回true。i = 0是虚拟的，实际上是插入到第一个元素位置
{
    if (last == maxSize-1) return false;        //表满，不能插入
    if (i <0 || i > last+1) return false;       //参数i不合理，不能插入
    for (int j = last; j >= i; j--)
        data[j+1] = data[j];                    //依次后移，空出第i号位置
    data[i] = x;                                //插入
    last++;
    return true;
}

template <class T>
bool SeqList<T>::Remove(int i, T& x)
//从表中删除第i(1<=i<=last+1)个表项，通过引用型参数x返回删除的元素值。函数返回删除
//成功的信息，弱删除成功则返回true，否则返回false
{
    if (last == -1) return false;               //表空，不能删除
    if (i < 1 || i > last+1) return false;      //参数i不合理，不能删除
    x = data[i-1];                              //保存被删除的值
    for (int j = i; j <= last; j++)
        data[j-1] = data[j];                    //依次前移，填补
    last--;                                     //最后位置减1
    return true;                                //删除成功    
}

template <class T>
void SeqList<T>::input()            //从标准输入逐个数据输入，建立顺序表
{
    while(1){
        cout << "开始建立顺序表，请输入表中元素个数：";
        cin >> last;
        if (last <= maxSize-1) break;
        cout << "表元素个数输入有误，范围不能超过" << maxSize - 1 << endl;
    }
    for (int i = 0; i < last; i++)
    { cout <<"#"<< i+1 <<":"; cin >> data[i];}
}

template <class T>
void SeqList<T>::output()
{
    cout << "顺序表当前元素的最后位置为：" << last << endl;
    for (int i = 0; i < last; i++)
        cout << "#" << i+1 << ":" << data[i] << endl;
}