/*我向DeepSeek学习了C++继承的语法、纯虚函数的概念，提示词如下：
1、（第二题的题目要求）这是我的高级程序设计课程作业，我希望你告诉我关于这道题可能用到的知识和C++语法，不要告诉我题目答案。
2、表格有大小（一个整数）和一个链表（实现表格），我应该把这两个数据定义在抽象线性表类的private里还是在派生类中定义？
在抽象基类private里定义，派生类能访问吗？如果定义不同派生类共享一个抽象类，访问时不会互相影响吧？
3、我完成了，请你提供测试用例，我测试一下
以及，代码中所有注释都是我自己手写，方便理解，非AI生成
*/ 

#include<iostream>
using namespace std;
class limited_linear_table{
protected:
    int num;//表格大小
    struct Node{
        long long val;
        Node* next;
    }* top;
public:
limited_linear_table();
virtual void insert(long long x)=0;
virtual void remove()=0;
virtual void get_top_element()=0;
};
limited_linear_table::limited_linear_table(){
    num=0;
    top=nullptr;
}
class Queue: protected limited_linear_table{
public:
void insert(long long x){
    Node* newNode=new Node;
    newNode->val=x;
    newNode->next=top;
    top=newNode;
    num++;
}
void remove(){
    if (num==0){
        cout<<"error"<<endl;
        return;
    }
    if (num==1){//这个是特殊情况，prev没有在current前面，特殊处理
        delete top;
        top=nullptr;
        num--;
        return;
    }
    Node* current=top;
    Node* prev=top;
    for (int i=0;i<num-1;i++){
        prev=current;
        current=current->next;
    }
    
    delete current;
    prev->next=nullptr;
    num--;
    return;
}
void get_top_element(){
if (num==0){
        cout<<"error"<<endl;
        return;
    }
    Node* current=top;
    for (int i=0;i<num-1;i++)current=current->next;
    long long x=current->val;
    cout<<x<<endl;
}
};
class Stack: protected limited_linear_table{
public:
void insert(long long x){
    Node* newNode=new Node;
    newNode->val=x;
    newNode->next=top;
    top=newNode;
    num++;
}
void get_top_element(){
if (num==0){
        cout<<"error"<<endl;
        return;
    }
    cout<<top->val<<endl;
}
void remove(){
    if (num==0){
        cout<<"error"<<endl;
        return;
    }
    Node* current=top;
    top=top->next;
    delete current;
    num--;
    return;
}
};
void check_Stack(){
    Stack stack;
    int total_operation;//操作总数
    cin>>total_operation;
    for (int i=0;i<total_operation;i++){
        int operate;//操作类型
        cin>>operate;
        if (operate==1){//插入表内
            long long elem;
            cin>>elem;
            stack.insert(elem);
        }
        else if (operate==2){//删除头部元素
            stack.remove();
        }
        else{//输出头部元素
            stack.get_top_element();
        }
    }
}
void check_Queue(){
    Queue queue;
    int total_operation;//操作总数
    cin>>total_operation;
    for (int i=0;i<total_operation;i++){
        int operate;//操作类型
        cin>>operate;
        if (operate==1){//插入表内
            long long elem;
            cin>>elem;
            queue.insert(elem);
        }
        else if (operate==2){//删除头部元素
            queue.remove();
        }
        else{//输出头部元素
            queue.get_top_element();
        }
    }
}
int main(){
    int T;//测试用例数量
    cin>>T;
    for (int i=0;i<T;i++){
        char check;
        cin>>check;
        if (check=='S'){//栈
            check_Stack();
        }
        else{//队列
            check_Queue();
        }
    }
    return 0;
}