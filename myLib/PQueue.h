#include <assert.h>
#include <iostream.h>
#include <stdlib.h>
const int DefaultPQSize = 50;           //优先级队列数组的默认长度

template <class T>
class PQueue
{
    public:
        PQueue(int sz = DefaultPQSize);         //构造函数
        ~PQueue() {delete []pqelements;}        //析构函数
        bool Insert(const T& x);                //将新元素x插入到队尾
        bool RemoveMin(T& x);                   //将队首元素删去
        bool getFront(T& x)const;               //读取队首元素（最小优先权）的值
        void makeEmpty() {count = 0;}           //置优先级队列为空
        bool IsEmpty()const{                    //判队列空否
            return (count == 0)?true:false;}
        bool IsFull()const                      //判队列满否
        {return (count == maxSize)?true:false;} 
        int getSize()const {return count;}      //求优先级队列中元素个数
    private:
        T* pqelements;                          //优先级队列数组
        int count;                              //当前元素个数（长度）
        int maxSize;                            //队列最大可容纳元素个数
        void adjust();
};

template <class T>
PQueue<T>::PQueue(int sz): maxSize(sz), count(0){
//构造函数：建立一个最大具有maxSize个元素的空优先级队列。
    pqelements = new T[maxSize];                //创建队列空间
    assert(pqelements != NULL);                 //断言：动态存储分配成功与否
}

template <class T>
bool PQueue<T>::Insert(const T& x){
//若优先级队列不满，则将元素x插入到该队列队尾，否则出错处理
    if (count == maxSize) return false;         //队列满则函数返回
    pqelements[count++] = x;                    //插入x到队尾
    adjust();                                   //按优先权进行调整
    return true;
}

template <class T>
void PQueue<T>::adjust(){
//将队尾元素按其优先权大小调整到适当位置，保持所有元素按优先权从小到大有序
    T temp = pqelements[count-1];
    int left = -1,right = count;                //形成包围所有数的空间，假设【-1】【count】是存在最小、大值数位置
  /*
    int j;  
    for (j = count-2; j >= 0; j--)
        if (pqelements[j] <= temp) break;       //发现有比temp更小或相等的pqelements[j] 跳出循环
        else pqelements[j+1] = pqelements[j];   //比temp大的元素 pqelements[j] 后移
    pqelements[j+1] = temp;                     //插入到适当位置
*/
    
    for(int mid = (left + right)/2; (right-left)>1;)    //插入位置count-1之前的序列已经有序，二分查找合理排序位置
    {
        if (pqelements[mid] < temp)                      //中值小于插入值，将左区间缩小至中值
            left = mid;
        else right = mid;                               //否则缩小右区间
        mid = (left + right)/2;
    }
    for(int i = count-1; i > left+1;i--)                //将左区间left+1 ~ count-2的值向右移一格
        pqelements[i] = pqelements[i-1];
    pqelements[left+1] = temp;                          //将插入值插入left+1
    
}

template <class T>
bool PQueue<T>::RemoveMin(T& x){
//若优先级队列不空则函数返回该队列具有最大优先权（值最小）元素的值，同时将该元素删除。
    if(count == 0) return false;                //若队列空，函数返回false
    x = pqelements[0];
    for(int i = 1; i < count; i++) pqelements[i-1] = pqelements[i];
    count--;                                    //优先级队列元素个数减一
    return true;                                //删除成功，返回true
}

