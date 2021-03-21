#include "ast/literals/ast_integer.hpp"

// Constructor
Integer::Integer(int _value)
  : value(_value)
{}

Integer::Integer() // Default initializer
  : Integer(0)
{}

// Useful shit (probs)
int Integer::getValue() const
{
  return value;
}

// Visualising
void Integer::PrettyPrint(std::ostream &dst, std::string indent) const
{
    dst << indent << "Integer = " << value << std::endl;
}

void Integer::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  if(destReg == -1){
    for(auto it = context.stack.back().varBindings.begin(); it != context.stack.back().varBindings.end(); it++){
      if (it->second.reg != -1){
        context.regFile.freeReg(it->second.reg); // This variable can still be accessed directly from memory
        destReg = it->second.reg;
        it->second.reg = -1; // Inidicate this variable is no longer available in register
      }
     }
    }

  dst << "li $" << destReg << ", " << getValue() << std::endl;
}
