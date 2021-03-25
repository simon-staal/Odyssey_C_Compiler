#include "ast/blocks/switch/ast_switch.hpp"

// Constructor
Switch::Switch(NodePtr expression, NodePtr scope)
{
  branches.push_back(expression);
  branches.push_back(scope);
}

// Destructor
Switch::~Switch()
{
  delete branches[0];
  delete branches[1];
}

// Visualising
void Switch::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Switch [" << std::endl;
  dst << indent << "Expression: " << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "SwitchScope:" << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endSwitch" << std::endl;
}

// Codegen
void Switch::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  //Basically evaluate condition, compare with condition of each case subnode
  // Potential workaround is to evaluate expression into special reg, and pass that along to the cases so they can do everything
  context.enterScope();
  // Use $s1 to store evaluated expression for case comparison
  dst << "addiu $29,$29,-4" << std::endl;
  context.stack.back().offset += 4;
  context.stack.back().varBindings["$s1"] = {4, -context.stack.back().offset, -1};
  dst << "sw $17,0($29)" << std::endl;
  branches[0]->generateMIPS(dst, context, 17);

  // Break stuff
  std::string endLabel = context.makeLabel("END");
  context.stack.back().endLabel = endLabel;

  unsigned i = 0;
  NodePtr node = branches[1]->getNode(i);
  while(node != NULL){
    node->generateMIPS(dst, context, destReg);
    i++;
    node = branches[1]->getNode(i);
  }
  dst << endLabel << ":" << std::endl;

  // Restore $s1
  dst << "lw $17," << context.stack.back().varBindings["$s1"].offset << "($30)" << std::endl;
  context.exitScope(dst);
}
