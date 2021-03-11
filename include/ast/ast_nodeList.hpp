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

  // Destructor (not sure)
  virtual ~NodeList();

  // Get stuff in list
  NodePtr getNode(unsigned index) const;
  
  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
};

#endif
