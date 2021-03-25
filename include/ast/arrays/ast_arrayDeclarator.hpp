#ifndef ast_arrayDeclarator_hpp
#define ast_arrayDeclarator_hpp

#include "ast/ast_node.hpp"
#include "ast/literals/ast_integer.hpp"


class ArrayDeclarator
  : public Node
{
public:
  // Constructors
  ArrayDeclarator(NodePtr id, NodePtr size);
  ArrayDeclarator(NodePtr id);

  // Destructor
  virtual ~ArrayDeclarator();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  void generateMIPS(std::ostream &dst, Context &context, int destReg) const;

  // Codegen + helpers
  virtual std::string getId() const override;
  virtual bool isFunction() const override;
  virtual int getArraySize() const override;

};

#endif
