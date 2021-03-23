#include "ast/ast_empty.hpp"

void EmptyNode::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "EmptyNode" << std::endl;
}
