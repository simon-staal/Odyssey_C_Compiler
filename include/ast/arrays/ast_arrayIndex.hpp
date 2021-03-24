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
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  void generateMIPS(std::ostream &dst, Context &context, int destReg) const;

  // Codegen + helpers
  virtual std::string getId() const override;
  virtual bool isFunction() const override;
};

#endif