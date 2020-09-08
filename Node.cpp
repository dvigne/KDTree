#include "kdtree.hpp"
#include <cmath>

/////////////////////////////////////////////////
/// @fn point Node::getPosition()
/// @brief Returns the Position of the Node object
/// @returns `point` The Position of the Node Object
/////////////////////////////////////////////////

point Node::getPosition() const {
  return position;
}

/////////////////////////////////////////////////
/// @fn int Node::getOccupiedConfidence()
/// @brief Returns the percent occupied confidency score that an
/// obstacle exists at this node.
/// @returns `int` percent occupancy score. Ranges from `0-100`
/// or `-1` if unknown
/////////////////////////////////////////////////

int Node::getOccupiedConfidence() const{
  return occupiedConfidence;
}

/////////////////////////////////////////////////
/// @fn bool Node::visited()
/// @brief Check if we have visited this node before. This helps with
/// optimizing the search algorithm for completeness.
/// @returns `bool` true or false regarding whether we have
/// visited this node or not.
/////////////////////////////////////////////////

bool Node::visited() const {
  return nodeVisited;
}

/////////////////////////////////////////////////
/// @fn bool Node::operator<(Node& secondNode)
/// @brief Check if this Node is less than another Node
/// @returns `bool` true if less than
/////////////////////////////////////////////////

bool Node::operator<(Node& secondNode) {
  return position < secondNode.getPosition();
}

/////////////////////////////////////////////////
/// @fn bool Node::operator==(Node& secondNode)
/// @brief Check equality between two nodes
/// @returns `bool` true if equal
/////////////////////////////////////////////////

bool Node::operator==(Node& secondNode) {
  return position == secondNode.getPosition();
}

/////////////////////////////////////////////////
/// @fn Node::operator=(const Node& secondNode)
/// @brief Copies the conents of the second node
/// into the curent node
/////////////////////////////////////////////////
void Node::operator=(const Node& secondNode) {
  position = secondNode.getPosition();
  occupiedConfidence = secondNode.getOccupiedConfidence();
  nodeVisited = secondNode.visited();
}

/////////////////////////////////////////////////
/// @fn Node::findNode(point p, uint8_t dimensions, uint32_t index)
/// @brief Searches through the kd-tree for the specified point
/// @param p Point to search for
/// @param dimensions Dimensionality of the tree
/// @param index Curent index for tail recursive searching
/// @returns `Node *` Pointer to found node
/////////////////////////////////////////////////
Node* Node::findNode(point p, uint8_t dimensions, uint32_t index) {
  if(this->getPosition() == p) {
    printf("Found Node (%d, %d) occu %d\n", this->getPosition()[0], this->getPosition()[1], this->getOccupiedConfidence());
    return this;
  }

  else if(this->getPosition()[index % dimensions] > p[index % dimensions]) {
    printf("Falling Left\n");
    return this->left->findNode(p, dimensions, ++index);
  }

  else {
    printf("Falling Right\n");
    return this->right->findNode(p, dimensions, ++index);
  }
}
