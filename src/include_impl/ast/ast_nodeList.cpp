#include "ast/ast_nodeList.hpp"

// Constructors
NodeList::NodeList(std::vector<NodePtr> nodes)
{
  branches = nodes;
}

NodeList::NodeList()
  : NodeList(std::vector<NodePtr>{})
{}

// Destructor
NodeList::~NodeList()
{
  for(unsigned i = 0; i < branches.size(); i++){
    delete branches[i];
  }
}

// Visualising
void NodeList::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "NodeList [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}

// Get stuff in list - codegen helper
NodePtr NodeList::getNode(unsigned index) const
{
  if(index < branches.size()){
    return branches[index];
  }
  else{
    return NULL;
  }
}
