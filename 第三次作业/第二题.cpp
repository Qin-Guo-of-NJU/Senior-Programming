/*
###写在前面###
1、Pet类、Cat、Dog派生类定义复制自上一题
*/
//#####从这里开始，都复制的上一题代码#####
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
                curr=curr->next;}
        };
};
Pet::Pet(int age,int weight) :AGE(age),WEIGHT(weight){
    PetNode* newNode= new PetNode(this);
    newNode->next=head;
    head=newNode;
}
int Pet::weight(){return WEIGHT;}
int Pet::age(){return AGE;}
void Pet::changeWeight(int w){
    WEIGHT+=w;
};
PetNode* Pet::head=nullptr;
class Cat:public Pet{
public:
    Cat(int age,int weight):Pet(age,weight){}
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
//#####复制的内容到这里结束#####
#include<string>
#include<vector>
#include<algorithm>
class Owner{
    private:
    string name;
    vector<Pet*>Pets;
    public:
    Owner(const string& ownername):name(ownername){};//引用类型，传递实参本身，而不是他的拷贝，提高效率
    //~Owner();没有要求做析构
    void addPet(Pet* pet);//add a pet
    void removePet(Pet* pet);//remove a pet
    void allMeow()const;//all pets meow
    void feedAll(int foodweight);//all pets eat,weight+foodweight!
};
void Owner::addPet(Pet* pet){
    Pets.push_back(pet);
}
void Owner::removePet(Pet* pet) {
    /*
    // 删除所有等于 pet 的元素，可以删除重复的，虽然作业中没有要求
    Pets.erase(remove(Pets.begin(), Pets.end(), pet), Pets.end());//remove是algorithm STL算法库中的函数
    不过我还是写得符合实际情况一点吧，允许添加相同宠物的情况下，应该是删除一个
    */
   //不能这样写：Pets.erase(pet);因为erase需要迭代器
   //这样:
   auto it =find(Pets.begin(),Pets.end(),pet);//auto :编译器自动判断变量类型，不用写vector
   //find函数：如果在Pets中找到与pet相同的元素，返回一个指向该元素的迭代器，否则返回指向Pets.end()的迭代器
   if (it!=Pets.end()){//不能if (it)，迭代器不能当作布尔值使用
        Pets.erase(it);//会删除it指向的元素，并自动调整容器，返回指向被删除元素的下一元素的迭代器
        cout<<"remove a pet"<<endl;

    }
    else{
        cout<<"this pet cannot be found!"<<endl;
    }

}
void Owner::allMeow()const{
    for (int i=0;i<Pets.size();i++){
        Pets[i]->meow();//复习：->成员访问运算符，通过指针访问对象的成员
    }
}
void Owner::feedAll(int foodweight){
    for (int i=0;i<Pets.size();i++){
        Pets[i]->changeWeight(foodweight);
    }
}
//以下测试函数由DeepSeek生成
int main() {
    cout << "========================================" << endl;
    cout << "   Pet Ownership System Test" << endl;
    cout << "========================================" << endl;
    
    // 1. Create pets
    cout << "\n[1] Creating pets:" << endl;
    Cat* fluffy = new Cat(2, 5);
    Dog* max = new Dog(3, 10);
    Cat* kitty = new Cat(1, 4);
    Dog* buddy = new Dog(4, 12);
    
    cout << "  Created:" << endl;
    cout << "    - Fluffy (Cat, 2 years, 5kg)" << endl;
    cout << "    - Max (Dog, 3 years, 10kg)" << endl;
    cout << "    - Kitty (Cat, 1 year, 4kg)" << endl;
    cout << "    - Buddy (Dog, 4 years, 12kg)" << endl;
    
    // 2. Create owners
    cout << "\n[2] Creating owners:" << endl;
    Owner alice("Alice");
    Owner bob("Bob");
    cout << "  Created: Alice and Bob" << endl;
    
    // 3. Add pets to owners
    cout << "\n[3] Adding pets to owners:" << endl;
    cout << "  Alice:" << endl;
    alice.addPet(fluffy);
    alice.addPet(max);
    cout << "  Bob:" << endl;
    bob.addPet(kitty);
    bob.addPet(fluffy);
    bob.addPet(buddy);
    
    // 4. Test allMeow()
    cout << "\n[4] Testing allMeow():" << endl;
    cout << "Alice's pets:" << endl;
    alice.allMeow();
    cout << "\nBob's pets:" << endl;
    bob.allMeow();
    
    // 5. Test feedAll()
    cout << "\n[5] Testing feedAll():" << endl;
    cout << "Alice feeds 2kg:" << endl;
    alice.feedAll(2);
    cout << "\nBob feeds 1kg:" << endl;
    bob.feedAll(1);
    
    // 6. Display weights after feeding
    cout << "\n[6] Weights after feeding:" << endl;
    cout << "  Fluffy: " << fluffy->weight() << "kg" << endl;
    cout << "  Max: " << max->weight() << "kg" << endl;
    cout << "  Kitty: " << kitty->weight() << "kg" << endl;
    cout << "  Buddy: " << buddy->weight() << "kg" << endl;
    
    // 7. Test removePet()
    cout << "\n[7] Testing removePet():" << endl;
    cout << "  Removing Max from Alice:" << endl;
    alice.removePet(max);
    cout << "\n  Removing Fluffy from Bob:" << endl;
    bob.removePet(fluffy);
    cout << "\n  Trying to remove non-existent pet:" << endl;
    alice.removePet(buddy);
    
    // 8. Test allMeow() after removal
    cout << "\n[8] Testing allMeow() after removal:" << endl;
    cout << "Alice's pets:" << endl;
    alice.allMeow();
    cout << "\nBob's pets:" << endl;
    bob.allMeow();
    
    // 9. Test Pet::growAll()
    cout << "\n[9] Testing Pet::growAll():" << endl;
    cout << "  Ages before:" << endl;
    cout << "    Fluffy: " << fluffy->age() << " years" << endl;
    cout << "    Max: " << max->age() << " years" << endl;
    cout << "    Kitty: " << kitty->age() << " years" << endl;
    cout << "    Buddy: " << buddy->age() << " years" << endl;
    
    Pet::growAll();
    
    cout << "  Ages after (+1 year):" << endl;
    cout << "    Fluffy: " << fluffy->age() << " years" << endl;
    cout << "    Max: " << max->age() << " years" << endl;
    cout << "    Kitty: " << kitty->age() << " years" << endl;
    cout << "    Buddy: " << buddy->age() << " years" << endl;
    
    // 10. Add pets back to test edge cases
    cout << "\n[10] Testing addPet() with existing pet:" << endl;
    cout << "  Adding Max back to Alice:" << endl;
    alice.addPet(max);
    cout << "  Alice's pets now:" << endl;
    alice.allMeow();
    
    // 11. Test feedAll with empty owner
    cout << "\n[11] Testing edge case - Owner with no pets:" << endl;
    Owner charlie("Charlie");
    cout << "Charlie has no pets:" << endl;
    charlie.allMeow();
    charlie.feedAll(5);
    
    // 12. Clean up
    cout << "\n[12] Cleaning up pets:" << endl;
    delete fluffy;
    delete max;
    delete kitty;
    delete buddy;
    cout << "  All pets deleted successfully!" << endl;
    
    cout << "\n========================================" << endl;
    cout << "   Test completed!" << endl;
    cout << "========================================" << endl;
    
    return 0;
}