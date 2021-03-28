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
      return 4; // You should never really try to getSize of void, just loads integer 0
    case _unsigned:
      return 4;
    case _char:
      return 1;
    case _float:
      return 4;
    case _double:
      return 8;
    default:
      std::cerr << "Tried to getsize of something with no primitive type" << std::endl;
      return 0;
  }
}

std::string PrimitiveType::getType() const
{
  switch(type){
    case _int:
      return "_int";
    case _void:
      return "_void";
    case _unsigned:
      return "_unsigned";
    case _char:
      return "_char";
    case _float:
      return "_float";
    case _double:
      return "_double";
    default:
      std::cerr << "Tried to getType of something with no primitve type" << std::endl;
      return "";
  }
}
