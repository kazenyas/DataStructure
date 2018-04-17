#ifndef _LINKEDLIST_h_
#define _LINKEDLIST_H_

#include<iostream.h>

template <class T>      //List类的前视声明
class List;



template <class T>
class LinkNode
{
    typedef LinkNode<T>* nPTR;

public:
    friend class List<T>;
    LinkNode(nPTR node = NULL):link(node){ };
    LinkNode(T dat,nPTR node = NULL):data(dat),link(node){ };

private:
    T data;
    nPTR link;
};

template <class T>
class List
{
    typedef LinkNode<T> node;
    typedef LinkNode<T>* nPTR;

public:
    List(){first = new node;};
    List(const T&x){first = new node(x);}
    List(List<T>& L);
    ~List(){makeEmpty();}               //析构函数
    void makeEmpty();                   //将链表置为空表
    int Length()const;                  //计算链表的长度
    nPTR getHead()const{return first;}  //返回附加头结点地址
    nPTR Search(T x);                   //搜索含数据x的元素
    nPTR Locate(int i);                 //搜索第i个元素的地址
    bool getData(int i,T& x)const;      //取出第i个元素的值
    void setData(int i,T x);           //用x修改第i个元素的值
    bool Insert(int i,T x);         //插入操作
    bool Remove(int i,T& x);            //删除操作，通过x返回
    bool IsEmpty()const                 //判表空否？空则返回true
    { return first->link == NULL?true:false;}
    bool IsFull()const {return false;}  //判表满否？不满则返回false
    void Sort();                        //排序
    void input();                       //输入
    void output();                      //输出
    List<T>& operator=(List<T>& L);     //重载函数：赋值

private:
    nPTR first;
};

template <class T>
List<T>::List(List<T>& L)               
//复制构造函数
{
    T value;
    nPTR srcptr = L.getHead();          //被复制的表的附加头结点地址
    nPTR destptr = first = new node;    
    while (scrptr->link != NULL)        //逐个结点复制
    {
        value = srcptr->link->data;
        destptr->link = new node(value);    
        destptr = destptr->link;
        srcptr = srcptr->link;
        destptr->link = NULL;
    }
}

template <class T>
void List<T>::makeEmpty()            
//将链表置为空表
{
    nPTR q;
    while(first->link != NULL)          //当链不空时，删去链中所有结点
    {
        q = first->link;
        first->link = q->link;          //保存被删结点，从链上摘下该结点
        delete q;
    }
}

template <class T>
int List<T>::Length()const          
//计算带附加头结点的单链表的长度
{
    nPTR = first->link; int count = 0;
    while (p != NULL)
    {
        p = p->link; count++;
    }
    return count;
}

template <class T>            
LinkNode<T>* List<T>::Search(T x)      
//在表中搜索含数据x的结点。搜索成功时，函数返回该结点地址；
{
    LinkNode<T>* current = first->link;
    while(current != NULL)
        if (current->data == x) break;      //循环找含x的结点
        else current = current->link;
    return current;
}

template <class T>
LinkNode<T>* List<T>::Locate(int i)
//定位函数。返回表中第i个元素的地址
{
    if (i<0) return NULL;           //参数不合理
    LinkNode<T>* current = first; int k = 0;    
    while (current != NULL && k < i)        //循环找第i个结点
    {
        current = current->link; k++;
    }
    return current;                         //返回第i个结点地址，若返回NULL，表示i值太大
}

template <class T>
bool List<T>::getData(int i,T& x)const
//取出链表中第i个元素的值
{
    if (i<=0) return NULL;                  //i太小
    nPTR current = Locate(i);
    if (current == NULL) return false;      //i太大
    else {x = current->data; return false;}
}

template <class T>
void List<T>::setData(int i,T x)
//给链表中第i个元素赋值x
{
    if(i<=0) return NULL;
    nPTR current = Locate(i);
    if (current == NULL) return;
    else current->data = x;
}

template <class T>
bool List<T>::Insert(int i,T x)
//讲新元素x插入在链表中第i个结点之后
{
    nPTR current = Locate(i);
    if (current == NULL) return false;
    nPTR newNode = new node(x);
    if (newNode == NULL) {cerr << "存储分配错误！"<<endl; exit(1);}
    newNode->link = current->link;          //链接在current之后
    current->link = newNode;
    return true;                            //插入成功
}

template <class T>
bool List<T>::Remove(int i,T& x)
//将链表中的第i个元素删去，通过引用型参数x返回该元素的值
{
    nPTR current = Locate(i-1);
    if (current == NULL || current->link == NULL) return false;         //删除不成功
    nPTR del = current->link;           //重新拉链，将被删结点从链中摘下
    current->link = del->link;
    x = del->data; delete del;          //取出被删结点中的数据值
    return true;
}

template <class T>
void List<T>::input()
//单链表的输入函数
{
    int n;
    T x;
    nPTR ptr = first;
    cout << "请输入链表元素个数：";
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cout << "#"<<i<<":";
        cin >> x;
        while(ptr->link != NULL)
        {
            ptr = ptr->link;
        }
        ptr->link = new node(x);
    }
}

template <class T>
void List<T>::output()
//单链表的输出函数：将单链表中所有数据按逻辑顺序输出到屏幕上
{
    nPTR current = first->link;
    while (current != NULL)
    {
        cout<<current->data<<endl;
        current = current->link;
    }
}

template <class T>
List<T>& List<T>::operator =(List<T>& L)
//重载函数：赋值操作，形式如A=B，其中A是调用此操作的List对象，B是与参数表中的
//引用型参数L结合的参数
{
    T value;
    nPTR srcptr = L.getHead();          //被复制表的附加头结点地址
    nPTR destptr = first = new node;
    while (srcptr->link != NULL)        //逐个结点复制
    {
        value = srcptr->link->data;
        destptr->link = new node(value);
        destptr = destptr->link;
        srcptr = srcptr->link;
    }
    destptr->link = NULL;
    return *this;
}

#endif