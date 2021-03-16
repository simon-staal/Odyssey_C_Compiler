#include "ast/ast_node.hpp"

// Used in derived classes
Node::Node(std::vector<NodePtr> _branches)
  : branches(_branches)
{}

Node::Node()
  : Node(std::vector<NodePtr>{})
{}

Node::Node(std::vector<NodePtr> branches1, std::vector<NodePtr> branches2)
{
  branches = branches1;
  branches.insert(branches.end(), branches2.begin(), branches2.end());
}

Node::~Node()
{
  for(unsigned i = 0; i < branches.size(); i++){
    delete branches[i];
  }
}

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
