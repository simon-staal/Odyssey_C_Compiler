#ifndef ast_typedef_hpp
#define ast_typedef_hpp

#include "ast/ast_node.hpp"

class TypeDef
  : public Node
{
public:
  // Constructor
  TypeDef(NodePtr type);

  // Destructor
  ~TypeDef();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;
};




#endif
