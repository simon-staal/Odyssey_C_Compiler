#include "ast/ast_sequence.hpp"

// Constructors
Sequence::Sequence()
{
  // Empty, do nothing
}

Sequence::Sequence(NodePtr in)
{
  branches.push_back(in);
}

Sequence::Sequence(std::vector<NodePtr> _branches)
  : Node(_branches)
{}

// Destructor
Sequence::~Sequence()
{
  for(unsigned i = 0; i < branches.size(); i++){
    delete branches[i];
  }
}

// Visualising
virtual void Sequence::PrettyPrint(std::ostream &dst, std::string indent) const override
{
  dst << indent << "Sequence [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}
