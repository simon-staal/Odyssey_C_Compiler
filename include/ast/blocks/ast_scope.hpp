#ifndef ast_scope_hpp
#define ast_scope_hpp

#include "ast/blocks/ast_sequence.hpp"

// The meat and potatoes of a function, basically a sequence

class Scope
  : public Sequence
{
public:
  // Does everything like Sequence (constructor/destructor wise)
  using Sequence::Sequence;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
