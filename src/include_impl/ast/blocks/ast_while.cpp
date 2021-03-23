#include "ast/blocks/ast_while.hpp"

While::While(NodePtr condition, NodePtr scope)
{
  branches.push_back(condition);
  branches.push_back(scope);
}

While::~While()
{
  delete branches[0];
  delete branches[1];
}

NodePtr While::getCondition() const
{
  return branches[0];
}

NodePtr While::getScope() const
{
  return branches[1];
}

void While::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "While condition [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endCondition" << std::endl;
  dst << indent << "Do scope [" << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endScope" << std::endl;
}

void While::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // Required to evaluate condition
  context.enterScope();

  std::string startLabel = context.makeLabel("START");
  dst << startLabel << ":" << std::endl;

  //Evaluate condition
  int conReg = context.regFile.allocate();
  if(conReg == -1){
    conReg = context.allocateFull();
  }
  branches[0]->generateMIPS(dst, context, conReg);

  // Scope of while loop
  std::string endLabel = context.makeLabel("ENDWHILE");
  dst << "beq $" << conReg << ",$0," << endLabel << std::endl;
  dst << "nop" << std::endl;
  branches[1]->generateMIPS(dst, context, destReg);
  dst << "b " << startLabel << std::endl;
  dst << "nop" << std::endl;

  // End of while
  dst << endLabel << ":" << std::endl;
  context.regFile.freeReg(conReg);
  context.exitScope(dst); // Closing scope opened for condition
}
