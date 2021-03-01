#ifndef ast_primitive_hpp
#define ast_primitive_hpp

#include "ast_node.hpp"

class PrimitiveType
  : public Node
{
public:
  enum Specifier {
    // Supported types
    _int
  };

  PrimitiveType(Specifier _type)
    : type(_type);
  {}

  ~PrimitiveType();

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent;
    switch(type){
      case _int:
        dst << "int ";
        break;
      default:
        dst << "unknown type ";
    }
  }

protected:
  Specifier type;
};

#endif
