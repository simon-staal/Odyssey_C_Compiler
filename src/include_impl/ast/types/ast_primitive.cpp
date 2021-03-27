#include "ast/types/ast_primitive.hpp"

// Constructor
PrimitiveType::PrimitiveType(Specifier _type)
  : type(_type)
{}

// Destructor
PrimitiveType::~PrimitiveType()
{};

// Visualising
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

// Codegen helper
int PrimitiveType::getSize() const
{
  switch(type){
    case _int:
      return 4;
    case _void:
      return 1; // Godbolt says so, this is invalid tho
    case _unsigned:
      return 4;
    case _char:
      return 1;
    default:
      return 0;
  }
}
