#ifndef ast_scope_hpp
#define ast_scope_hpp

#include "ast_node.hpp"

class Scope
  : public Node
{
protected:
  std::vector<NodePtr> expressions;

public:
  Scope(NodePtr in)
  {
    expressions.push_back(in);
  }
  Scope(ExprPtr expression)
    : expression(expressions->branches);
  {}

  std::vector<NodePtr> getScope() { return expressions; }

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
      dst << indent << "Sequence [" << std::endl
      for(int i = 0; i < seq.size(); i++){
        PrettyPrint(seq[i], indent+"  ")
      }
      dst << indent << "]" << std::endl;
  }
};

#endif
