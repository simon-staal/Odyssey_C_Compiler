#ifndef ast_arrayInit_hpp
#define ast_arrayInit_hpp

#include "ast/ast_node.hpp"

class ArrayInit
  : public Node
{
public:
  // Constructors
  ArrayInit(std::vector<NodePtr> elements);

  // Destructor
  ~ArrayInit();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  int getValue(int i) const override;
  double getFloat(int i) const override;
  void generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const override;

};


#endif
