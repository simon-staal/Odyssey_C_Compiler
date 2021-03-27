#include "ast/blocks/switch/ast_case.hpp"

// Constructor
Case::Case(NodePtr condition, NodePtr execute)
{
  branches.push_back(condition);
  branches.push_back(execute);
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
  // Start of case
  dst << context.stack.back().startLabel << ":" << std::endl;

  // Evaluate condition
  int conReg = context.allocate();
  branches[0]->generateMIPS(dst, context, conReg);
  std::string nextCase = context.makeLabel("CASE");
  context.stack.back().startLabel = nextCase; // Updates next case
  dst << "bne $" << conReg << ",$17," << nextCase << std::endl; // Skips to next case if condition doesn't match
  dst << "nop" << std::endl;
  context.regFile.freeReg(conReg);

  // Execute case
  branches[1]->generateMIPS(dst, context, destReg);
}
