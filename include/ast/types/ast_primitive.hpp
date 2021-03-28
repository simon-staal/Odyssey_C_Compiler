#ifndef ast_primitive_hpp
#define ast_primitive_hpp

#include "ast/ast_node.hpp"

class PrimitiveType
  : public Node
{
public:
  // Constructor
  PrimitiveType(enum Specifier _type);

  // Destructor
  ~PrimitiveType();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Helper for codegen
  int getSize() const override;
  std::string getType() const override;
protected:
  enum Specifier type;
};

#endif
