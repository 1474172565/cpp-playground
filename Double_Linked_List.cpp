#include <string>
#include <utility>
#include <iostream>

class Double_Linked_List{
    std::string name;
    std::string words;

    Double_Linked_List* Prev;
    Double_Linked_List* Next;
public:
    Double_Linked_List(const std::string& Name , const std::string& Words , Double_Linked_List* p1 , Double_Linked_List* p2) : name(Name) , words(Words) , Prev(std::move(p1)) , Next(std::move(p2)){};
    Double_Linked_List(){name = ' ' ; words = '0';}
    ~Double_Linked_List(){std::cout << "dadadafa";}
};

class A : Double_Linked_List{
public:
  ~A(){std::cout << " you";}  
};

int main(){
    Double_Linked_List A;
    class A B;

    return 0;
}