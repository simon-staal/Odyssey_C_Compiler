#include "ast/types/ast_primitive.hpp"

PrimitiveType::PrimitiveType(Specifier _type)
  : type(_type)
{}

PrimitiveType::~PrimitiveType();

virtual void PrimitiveType::PrettyPrint(std::ostream &dst, std::string indent) const override
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
