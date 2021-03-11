#include "ast/types/ast_primitive.hpp"

PrimitiveType::PrimitiveType(Specifier _type)
  : type(_type)
{}

void PrimitiveType::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent;
  switch(type){
    case _int:
      dst << "int: ";
      break;
    default:
      dst << "unknown type ";
  }
}
