#ifndef ast_nodeList_hpp
#define ast_nodeList_hpp

#include "ast_node.hpp"

class NodeList;

typedef const NodeList *NodeListPtr;

class NodeList
  : public Node
{
public:
  NodeList(std::vector<NodePtr> nodes)
  {
    branches = nodes;
  }

  NodeList()
    : NodeList(std::vector<NodePtr>{})
  {}

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "NodeList [" << std::endl;
    for(unsigned i = 0; i < branches.size(); i++){
      branches[i]->PrettyPrint(dst, indent+"  ");
    }
    dst << indent << "]" << std::endl;
  }
};
