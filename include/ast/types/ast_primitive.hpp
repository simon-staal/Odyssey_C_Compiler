#ifndef ast_primitive_hpp
#define ast_primitive_hpp

#include "ast/ast_node.hpp"

class PrimitiveType
  : public Node
{
public:
  // Supported types
  enum Specifier {
    _int
  };

  // Constructor
  PrimitiveType(Specifier _type);

  // Destructor
  ~PrimitiveType();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Helper for codegen
  int getSize() const override;
protected:
  Specifier type;
};

#endif
