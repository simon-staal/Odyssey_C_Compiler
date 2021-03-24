#include "ast/keywords/ast_continue.hpp"

void Continue::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "CONTINUE" << std::endl;
}

void Continue::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  dst << "b " << context.stack.back().startLabel << std::endl;
}
