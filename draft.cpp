#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Linked_list{
  std::string name;
  long num;
  std::unique_ptr<Linked_list> next;
};

void emplace_list(Linked_list &Head , const std::string &name ,const int num) // 在链表后加上新的链表（构造）；
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

void erase_list(Linked_list &Head , const int index) // 第 index 个链表之后删除
{
  Linked_list* current = &Head;
  for(int i = 0 ; i < index ; ++i)
  {
    current = current->next.get();
  }

  current->next.reset();
}

void Print_list(Linked_list &Head){// 逐个打印
  Linked_list* current = &Head;

  while(current != nullptr)
  {
    std::cout << '[' <<current->name << ',' << current->num << ']' << '\n';
    current = current->next.get();
  }
}

void Push_back(Linked_list &Head , Linked_list &B)//把链表 放到 最后 （赋值）
{
  Linked_list* current = &Head;

  while(current->next != nullptr)
  {
    current = current->next.get();
  }

  auto middle = std::make_unique<Linked_list> ();
  middle->name = B.name;
  middle->num = B.num;
  middle->next = nullptr;

  current->next = std::move(middle); //Linked_list* b.......... '\n' current->next.reset(b); 堆上 unique 指针 不能管理 栈上的 指针 ， 用make_unique
}

void Insert_list(Linked_list &Head , Linked_list &C , const int index)
{
  Linked_list* current = &Head;

  for (int i = 0 ; i < index ; ++i)
  {
    current = current->next.get();
  } // A -> B -> B -> D ;=> A -> B -> C -> D; 

  auto temp = std::make_unique<Linked_list> (); //temp ~= B;=> B -> temp;?????
  temp->name = current->name;
  temp->num = current->num;
  temp->next = std::move(current->next);

}

int main()
{
  Linked_list A{"105" , 1};
  Linked_list B{"AKA" , 123};
  emplace_list(A , "106" , 2);
  emplace_list(A , "107" , 3);
  emplace_list(A , "108" , 4);
  Push_back(A, B);
  Print_list(A);

  erase_list(A, 2);

  std::cout << '\n';
  Print_list(A);
  return 0;
}