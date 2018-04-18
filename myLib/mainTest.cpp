#include "Trituple.h"
#include <string.h>

int main()
{
    char* str1 = "word2";
    char* str2 = "word2";
    
    cout << &str1 << endl << &str2 << endl;
    str2 = _strdup(str1);

    cout << &str1 << endl << &str2 << endl;
    char *p;
    p = _strdup(str1);
    cout << *p << &p;
    return 0;
}