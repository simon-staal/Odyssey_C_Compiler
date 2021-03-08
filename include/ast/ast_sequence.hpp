#ifndef ast_sequence_hpp
#define ast_sequence_hpp

#include "ast_node.hpp"

// Represents a generic sequence of c++ code, basically going to be used for scope, keeping sequence generic
// cause it might be reusable for other shit later (globals?)

class Sequence;
typedef Sequence *SeqPtr;

class Sequence
  : public Node
{
public:
  // Constructors
  Sequence()
  {
    // Empty, do nothing
  }

  Sequence(NodePtr in)
  {
    branches.push_back(in);
  }

  Sequence(std::vector<NodePtr> _branches)
    : branches(_branches)
  {}

  // Destructor
  ~Sequence()
  {
    for(unsigned i = 0; i < expressions.size(); i++){
      delete expressions[i];
    }
  }

  // Visualising
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
