#include "ast/blocks/ast_ifElse.hpp"

// Constructors
IfElse::IfElse(NodePtr condition, NodePtr ifScope, NodePtr elseScope)
{
  branches.push_back(condition);
  branches.push_back(ifScope);
  branches.push_back(elseScope);
}

IfElse::IfElse(NodePtr condition, NodePtr ifScope)
  : IfElse(condition, ifScope, new Scope())
{}

// Destructor
IfElse::~IfElse()
{
  delete branches[0];
  delete branches[1];
  delete branches[2];
}

// Where things should be
NodePtr IfElse::getCondition() const
{
  return branches[0];
}

NodePtr IfElse::getIfScope() const
{
  return branches[1];
}

NodePtr IfElse::getElseScope() const
{
  return branches[2];
}

// Visualising
void IfElse::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Condition [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endCondition" << std::endl;
  dst << indent << "If Scope [" << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endIfScope" << std::endl;
  dst << indent << "Else Scope [" << std::endl;
  branches[2]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endElseScope" << std::endl;
}

void IfElse::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // If scope (needed for condition)
  context.enterScope();

  // Evaluate condition
  int conReg = context.regFile.allocate();
  if(conReg == -1){
    conReg = context.allocateFull();
  }
  branches[0]->generateMIPS(dst, context, conReg);

  // If branch
  std::string elseLabel = context.makeLabel("ELSE");
  std::string endLabel = context.makeLabel("ENDIF");
  dst << "beq $" << conReg << ",$0," << elseLabel << std::endl;
  dst << "nop" << std::endl;
  branches[1]->generateMIPS(dst, context, destReg);
  context.exitScope(dst); // Exit ifscope
  dst << "b " << endLabel << std::endl; // Go to end of ifElse
  dst << "nop" << std::endl;

  // Else branch
  dst << elseLabel << ":" << std::endl;
  branches[2]->generateMIPS(dst, context, destReg);

  // End of ifElse
  dst << endLabel << ":" << std::endl;
}
