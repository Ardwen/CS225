#include "List.h"
#include <iostream>
#include <string>

int main() {
  List<int> n;
  n.insertBack(10);
  n.insertBack(22);
  n.insertBack(33);
  n.insertBack(4);
  n.insertBack(52);
  n.insertBack(6);
  n.insertBack(7);
  n.insertBack(8);

  n.sort();
  n.print();


  return 0;
}
