#include <assert.h>
#include <iostream.h>

template <class T>
class SeqQueue
{
    public:
        SeqQueue(int sz = 10);
        ~SeqQueue() {delete[] elements;}
        bool EnQueue(const T& x);
        bool DeQueue(T& x);
        bool getFront(T& x)const;
        void makeEmpty() {front = rear = 0;}
        bool IsEmpty() const {return (front == rear) ? true:false;}
        bool IsFull()const
        {return ((rear+1)%maxSize == front)?true:false;}
        int getSize()const {return (rear-front+maxSize)%maxSize;}
        friend ostream& operator << (ostream& out,SeqQueue<T>& Q);

    private:
        int rear, front;
        T* elements;
        int maxSize;
};

template <class T>
SeqQueue<T>::SeqQueue(int sz) : front(0), rear(0), maxSize(sz){
    elements = new T[maxSize];
    assert(elements != NULL);
}

template <class T>
bool SeqQueue<T>::EnQueue(const T& x){
    if ((IsFull()==true)) return false;
    elements[rear] = x;
    rear = (rear+1)%maxSize;
    return true;
}

template <class T>
bool SeqQueue<T>::DeQueue(T& x){
    if(IsEmpty() == true) return false;
    x = elements[front];
    front = (front+1)%maxSize;
    return true;
}

template <class T>
bool SeqQueue<T>::getFront(T& x)const{
    if (IsEmpty()==true) return false;
    x = elements[front];
    return true;
}

template <class T>
ostream& operator << (ostream& out, SeqQueue<T>& Q){
    out << "front = " << Q.front << ", rear = " << Q.rear << endl;
    for(int i = Q.front; i != Q.rear; i = (i+1)%(Q.maxSize))
        out << i << ":" << Q.elements[i] << endl;
    return out;
}
