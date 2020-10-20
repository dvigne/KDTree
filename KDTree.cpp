#include "kdtree.hpp"
#include <utility>
#include <algorithm>

/////////////////////////////////////////////////
/// @fn Node KDTree::search(point p)
/// @brief Returns the Node at a given point
/// @returns `Node` Node located at given point
/////////////////////////////////////////////////

Node* KDTree::search(point p) {
  return this->node->findNode(p, this->dimensions);
}

/////////////////////////////////////////////////
/// @fn void KDTree::insert(std::vector<Node>& na)
/// @brief Insert a Node into the K-D Tree
/// @param nodeArray std::vector of Node objects to insert
/////////////////////////////////////////////////

void KDTree::insert(std::vector<Node> nodeArray) {
  this->nodeArr.reserve(nodeArray.size());
  this->nodeArr = nodeArray;
  this->node = makeTree(0, nodeArray.size());
}

Node* KDTree::makeTree(size_t begin, size_t end, size_t index) {
  if(end <= begin) {
    return nullptr;
  }
  size_t n = begin + (end - begin) / 2;
  printf("Inserting Node (%d, %d)\n", nodeArr[n].getPosition()[0], nodeArr[n].getPosition()[1]);
  std::nth_element(&nodeArr[begin], &nodeArr[n], &nodeArr[0] + end, compareNodes(index));
  index = (++index) % this->dimensions;
  nodeArr[n].left = makeTree(begin, n, index);
  nodeArr[n].right = makeTree(n + 1, end, index);
  return &nodeArr[n];
}
