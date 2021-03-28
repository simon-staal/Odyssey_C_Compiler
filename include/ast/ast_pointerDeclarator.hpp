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
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Get stuff in list (codegen)
  bool isInit() const override;
  bool isFunction() const override;
  std::string getId() const override;
  bool isPtr() const override;

};

#endif
