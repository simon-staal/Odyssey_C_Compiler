#ifndef ast_scopeGlobal_hpp
#define ast_scopeGlobal_hpp

#include "ast/blocks/ast_sequence.hpp"

// Holds everything declared in global scope

class GlobalScope
  : public Sequence
{
public:
  using Sequence::Sequence;

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
