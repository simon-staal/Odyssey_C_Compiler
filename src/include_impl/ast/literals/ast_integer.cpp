#include "ast/literals/ast_integer.hpp"

// Constructor
Integer::Integer(int _value)
  : value(_value)
{}

Integer::Integer() // Default initializer
  : Integer(0)
{}

// Visualising
void Integer::PrettyPrint(std::ostream &dst, std::string indent) const
{
    dst << indent << "Integer = " << value << std::endl;
}

// Codegen
void Integer::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // I don't think this stuff is relevant since we're passing destReg to this node, leaning just in case (I didn't write this)
  if(destReg == -1){
    for(auto it = context.stack.back().varBindings.begin(); it != context.stack.back().varBindings.end(); it++){
      if (it->second.reg != -1){
        context.regFile.freeReg(it->second.reg); // This variable can still be accessed directly from memory
        destReg = it->second.reg;
        it->second.reg = -1; // Inidicate this variable is no longer available in register
      }
    }
  }

  // All that's relevant imo
  dst << "li $" << destReg << "," << value << std::endl;
}

int Integer::getValue() const // returns value
{
  return value;
}

int Integer::getSize() const
{
  return 4; // Int size is 4
}
