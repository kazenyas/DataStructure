#include <iostream.h>
#include <stdlib.h>
const int DefaultSize = 100;
#define zero 0


template <class T>
class Trituple                      //三元组类Trituple
{
    public:
        Trituple() {row = col = 0; value = zero;}
        Trituple(Trituple<T>& t){row = t.row; col = t.col; value = t.value;}
        int row, col;               //非零元素的行号、列号
        T value;                    //非零元素的值
};

template <class T>
class SparseMatrix      //稀疏矩阵的类声明
{
    friend ostream& operator << (ostream& out, SparseMatrix<T>& M);
                                    //友元函数：输出流操作符重载
    friend istream& operator >> (istream& in, SparseMatrix<T>& M);
                                    //友元函数：输入流操作符重载
    public:
        SparseMatrix(int maxSize = DefaultSize);        //构造函数
        SparseMatrix(SparseMatrix<T>& x);               //复制构造函数
        ~SparseMatrix() {delete []smArray;}             //析构函数
        SparseMatrix<T>& operator = (SparseMatrix<T>& x);
        SparseMatrix<T> Transpose();                    //对当前稀疏矩阵对象(*this指示)执行转置运算
        SparseMatrix<T> FastTranspose();
        SparseMatrix<T> Add(SparseMatrix<T>& b);        //当前矩阵（*this指示）与矩阵b相加
        SparseMatrix<T> Multiply(SparseMatrix<T>& b);   //按公式c[i][j] = ∑(a[i][k]*b[k][j])实现当前矩阵与矩阵b相乘
    private:
        int Rows,Cols,Terms;
        Trituple<T> *smArray;
        int maxTerms;

};

template <class T>
SparseMatrix<T>::SparseMatrix(int maxSize):maxTerms(maxSize){
    if (maxSize < 1){
        cerr<<"矩阵初始化值错！"<<endl; exit(1);}
    smArray = new Trituple<T>[maxSize];
    if (smArray == NULL){
        cerr<< "存储分配错！"<< endl; exit(1);}
    Rows = Cols = Terms = 0;
}

template <class T>
SparseMatrix<T>::SparseMatrix(SparseMatrix<T>& x){
    Rows = x.Rows; Cols = x.Cols; Terms = x.Terms;
    maxTerms = x.maxTerms;
    smArray = new Trituple<T>[maxTerms];
    if (smArray == NULL){
        cerr << "存储分配错！"<<endl; exit(1);}
    for (int i = 0; i < Terms; i++) smArray[i] = x.smArray[i];
    //使用结点成员函数"="执行逐个结点复制
}

template <class T>
ostream& operator << (ostream& out, SparseMatrix<T>& M){
    out << "rows = " << M.Rows << endl;
    out << "cols = " << M.Cols << endl;
    out << "Nonzero terms = " << M.Terms << endl;
    for (int i = 0; i < M.Terms;i++)
        out << "M[" << M.smArray[i].row << "][" << M.smArray[i].col
        << "]=" << M.smArray[i].value << endl;
    return out;
}

template <class T>
istream& operator >> (istream& in, SparseMatrix<T>& M){
    cout << "Enter number of rows, columns, and terms" << endl;
    in >> M.Rows >> M.Cols >> M.Terms;
    if (M.Terms > maxTerms){
        cerr << "number of terms overflow!" <<endl; exit(1);}
    for (int i = 0; i < M.Terms; i++){
        cout << "Enter row, column, and value of term:" << i+1 << endl;
        in >> M.smArray[i].row >> M.smArray[i].col >>
            >> M.smArray[i].value;
    }
    return in;
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::Transpose()
//将稀疏矩阵a（*this指示）转置，结果在稀疏矩阵b中并通过函数返回
{
    SparseMatrix<T> b(maxTerms);            //创建一个稀疏矩阵类的对象b
    b.Rows = Cols;                          //矩阵b的行数=矩阵a的列数
    b.Cols = Rows;                          //矩阵b的列数=矩阵a的行数    
    b.Terms = Terms;                        //矩阵b的非零元素个数
    if (Terms > 0){
        int k,i,CurrentB = 0;               //存放位置指针
        for (k = 0; k < Cols; k++)          //按列号做扫描，做Cols趟
            if (smArray[i].col == k){
                b.smArray[CurrentB].row = k;
                b.smArray[CurrentB].col = smArray[i].row;
                b.smArray[CurrentB].value = smArray[i].value;
                CurrentB++;                 //存放指针进1
            }
    }
    return b;
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::FastTranspose(){
//快速转置
    int *rowSize = new int[Cols];               //辅助数组，统计各列非零元素个数
    int *rowStart = new int[Cols];              //辅助数组，预计转置后各行存放位置
    SparseMatrix<T> b(maxTerm);                 //存放转置结果
    b.Rows = Cols; b.Cols = Rows; b.Terms = Terms;
    if (Terms > 0){
        int i, j;
        for (i = 0; i < Cols; i++) rowSize[i] = 0;
        for (i = 0; i < Terms; i++) rowSize[smArray[i].col]++;
        rowStart[0] = 0;
        for (i = 1; i < Cols; i++)
            rowStart[i] = rowStart[i-1] + rowSize[i-1];
        for (i = 0; i < Terms; i++){            //从a向b传送
            j = rowStart[smArray[i].col];       //第i个非零元素在b中应放位置
            b.smArray[j].row = smArray[i].col;  
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;         //rowStart的个数更新
        }
    }
    delete []rowSize; delete []rowStart;
    return b;
}

template <class T>
SparseMatrix<T> SparseMatrix<T>::Add(SparseMatrix<T>& b){
//两个稀疏矩阵A（*this指示）与B（参数表中的b）相加，结果在Result中
    SparseMatrix<T> Result;          //结果矩阵的三元表组
    if (Rows != b.Rows || Cols != b.Cols){
        cout << "Incompatible matrices" << endl;//两个矩阵规格不一样
        return Result;
    }
    int i = 0, j = 0, index_a,index_b; Result.Terms = 0;
    while (i < Terms && j < b.Terms){
        index_a = Cols * smArray[i].row + smArray[i].col;
        index_b = Cols * b.smArray[j].row + b.smArray[j].col;
        if (index_a < index_b) {                //smArray[i]在b.smArray[j]前
            Result.smArray[Result.Terms] = smArray[i];
            i++;
        }
        else if (index_a > index_b) {           //smArray[i]在b.smArray[j]后
            Result.smArray[Result.Terms] = b.smArray[i];
            j++;
        }
        else {                                  //smArray[i]和b.smArray[j]在相同位置
            Result.smArray[Result.Terms] = smArray[i];
            Result.smArray[Result.Terms].value = smArray[i].value + b.smArray[j].value;
            i++; j++;
        }
        Result.Terms++;
    }
    //复制剩余元素
    for(; i < Terms; i++){
        Result.smArray[Result.Terms] = smArray[i];
        Result.Terms++;
    }
    for(; j < b.Terms; j++){
        Result.smArray[Result.Terms] = b.smArray[i];
        Result.Terms++;
    }
    return Result;
}   


template <class T>
SparseMatrix<T> SparseMatrix<T>::Multiply(SparseMatrix<T>& b){
    //两个稀疏矩阵a(*this指示)与b(参数表中的b)相乘，结果在Result中
    SparseMatrix<T> result;        //结果矩阵的三元组表
    if (Cols != b.Rows){
        cerr << "Incompatible matrices" << endl;    //A列数与B行数不等
        return result;                              //返回空矩阵
    }
    if (Terms == maxTerms || b.Terms == maxTerms){
        cerr << "One additional space in a or b needed" << endl;
        return result;                              //空间不足，返回空矩阵
    }
    int *rowSize = new int[b.Rows];                 //矩阵b各行非零元素个数
    int *rowStart = new int[b.Rows+1];              //矩阵b各行在三元组开始位置
    T *temp = new T[b.Cols];                        //暂存每一行计算结果
    int i, Current, LastInResult, RowA, ColA, ColB;
    for (i = 0; i < b.Rows; i++) rowSize[i] = 0;
    for (i = 0; i < b.Terms; i++) rowSize[b.smArray[i].row]++;
    rowStart[0] = 0;                                //B第i行非零元素开始位置
    for (i = 1; i <= b.Rows; i++)
        rowStart[i] = rowStart[i-1] + rowSize[i-1];
    Current = 0; LastInResult = -1;                  //a扫描指针及result存指针
    while (Current < Terms){                        //生成result的当前行temp
        RowA = smArray[Current].row;                //当前行的行号
        for (i = 0; i < b.Cols; i++) temp[i] = 0;
        while (Current < Terms && smArray[Current].row == RowA){
            ColA = smArray[Current].col;            //矩阵A当前扫描到元素的列号
            for (i = rowStart[ColA]; i < rowStart[ColA+1]; i++){
                ColB = b.smArray[i].col;            //矩阵B中相乘元素的列号
                temp[ColB] += smArray[Current].value * b.smArray[i].value;
            }                                       //A的RowA行与B的ColB列相乘
            Current++;
        }
        for (i = 0; i < b.Cols; i++)
            if (temp[i] != 0) {                     //将temp中的非零元素压缩到result中去
                LastInResult++;
                result.smArray[LastInResult].row = RowA;
                result.smArray[LastInResult].col = i;
                result.smArray[LastInResult].value = temp[i];
            }
    }
    result.Rows = Rows; result.Cols = b.Cols;
    result.Terms = LastInResult+1;
    delete []rowSize; delete []rowStart; delete []temp;
    return result;
};
