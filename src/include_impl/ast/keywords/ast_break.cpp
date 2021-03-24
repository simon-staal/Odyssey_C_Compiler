#include "ast/keywords/ast_break.hpp"

void Break::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "BREAK" << std::endl;
}

void Break::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  dst << "b " << context.stack.back().endLabel << std::endl;
  dst << "nop" << std::endl;
}
