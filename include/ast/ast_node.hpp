#ifndef ast_node_hpp
#define ast_node_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class Node;

typedef const Node *NodePtr;

class Node
{
protected:
  std::vector<NodePtr> branches;

public:
  virtual ~Node();

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const = 0;
  friend std::ostream& operator<<(std::ostream &dst, const Node &Node);
  friend std::ostream& operator<<(std::ostream &dst, const NodePtr Node);
};

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

struct CompileContext
{
    std::map<std::string,int32_t> bindings;
};

/* RANDOM GARBAGE
NodePtr Parse(
    std::istream &src
);

void PrettyPrint(
    std::ostream &dst,
    NodePtr node,
    std::string indent=""
);

void Compile(
    NodePtr Node,
    CompileContext &context
);
*/

#endif
