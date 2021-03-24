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
void generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  //Basically evaluate condition, compare with condition of each subnode
  // Make a bunch of labels to jump around, if default always do it (default is last element)
  // Potential workaround is to evaluate expression into special reg, and pass that along to the cases so they can do everything
}
