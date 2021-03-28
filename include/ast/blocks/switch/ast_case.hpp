#ifndef ast_case_hpp
#define ast_case_hpp

#include "ast/ast_node.hpp"

class Case
  : public Node
{
public:
  // Constructor
  Case(NodePtr condition, NodePtr execute);

  // Destructor
  virtual ~Case();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
