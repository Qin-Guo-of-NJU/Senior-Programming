/*
写在前面：
1、所有注释均为手动添加，非AI生成
2、所有与AI使用相关的内容都在注释中写出
*/
#include<iostream>
using namespace std;
class Matrix{
public:
    Matrix(int r,int c);//构造函数
    Matrix(const Matrix &other);//拷贝
    ~Matrix();//析构函数
    int getRows()const;
    int getCols()const;
    int getElement(int i,int j)const;
    void setElement(int i,int j,int val);
    Matrix add(const Matrix &other)const;
    Matrix sub(const Matrix& other)const;
    static int matrixCount;
    static int getMatrixCount();
private:
//TO DO 用什么数据结构实现矩阵？不知道矩阵的大小，用二级指针，在构造函数中创建方便一点
    int row;//行，横着的
    int col;//列，竖着的
    int** mat;
};
int Matrix::matrixCount=0;//忘记初始化了，AI指出的错误
Matrix::Matrix(int r,int c):row(r),col(c){
    //TO DO
    mat=new int* [row];
    for (int i=0;i<row;i++){
        mat[i]=new int[col]();//此处加括号能将元素初始化为0，向AI学习的
    }
    matrixCount++;
}
Matrix::~Matrix(){
    //TO DO
    for (int i=0;i<row;i++){
        delete[] mat[i];
    }
    delete[] mat;
    matrixCount--;
}
Matrix::Matrix(const Matrix &other){//拷贝
    //TO DO  
    /*这里一开始一直报错，我本打算创建一个类，复制数据后返回这个类，但是报错说我没有默认构造函数。
    我后来想一下，这个拷贝函数是一个method，它是对于类的一个操作，所以直接使用类本身的数据就可以
    报错应该是因为类的内部再创建类会有无限循环，所以类的method 不能调用自己的构造函数
    
    对不起，我又问了一下AI，上面是在胡说八道
    这个函数也是个构造函数，构造函数里不能创建类对象，但是method里可以创建，否则怎么实现加法和乘法呢！！！
    */
    row=other.row;
    col=other.col;
    for (int i=0;i<row;i++){
        mat[i]=new int[col]();
    }
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            mat[i][j]=other.mat[i][j];
        }
    }
    matrixCount++;
}
int Matrix::getRows()const{
    return row;
}
int Matrix::getCols()const{
    return col;
}
int Matrix::getMatrixCount(){
    return matrixCount;
}
int Matrix::getElement(int i,int j)const{
    //TO DO
    return mat[i][j];
}
void Matrix::setElement(int i,int j,int val){
    //TO DO
    mat[i][j]=val;
}

Matrix Matrix::add(const Matrix & other)const{
    //TO DO
    Matrix result(row,col);
    for (int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            result.mat[i][j]=mat[i][j]+other.mat[i][j];
        }
    }
    return result;

}
Matrix Matrix::sub(const Matrix & other)const{
    //TO DO
    Matrix result(row,other.col);
    for (int i=0;i<row;i++){
        for (int j=0;j<other.col;j++){
            
            result.mat[i][j]=mat[i][j]-other.mat[i][j];
        }
    }
    return result;
}

//以下测试程序和打印函数为AI生成
//添加打印函数



void printMatrix(const Matrix& m, const string& name) {
    cout << name << " (" << m.getRows() << "x" << m.getCols() << "):" << endl;
    for (int i = 0; i < m.getRows(); i++) {
        for (int j = 0; j < m.getCols(); j++) {
            cout << m.getElement(i, j) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {









    cout << "========== Matrix Class Test ==========" << endl;
    cout << "Initial matrix count: " << Matrix::getMatrixCount() << endl << endl;
    
    // Test 1: Constructor
    cout << "----- Test 1: Constructor -----" << endl;
    Matrix m1(2, 3);
    cout << "After creating m1: " << Matrix::getMatrixCount() << endl;
    cout << "Created m1(2x3), count: " << Matrix::getMatrixCount() << endl;
    
    // Set values
    int val = 1;
    for (int i = 0; i < m1.getRows(); i++) {
        for (int j = 0; j < m1.getCols(); j++) {
            m1.setElement(i, j, val++);
        }
    }
    printMatrix(m1, "m1");
    
    // Test 2: Copy constructor
    cout << "----- Test 2: Copy constructor -----" << endl;
    Matrix m2 = m1;
    cout << "After creating m2: " << Matrix::getMatrixCount() << endl;
    cout << "Created m2(copy of m1), count: " << Matrix::getMatrixCount() << endl;
    printMatrix(m2, "m2");
    
    // Test 3: Matrix addition
    cout << "----- Test 3: Matrix addition -----" << endl;
    Matrix a(2, 2);
    cout << "After creating a: " << Matrix::getMatrixCount() << endl;
    Matrix b(2, 2);
    cout << "After creating b: " << Matrix::getMatrixCount() << endl;
    
    a.setElement(0, 0, 1); a.setElement(0, 1, 2);
    a.setElement(1, 0, 3); a.setElement(1, 1, 4);
    
    b.setElement(0, 0, 5); b.setElement(0, 1, 6);
    b.setElement(1, 0, 7); b.setElement(1, 1, 8);
    
    printMatrix(a, "a");
    printMatrix(b, "b");
    
    Matrix c = a.add(b);
    cout << "After a.add(b): " << Matrix::getMatrixCount() << endl;
    cout << "c = a + b" << endl;
    printMatrix(c, "c");
    
    // Test 4: Matrix subtraction
    cout << "----- Test 4: Matrix subtraction -----" << endl;
    Matrix d = a.sub(b);
    cout << "After a.sub(b): " << Matrix::getMatrixCount() << endl;
    cout << "d = a - b" << endl;
    printMatrix(d, "d");
    
    // Test 5: Object count
    cout << "----- Test 5: Object count -----" << endl;
    cout << "Current matrix count: " << Matrix::getMatrixCount() << endl;
    {
        Matrix temp1(1, 1);
        Matrix temp2(2, 2);
        cout << "Created 2 temporary matrices inside block" << endl;
        cout << "Count inside block: " << Matrix::getMatrixCount() << endl;
    }
    cout << "After block, count: " << Matrix::getMatrixCount() << endl;
    
    cout << "========== Test Complete ==========" << endl;
    cout << "Final matrix count: " << Matrix::getMatrixCount() << endl;
    
    return 0;
}