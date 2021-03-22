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

int Node::getSize() const
{
  std::cerr << "Tried to getSize of something not implemented" << std::endl;
  return 0;
}

std::string Node::getId() const
{
  std::cerr << "Tried to getId of something not implemented" << std::endl;
  return "";
}

bool Node::isFunction() const
{
  std::cerr << "Tried to check isFunction of something not implemented" << std::endl;
  return 1;
}

bool Node::isInit() const
{
  std::cerr << "Tried to check isInit of something not implemented" << std::endl;
  return 1;
}

NodePtr Node::getNode(unsigned index) const
{
  std::cerr << "Tried to getNode of something not implemented" << std::endl;
  return NULL;
}

void Node::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::cerr << "YOU IN THE WRONG HOUSE FOOL" << std::endl;
  exit(1);
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
