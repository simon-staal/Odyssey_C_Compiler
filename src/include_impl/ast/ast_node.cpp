#include "ast/ast_node.hpp"

// Constructors
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

// Destructor
Node::~Node()
{
  for(unsigned i = 0; i < branches.size(); i++){
    delete branches[i];
  }
}

// Visualising
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

// Codegen
void Node::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::cerr << "YOU IN THE WRONG HOUSE FOOL" << std::endl;
  exit(1);
}

// Codegen helpers
int Node::getSize() const
{
  std::cerr << "Tried to getSize of something not implemented" << std::endl;
  return 0;
}

int Node::getSize(Context &context) const
{
  std::cerr << "Tried to getSize of expression of something not implemented" << std::endl;
  return 0;
}

std::string Node::getId() const
{
  std::cerr << "Tried to getId of something not implemented" << std::endl;
  exit(1);
}

bool Node::isFunction() const
{
  return false;
}

bool Node::isInit() const
{
  std::cerr << "Tried to check isInit of something not implemented" << std::endl;
  exit(1);
}

NodePtr Node::getNode(unsigned index) const
{
  if(index < branches.size()){
    return branches[index];
  }
  return NULL;
}

int Node::getArraySize() const
{
  // DEBUGGING
  // std::cerr << "Tried to getArraySize of something..." << std::endl;
  return 0;
}

int Node::getValue() const
{
  std::cerr << "Tried to getValue of something with no value" << std::endl;
  exit(1);
}

int Node::getValue(int i) const
{
  std::cerr << "Tried to getValue (array) of something not implemented" << std::endl;
  exit(1);
}
