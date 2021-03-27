#ifndef ast_pointerDeclarator_hpp
#define ast_pointerDeclarator_hpp

#include "ast_node.hpp"


class PointerDeclarator
  : public Node
{
public:

  PointerDeclarator(NodePtr id);

  // Destructor
  virtual ~PointerDeclarator();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;

  // Get stuff in list (codegen)
  virtual bool isInit() const override;
  virtual bool isFunction() const override;
  virtual std::string getId() const override;
  bool isPtr() const override;
  
};

#endif
