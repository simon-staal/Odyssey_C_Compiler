#ifndef ast_arrayDeclarator_hpp
#define ast_arrayDeclarator_hpp

#include "ast/ast_node.hpp"
#include "ast/literals/ast_integer.hpp" // For empty size constructor

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
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen helpers
  std::string getId() const override;
  bool isFunction() const override;
  bool isInit() const override;
  int getArraySize() const override;
};

#endif
