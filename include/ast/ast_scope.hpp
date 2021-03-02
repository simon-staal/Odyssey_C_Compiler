#ifndef ast_scope_hpp
#define ast_scope_hpp

#include "ast_node.hpp"
#include "ast_sequence.hpp"

class Scope
  : public Node
{
protected:
  std::vector<NodePtr> seq;

public:
  Scope(NodePtr in)
  {
    expressions.push_back(in);
  }
  Scope(SeqPtr _seq)
    : seq(_seq->expressions);
  {}

  ~Scope()
  {
    for(int i = 0; i < expressions.size(); i++){
      delete expressions[i];
    }
  }

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
