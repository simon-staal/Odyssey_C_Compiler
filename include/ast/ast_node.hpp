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
public:
  virtual ~Node();

  friend std::ostream& operator<<(std::ostream &dst, const Node &Node);
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const = 0;
};

std::ostream &operator<<(std::ostream &dst, const Node &Node)
{
  Node.PrettyPrint(dst, "");
  return dst;
}


struct CompileContext
{
    std::map<std::string,int32_t> bindings;
};

/*
NodePtr Parse(
    std::istream &src
);
*/
void PrettyPrint(
    std::ostream &dst,
    NodePtr node,
    std::string indent=""
);


/*
void Compile(
    NodePtr Node,
    CompileContext &context
);
*/

#endif
