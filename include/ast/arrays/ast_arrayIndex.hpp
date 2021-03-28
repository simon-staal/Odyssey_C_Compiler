#ifndef ast_arrayIndex_hpp
#define ast_arrayIndex_hpp

#include "ast/ast_node.hpp"
#include "ast/ast_nodeList.hpp"


class ArrayIndex
  : public Node
{
public:
  // Constructors
  ArrayIndex(NodePtr id, NodePtr index);

  // Destructor
  virtual ~ArrayIndex();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const;
  std::string getId() const override;
  bool isFunction() const override;
};

#endif
