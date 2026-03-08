#include <iostream>
#include <memory>
#include <string>

struct Linked_list{
  std::string name;
  long num;
  std::unique_ptr<Linked_list> next;
};

void emplace_list(Linked_list &Head , const std::string &name ,const int num)
{
  Linked_list* current = &Head;
  while(current->next != nullptr)
  {
    current = current->next.get();
  }
  
  current->next = std::make_unique<Linked_list> ();//构造初始化 current->next = std::make_unique<Linked_list> (Linked_list{name , num});
  current->next->name = name;
  current->next->num = num;
}

void erase_list(Linked_list &Head , const int index)
{
  Linked_list* current = &Head;
  for(int i = 0 ; i < index ; ++i)
  {

  }
}

void Print_list(Linked_list &Head){
  Linked_list* current = &Head;

  while(current != nullptr)
  {
    std::cout << current->name << current->num << '\n';
    current = current->next.get();
  }
}

int main()
{
  Linked_list A{"hahaha" , 1};
  emplace_list(A , "asdw" , 2);

  Print_list(A);

  return 0;
}