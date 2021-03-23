#ifndef ast_nodeList_hpp
#define ast_nodeList_hpp

#include "ast_node.hpp"

class NodeList;
typedef NodeList *NodeListPtr;

class NodeList
  : public Node
{
public:
  // Constructors
  NodeList(std::vector<NodePtr> nodes);
  NodeList();

  // Destructor
  virtual ~NodeList();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Get stuff in list (codegen)
  virtual NodePtr getNode(unsigned index) const override;
};

#endif
