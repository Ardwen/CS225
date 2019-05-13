/* Your code here! */
#include "dsets.h"
#include <vector>
using namespace std;
void DisjointSets::addelements(int num){
  for (int i = 0; i < num; i++) {
    elements.push_back(-1);
  }
}
int DisjointSets::find (int elem){
 if (elements[elem] < 0) {
   return elem;
 } else {
   return find(elements[elem]);
 }
}

void DisjointSets::setunion	(int a,int b) {
  int root1 = find(a);
  int root2 = find(b);
  if (root1 == root2) {
    return;
  }
  int newSize = elements[root1] + elements[root2];
  if (elements[root1] <= elements[root2]) {
    elements[root2] = root1;
    elements[root1] = newSize;
  } else {
    elements[root1] = root2;
    elements[root2] = newSize;
  }
  return;
}

int DisjointSets::size (int elem) {
  int root = find(elem);
  return -1 * elements[root];
}
