//加注释是为了方便自己理解，不是AI生成的
#include<iostream>
using namespace std;
class Queue{
private:
    int num;//队列元素数量
    struct Node{
        long long val;
        Node* next;
    }* top;
public:
    Queue();
    void join(long long x);//入队
    void get_out();//弹出并输出队列头部元素
    void request();//输出队列头部元素


};
Queue::Queue(){
    num=0;
    top=nullptr;
}
void Queue::join(long long x){
    Node* newNode=new Node;
    newNode->val=x;
    newNode->next=top;
    top=newNode;
    num++;
}
void Queue::get_out(){
    if (num==0){
        cout<<"Error"<<endl;
        return;
    }
    if (num==1){
        delete top;
        top=nullptr;
        num--;
        return;
    }
    Node* current=top;
    Node* prev=top;
    for (int i=0;i<num-1;i++){prev=current;
        current=current->next;
    }
    
    long long x=current->val;
    cout<<x<<endl;
    delete current;
    prev->next=nullptr;
    num--;
    return;
}
void Queue::request(){
if (num==0){
        cout<<"Error"<<endl;
        return;
    }
    Node* current=top;
    for (int i=0;i<num-1;i++)current=current->next;
    long long x=current->val;
    cout<<x<<endl;
}
int main(){
    int total_operation;
    cin>>total_operation;
    Queue queue;
    for (int i=0;i<total_operation;i++){
        int operate;
        cin>>operate;
        if (operate==1){
            long long x;
            cin>>x;
            queue.join(x);
        }
        else if(operate==2){
            queue.get_out();
        }
        else//operate==3
        {
            queue.request();
        }
    }
    return 0;
}