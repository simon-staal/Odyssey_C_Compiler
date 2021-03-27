#include "ast/blocks/switch/ast_default.hpp"

// Constructor
Default::Default(NodePtr execute)
{
  branches.push_back(execute);
}

// Destructor
Default::~Default()
{
  delete branches[0];
}

// Visualising
void Default::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Default case [" << std::endl;
  dst << indent << "Execute:" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endCase" << std::endl;
}

void Default::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // Last case
  dst << context.stack.back().startLabel << ":" << std::endl;
  context.stack.back().startLabel = "DONE"; // In case no default
  branches[0]->generateMIPS(dst, context, destReg);
}
