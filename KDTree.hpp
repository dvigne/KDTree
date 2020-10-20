#pragma once
#include <cstdint>
#include <memory>
#include <vector>
#include <cstdarg>
/////////////////////////////////////////////////
/// @struct DuplicateValueException
/// @brief Duplicate Value Exception
/// @details Throws `const char * "Duplicate Node Inserted"` if the requested
/// Node cannot be insertted into the KDTree
/////////////////////////////////////////////////

struct DuplicateValueException : public std::exception {
  /// @brief Returns `const char *` for pretty printing
  const char * what() const throw() {
    return "Supplied point out of tree bounds";
  }
};

/////////////////////////////////////////////////
/// @struct point
/// @brief Simple datastructure to hold x and y
/// coordinates
///
/// @fn point::point(float x, float y)
/// @brief point struct constructor
/// @param x X coordinate to assign
/// @param y Y coordinate to assign
///
/// @fn bool point::operator==(const point& otherPoint)
/// @brief Overloaded `==` operator for equivalency testing
/// @param otherPoint Second point to test
/// @returns `bool` True or false depending on equivalency
/////////////////////////////////////////////////

struct point {
  std::vector<int> coordinate; ///< point vector containing variables dimensional coordinates
  point(int num, ...) {
    va_list arglist;
    va_start(arglist, num);
    for(int i = 0; i < num; i++) {
      coordinate.push_back(va_arg(arglist, int));
    }
    va_end(arglist);
  }
  bool operator==(const point& otherPoint) { return coordinate == otherPoint.coordinate; };
  bool operator<(const point& otherPoint) { return coordinate < otherPoint.coordinate; };
  int operator[](int i) { return coordinate[i]; };
};
/////////////////////////////////////////////////
/// @class Node
/// @brief datastructure to be added to the kd-tree
/////////////////////////////////////////////////
class Node {
private:
  bool nodeVisited = false;
  point position;

public:
  Node* left;
  Node* right;
  /////////////////////////////////////////////////
  /// @fn Node::Node(point position, int occupiedConfidence, bool visited = false)
  /// @brief Node constructor
  /// @param position point position of node
  /// @param occupiedConfidence Percent confidence that a node is occupied by an obstacle.
  /// Helps with optimizing the search algorithm.
  /// ranges from `0-100` and `-1` if unknown
  /// @param visited Optional setting to mark this node as visited
  /////////////////////////////////////////////////

  Node(point position, int occupiedConfidence, bool visited = false) : position(position), occupiedConfidence(occupiedConfidence), nodeVisited(visited){};

  /////////////////////////////////////////////////
  /// @fn Node::Node(const Node& cNode)
  /// @brief Simple copy constructor for nodes
  /// @param cNode Node to copy
  /////////////////////////////////////////////////
  Node(const Node& cNode) : position(cNode.getPosition()), occupiedConfidence(cNode.getOccupiedConfidence()), nodeVisited(cNode.visited()){};
  point getPosition() const;;
  bool visited() const;
  bool operator<(Node& secondNode);
  bool operator==(Node& secondNode);
  void operator=(const Node& secondNode);
  Node* findNode(point p, uint8_t dimensions, uint32_t index = 0);
};

/////////////////////////////////////////////////
/// @class KDTree
/// @brief Actual KD-tree class with supporting methods
/////////////////////////////////////////////////
class KDTree {
private:
  uint8_t dimensions = 2;
  Node* node; // Root of tree
  std::vector<Node> nodeArr; // Preallocated Array of nodes for easy sorting

  Node* makeTree(size_t begin, size_t end, size_t index = 0);

  struct compareNodes {
      compareNodes(size_t index) : index(index) {}
      bool operator()(const Node& n1, const Node& n2) const {
          return n1.getPosition()[index] < n2.getPosition()[index];
      }
      size_t index;
    };

public:
  KDTree(uint8_t dimensions) : dimensions(dimensions){};
  KDTree(uint8_t dimensions, Node node) : dimensions(dimensions), node(&node){};
  void insert(std::vector<Node> nodeArray);
  Node* search(point p);
  std::vector<Node> getNodes(point p1, point p2);
  Node* getNode();
};
