#include "kdtree.hpp"
#include <cstdio>
#include <memory>

int main(int argc, char const *argv[]) {
  // point pt(2,  1, 5);
  // printf("Point (%d, %d)\n", pt[0], pt[1]);
  KDTree tree(2);
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      Node newNode(point(2, i,j), j - i);
      printf("Insertting Node (%d, %d)\n", newNode.getPosition()[0], newNode.getPosition()[1]);
      tree.insert(newNode);
    }
  }

  Node* foundNode = tree.search(point(2, 2 ,2));
  printf("Node (%d, %d) With Occu %d\n", foundNode->position[0], foundNode->position[1], foundNode->visited());
  return 0;
}
