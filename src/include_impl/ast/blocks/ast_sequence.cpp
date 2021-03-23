#include "ast/blocks/ast_sequence.hpp"

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

Sequence::Sequence(std::vector<NodePtr> decList, std::vector<NodePtr> statList)
  : Node(decList, statList)
{}

// Destructor
Sequence::~Sequence()
{
  for(unsigned i = 0; i < branches.size(); i++){
    delete branches[i];
  }
}

// Visualising
void Sequence::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Sequence [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}

NodePtr Sequence::getNode(unsigned index) const
{
  if(index < branches.size()){
    return branches[index];
  }
  return NULL;
}
