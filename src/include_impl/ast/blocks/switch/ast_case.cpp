#include "ast/blocks/switch/ast_case.hpp"

// Constructor
Case::Case(NodePtr condition, NodePtr execute)
{
  branches.push_back(condition);
  branches.push_back(execute)
}

// Destructor
Case::~Case()
{
  delete branches[0];
  delete branches[1];
}

void Case::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Case [" << std::endl;
  dst << indent << "MatchExpression:" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "Execute:" << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endCase" << std::endl;
}

void Case::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // Think about
}
