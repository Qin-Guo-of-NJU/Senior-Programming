/*
###写在前面###
1、所有注释均为手动添加
2、使用链表实现growAll和析构函数功能
*/
#include<iostream>
using namespace std;
class Pet;
struct PetNode{
    Pet* pet;//这里和AI讨论过，用指针保证多态性，可以指向任何P儿童派生类对象
    PetNode* next;
    PetNode(Pet* p):pet(p),next(nullptr){}
};
class Pet{
protected:
    int WEIGHT;//体重数值
    int AGE;//年龄数值
    static PetNode* head;
public:
    Pet(int age,int weight);
    void changeWeight(int w);
    int weight();//return WEIGHT
    int age();//return AGE
    virtual void meow() const=0;
    virtual ~Pet(){
        PetNode* prev=nullptr;
        PetNode* curr=Pet::head;
        while (curr!=nullptr){
            if (curr->pet==this){//找到对应节点
                if (prev==nullptr)//头节点
                {
                    head=curr->next;
                    
                }
                else{
                    prev->next=curr->next;
                }
                delete curr;
                break;
            }
            prev=curr;
            curr=curr->next;
        }
    }
    static void growAll(){
        
            PetNode* curr=head;
            while(curr!=nullptr){
                if (curr->pet!=nullptr){
                curr->pet->AGE++;}
                curr=curr->next;
            }
        
        };
};
Pet::Pet(int age,int weight) :AGE(age),WEIGHT(weight){//这里构建链表的方式类似栈
    PetNode* newNode= new PetNode(this);
    newNode->next=head;
    head=newNode;
}
int Pet::weight(){return WEIGHT;}
int Pet::age(){return AGE;}
void Pet::changeWeight(int w){
    WEIGHT+=w;
};
PetNode* Pet::head=nullptr;//初始化头指针
class Cat:public Pet{
public:
    Cat(int age,int weight):Pet(age,weight){}//这一行什么原理？我知道这是个构造函数，不过第一次见这个语法，上次做线性表的时候不需要构造函数
    /*AI回答：初始化列表语法
    含义是：
    1、Cat构造函数执行前，先调用Pet构造函数
    2、传递参数
    3、相当于先初始化基类，在初始化派生类*/
    void meow()const override{
        cout<<"miao"<<endl;
    }
    
};
class Dog:public Pet{
public:
    Dog(int age,int weight):Pet(age,weight){}
    void meow()const override{
        cout<<"wang wang"<<endl;
    }
};
//以下测试函数由DeepSeek生成
int main(){
    cout << "=== Blue Whale Pet System Test ===" << endl;
    
    // Create pet objects
    cout << "\n1. Creating pets:" << endl;
    Cat* cat1 = new Cat(2, 5);   // 2 years old, 5kg
    Dog* dog1 = new Dog(3, 10);  // 3 years old, 10kg
    Cat* cat2 = new Cat(1, 4);   // 1 year old, 4kg
    
    cout << "Created: 2-year-old cat, 3-year-old dog, 1-year-old cat" << endl;
    
    // Test age() and weight() functions
    cout << "\n2. Testing age() and weight() functions:" << endl;
    cout << "Cat1 - Age: " << cat1->age() << " years, Weight: " << cat1->weight() << "kg" << endl;
    cout << "Dog1 - Age: " << dog1->age() << " years, Weight: " << dog1->weight() << "kg" << endl;
    cout << "Cat2 - Age: " << cat2->age() << " years, Weight: " << cat2->weight() << "kg" << endl;
    
    // Test changeWeight() function
    cout << "\n3. Testing changeWeight() function:" << endl;
    cout << "Cat1 gains 2kg" << endl;
    cat1->changeWeight(2);
    cout << "Cat1 new weight: " << cat1->weight() << "kg" << endl;
    
    cout << "Dog1 loses 1kg" << endl;
    dog1->changeWeight(-1);
    cout << "Dog1 new weight: " << dog1->weight() << "kg" << endl;
    
    // Test meow() function (polymorphism)
    cout << "\n4. Testing meow() function (polymorphism):" << endl;
    cout << "Cat1 sound: ";
    cat1->meow();
    cout << "Dog1 sound: ";
    dog1->meow();
    cout << "Cat2 sound: ";
    cat2->meow();
    
    // Test growAll() static function
    cout << "\n5. Testing growAll() function:" << endl;
    cout << "Before all pets grow 1 year:" << endl;
    cout << "Cat1: " << cat1->age() << " years, Dog1: " << dog1->age() 
         << " years, Cat2: " << cat2->age() << " years" << endl;
    
    Pet::growAll();  // All pets age +1
    
    cout << "After all pets grow 1 year:" << endl;
    cout << "Cat1: " << cat1->age() << " years, Dog1: " << dog1->age() 
         << " years, Cat2: " << cat2->age() << " years" << endl;
    
    // Test polymorphism with base class pointers
    cout << "\n6. Testing polymorphism with base class pointers:" << endl;
    Pet* pets[] = {cat1, dog1, cat2};
    for(int i = 0; i < 3; i++) {
        cout << "Pet " << i+1 << " sound: ";
        pets[i]->meow();  // Calls appropriate meow() based on actual object type
    }
    
    // Test destructor (automatically removes from linked list)
    cout << "\n7. Testing destructor (memory cleanup):" << endl;
    cout << "Deleting Cat1..." << endl;
    delete cat1;  // Calls ~Cat() and ~Pet(), removes from linked list
    
    cout << "\nDeleting Dog1..." << endl;
    delete dog1;
    
    cout << "\nDeleting Cat2..." << endl;
    delete cat2;
    
    cout << "\nAll pets deleted. Test completed!" << endl;
    
    return 0;
}