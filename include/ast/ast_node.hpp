#ifndef ast_node_hpp
#define ast_node_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

// Base building block for everything, the Argos

class Node;
typedef const Node *NodePtr;

class Node
{
protected:
  std::vector<NodePtr> branches;

public:
  // Used in derived classes
  Node(std::vector<NodePtr> _branches)
    : branches(_branches)
  {}
  
  Node()
    : Node(std::vector<NodePtr>{})
  {}

  virtual ~Node()
  {
    for(unsigned i = 0; i < branches.size(); i++){
      delete branches[i];
    }
  }

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const = 0;

  // We friends with ostream now :D
  friend std::ostream& operator<<(std::ostream &dst, const Node &Node);
  friend std::ostream& operator<<(std::ostream &dst, const NodePtr Node);
};

// Overloading << for nodes, just to make things look nice
std::ostream &operator<<(std::ostream &dst, const Node &Node)
{
  Node.PrettyPrint(dst, "");
  return dst;
}

std::ostream &operator<<(std::ostream &dst, const NodePtr Node)
{
  Node->PrettyPrint(dst, "");
  return dst;
}

// idk wtf this is lmao
/*
struct CompileContext
{
    std::map<std::string,int32_t> bindings;
};
*/

#endif
