#ifndef ast_scopeGlobal_hpp
#define ast_scopeGlobal_hpp

#include "ast/ast_sequence.hpp"

class GlobalScope
  : public Sequence
{
public:
  using Sequence::Sequence;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
