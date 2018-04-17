#include <assert.h>
#include <iostream.h>
const int stackIncreament = 20;

template <class T>
class SeqStack
{
    public:
        SeqStack(int sz = 50);
        ~SeqStack(){delete []elements;}
        void Push(const T& x);
        bool Pop(T& x);s
        bool getTop(T& x);
        bool IsEmpty()const{return (top==-1)?true:false;}
        bool IsFull()const{return (top == maxSize)?true:false;}
        int getSize()const {return top+1;}
        void MakeEmpty() {top=-1;}
        friend ostream& operator <<(ostream& os, SeqStack<T>& s);
    private:
        T *elements;
        int top;
        int maxSize;
        void overflowProcess();

};

template <class T>
SeqStack<T>::SeqStack(int sz):top(-1),maxSize(sz)
{
    elements = new T[maxSize];
    assert(elements != NULL);
}

template <class T>
void SeqStack<T>::overflowProcess()
{
    T *newArray = new T[maxSize + stackIncreament];
    if (newArray = NULL) {cerr << "´æ´¢·ÖÅäÊ§°Ü£¡"<<endl; exit(1);}
    for (int i = 0; i <= top; i++) newArray[i] = elements[i];
    maxSize = maxSize + stackIncreament;
    delete []elements;
    elements = newArray;
}

template <class T>
void SeqStack<T>::Push(const T& x)
{
    if (IsFull() == true) overflowProcess();
    elements[++top] = x;
}

template <class T>
bool SeqStack<T>::Pop(T& x)
{
    if (IsEmpty() == true) return false;
    x = elements[top--];
    return true;
}

template <class T>
bool SeqStack<T>::getTop(T& x)
{
    if (IsEmpty() == true) return false;
    x = elements[top];
    return true;
}

template <class T>
ostream& operator << (ostream& out, SeqStack<T>& s)
{
    out << "top = " << s.top << endl;
    for (int i = 0; i <= s.top; i++)
        out << i << ":" << s.elements[i] << endl;
    return out;
}
