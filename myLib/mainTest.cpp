#include "PQueue.h"

int main()
{
    PQueue<int> a;
    a.Insert(11);
    a.Insert(23);
    a.Insert(32);
    a.Insert(55);
    a.Insert(5);
    a.Insert(2);
    a.Insert(9);

    int min;
    while(!a.IsEmpty()){
        a.RemoveMin(min);
        cout << min << endl;
    }
    return 0;
}