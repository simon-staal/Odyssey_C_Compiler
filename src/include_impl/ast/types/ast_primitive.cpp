#include "ast/types/ast_primitive.hpp"

PrimitiveType::PrimitiveType(Specifier _type)
  : type(_type)
{}

PrimitiveType::~PrimitiveType()
{};

int PrimitiveType::getSize() const
{
  switch(type){
    case _int:
      return 4;
    default:
      return NULL;
  }
}

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
