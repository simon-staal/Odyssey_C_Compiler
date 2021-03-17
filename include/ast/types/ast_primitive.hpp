#ifndef ast_primitive_hpp
#define ast_primitive_hpp

#include "ast/ast_node.hpp"

class PrimitiveType
  : public Node
{
public:
  enum Specifier {
    // Supported types
    _int
  };

  PrimitiveType(Specifier _type);

  int getSize() const override;

  ~PrimitiveType();

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

protected:
  Specifier type;
};

#endif
