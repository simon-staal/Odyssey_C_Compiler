#ifndef ast_sequence_hpp
#define ast_sequence_hpp

#include "ast/ast_node.hpp"

// Represents a generic sequence of c++ code, basically going to be used for scope, keeping sequence generic
// cause it might be reusable for other shit later (globals?)

class Sequence;
typedef Sequence *SeqPtr;

class Sequence
  : public Node
{
public:
  // Constructors
  Sequence();
  Sequence(NodePtr in);
  Sequence(std::vector<NodePtr> _branches);
  Sequence(std::vector<NodePtr> decList, std::vector<NodePtr> statList);

  // Destructor
  ~Sequence();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
};

#endif
