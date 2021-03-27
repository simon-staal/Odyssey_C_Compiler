#ifndef ast_sizeof_hpp
#define ast_sizeof_hpp

#include "ast/ast_node.hpp"

class SizeOf
  : public Node
{
public:
  // Constructor
  SizeOf(NodePtr type);

  // Destructor
  ~SizeOf();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
