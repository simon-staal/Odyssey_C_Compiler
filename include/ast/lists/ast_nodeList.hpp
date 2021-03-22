#ifndef ast_nodeList_hpp
#define ast_nodeList_hpp

#include "ast/ast_node.hpp"

class NodeList;
typedef NodeList *NodeListPtr;

class NodeList
  : public Node
{
public:
  // Constructors
  NodeList(std::vector<NodePtr> nodes);
  NodeList();

  // Destructor (not sure)
  virtual ~NodeList();

  // Get stuff in list
  virtual NodePtr getNode(unsigned index) const override;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
};

#endif
