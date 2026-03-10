#include <iostream>
#include <memory>
#include <string>
#include <utility>

/*
  目标： 完成一个 Linked_list 链表 
  功能： 尾部构造（传入值） ， 尾部插入（传入链表） ， 定点插入（不可尾插） ， 定点后序列删除 ， 定点删除 ， 打印链表（以键值对形式）；
  规划： 结构体(已完成) => 类封装 => 自己的STL库（自定义链表）; 
  高级语法： C11 unique_ptr , C17 std::move;  
*/

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
  for(int i = 0 ; i < index ; ++i)
  {
    current = current->next.get();  // A -> B -> C -> D;(移动到B ，当index == 1)
  }

  if(current->next.get() == nullptr) {return;}

  auto b = std::make_unique<Linked_list> ();

  b->name = C.name;
  b->num = C.num;
  
  b->next = std::move(current->next);
  current->next = std::move(b);
}

void erase_list_all(Linked_list &Head , const int index) // 第 index 个链表之后删除
{
  Linked_list* current = &Head;
  for(int i = 0 ; i < index ; ++i)
  {
    current = current->next.get();
  }

  current->next.reset();
}

void erase_List_at(Linked_list &Head , const int index)
{
  Linked_list* current = &Head;
  for(int i = 0 ; i < index ; ++i)
  {
    current = current->next.get();
  }// A -> B -> C -> D => A -> B -> D; B->next = std::move(C->next); C被自动释放；当 index = 1 时 ， B 即为current；

  current->next = std::move(current->next->next);
}

void Print_list(Linked_list &Head){// 逐个打印
  Linked_list* current = &Head;

  while(current != nullptr)
  {
    std::cout << '[' <<current->name << ',' << current->num << ']' << '\n';
    current = current->next.get();
  }
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

  erase_list_all(A, 2);

  std::cout << '\n';
  Print_list(A);
  return 0;
}