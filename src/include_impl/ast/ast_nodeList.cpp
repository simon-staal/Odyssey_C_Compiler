#include "ast/ast_nodeList.hpp"

// Constructors
NodeList::NodeList(std::vector<NodePtr> nodes)
{
  branches = nodes;
}

NodeList::NodeList()
  : NodeList(std::vector<NodePtr>{})
{}

// Destructor (not sure)
virtual NodeList::~NodeList()
{
  for(unsigned i = 0; i < branches.size(); i++){
    delete branches[i];
  }
}

// Get stuff in list
NodePtr NodeList::getNode(unsigned index) const
{
  return branches[index];
}

// Visualising
virtual void NodeList::PrettyPrint(std::ostream &dst, std::string indent) const override
{
  dst << indent << "NodeList [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}
