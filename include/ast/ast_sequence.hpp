#ifndef ast_sequence_hpp
#define ast_sequence_hpp

#include "ast_node.hpp"
#include "ast_expression.hpp"

class Sequence;
typedef Sequence *SeqPtr;

class Sequence
  : public Node
{
public:
  std::vector<NodePtr> expressions;

  Sequence(NodePtr in)
  {
    expressions.push_back(in);
  }

  ~Sequence()
  {
    for(unsigned i = 0; i < expressions.size(); i++){
      delete expressions[i];
    }
  }

  std::vector<NodePtr> getSequence() { return expressions; }

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "Sequence [" << std::endl;
    for(unsigned i = 0; i < expressions.size(); i++){
      expressions[i]->PrettyPrint(dst, indent+"  ");
    }
    dst << indent << "]" << std::endl;
  }
};

#endif
