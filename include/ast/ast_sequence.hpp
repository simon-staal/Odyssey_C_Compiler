#ifndef ast_sequence_hpp
#define ast_sequence_hpp

#include "ast_node.hpp"
#include "ast_expression.hpp"

class Sequence;
typedef Sequence *SeqPtr;

class Sequence
  : public Node
{
protected:
  std::vector<NodePtr> expressions;
public:
  Sequence(NodePtr in)
  {
    expressions.push_back(in);
  }

  ~Sequence()
  {
    for(int i = 0; i < expressions.size(); i++){
      delete expressions[i];
    }
  }

  std::vector<NodePtr> getSequence() { return expressions; }

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "Sequence [" << std::endl;
    for(int i = 0; i < expressions.size(); i++){
      PrettyPrint(expressions[i], indent+"  ");
    }
    sdt << indent << "]" << std::endl;
  }
}

#endif
