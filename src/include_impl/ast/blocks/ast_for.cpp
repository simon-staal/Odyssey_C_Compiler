#include "ast/blocks/ast_for.hpp"

// Constructor
For::For(NodePtr initializer, NodePtr condition, NodePtr increment, NodePtr scope)
{
  branches.push_back(initializer);
  branches.push_back(condition);
  branches.push_back(increment);
  branches.push_back(scope);
}

// Destructor
For::~For()
{
  for(unsigned i = 0; i < 4; i++){ // I used the for loop to destroy the for loop
    delete branches[i];
  }
}

// Visualising
void For::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "For initilisation [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent+"  " << "Condition: " << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent+"  " << "Increment: " << std::endl;
  branches[2]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endInitialisation" << std::endl;
  dst << indent << "Do scope [" << std::endl;
  branches[3]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]endDoScope" << std::endl;
}

// Codegen
void For::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // Required for initializer
  context.enterScope();

  // Initialise iterator
  int itReg = context.allocate();
  branches[0]->generateMIPS(dst, context, itReg);

  // Start of loop
  std::string startLabel = context.makeLabel("START");
  dst << startLabel << ":" << std::endl;
  // To handle continue statements
  std::string incLabel = context.makeLabel("INC");
  context.stack.back().startLabel = incLabel;
  // Evaluate condition
  branches[1]->generateMIPS(dst, context, itReg);

  // Loopy bit
  std::string endLabel = context.makeLabel("END");
  context.stack.back().endLabel = endLabel;
  dst << "beq $" << itReg << ",$0," << endLabel << std::endl;
  dst << "nop" << std::endl;
  unsigned i = 0;
  NodePtr node = branches[3]->getNode(i);
  while(node != NULL){
    node->generateMIPS(dst, context, destReg); // Scope
    i++;
    node = branches[3]->getNode(i);
  }
  dst << incLabel << ":" << std::endl;
  branches[2]->generateMIPS(dst, context, itReg); // Increment
  dst << "b " << startLabel << std::endl;
  dst << "nop" << std::endl;

  // End of loop
  dst << endLabel << ":" << std::endl;
  context.regFile.freeReg(itReg);
  context.exitScope(dst);
}
