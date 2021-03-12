#include "ast/types/ast_primitive.hpp"

PrimitiveType::PrimitiveType(Specifier _type)
  : type(_type)
{}

PrimitiveType::~PrimitiveType()
{};

void PrimitiveType::PrettyPrint(std::ostream &dst, std::string indent) const
{
  switch(type){
    case _int:
      dst << "int";
      break;
    default:
      dst << "unknown type ";
  }
  dst << std::endl;
}
