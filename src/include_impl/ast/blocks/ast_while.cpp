#include "ast/blocks/ast_while.hpp"

// Constructor
While::While(NodePtr condition, NodePtr scope)
{
  branches.push_back(condition);
  branches.push_back(scope);
}

// Destructor
While::~While()
{
  delete branches[0];
  delete branches[1];
}

// Visualising
void While::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "While condition [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endCondition" << std::endl;
  dst << indent << "Do scope [" << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endDoScope" << std::endl;
}

// Codegen
void While::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  context.enterScope();

  std::string startLabel = context.makeLabel("START");
  context.stack.back().startLabel = startLabel;
  dst << startLabel << ":" << std::endl;

  //Evaluate condition
  int conReg = context.allocate();
  branches[0]->generateMIPS(dst, context, conReg);

  // Scope of while loop
  std::string endLabel = context.makeLabel("END");
  context.stack.back().endLabel = endLabel;
  dst << "beq $" << conReg << ",$0," << endLabel << std::endl;
  dst << "nop" << std::endl;
  unsigned i = 0;
  NodePtr node = branches[1]->getNode(i);
  while(node != NULL){
    node->generateMIPS(dst, context, destReg); // Scope
    i++;
    node = branches[1]->getNode(i);
  }
  dst << "b " << startLabel << std::endl;
  dst << "nop" << std::endl;

  // End of while
  dst << endLabel << ":" << std::endl;
  context.regFile.freeReg(conReg);
  context.exitScope(dst); // Closing scope opened for condition
}
