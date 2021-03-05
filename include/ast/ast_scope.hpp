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
    seq.push_back(in);
  }

  Scope(SeqPtr _seq)
    : seq(_seq->expressions)
  {}

  ~Scope()
  {
    for(unsigned i = 0; i < seq.size(); i++){
      delete seq[i];
    }
  }

  std::vector<NodePtr> getScope() { return seq; }

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
      dst << indent << "Sequence [" << std::endl;
      for(unsigned i = 0; i < seq.size(); i++){
        seq[i]->PrettyPrint(dst, indent+"  ");
      }
      dst << indent << "]" << std::endl;
  }
};

#endif
