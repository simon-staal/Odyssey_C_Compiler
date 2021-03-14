#ifndef ast_scope_hpp
#define ast_scope_hpp

#include "ast/ast_node.hpp"
#include "ast/ast_sequence.hpp"

// The meat and potatoes of a function, basically a sequence

class Scope;
typedef const Scope *ScopePtr;

class Scope
  : public Sequence
{
public:
  // I think this works? should do everything like Sequence
  using Sequence::Sequence;

  // Just in case we need it
  std::vector<NodePtr> getScope();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
};

#endif
