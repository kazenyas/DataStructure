#include <iostream.h>
#include <stdlib.h>
const int DefaultSize = 100;

template <class T>
class Trituple                      //三元组类Trituple
{
    public:
        Trituple(Trituple<T>& t){row = t.row; col = t.col; value = t.value;}
        int row, col;               //非零元素的行号、列号
        T value;                    //非零元素的值
        friend Trituple<T>& operator =(Trituple<T>& x);  //结点赋值
};

template<class T>
Trituple<T>& operator =(Trituple<T>& x)
{
    row = t.row; col = t.col; value = t.value;
}

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
SparseMatrix<T> SparseMatrix<T>::transpose()
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
SparseMatrix<T> SparseMatrix<T>::Add(SparseMatrix<T> b){
//两个稀疏矩阵A（*this指示）与B（参数表中的b）相加，结果在Result中

}