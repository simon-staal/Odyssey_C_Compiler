#ifndef ast_identifier_hpp
#define ast_identifier_hpp

#include "ast_node.hpp"

class Identifier
  : public Node
{
protected:
  std::string id;
public:
  // Constructor
  Identifier(std::string _id);

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  std::string getId() const override; // Getting identifier
  int getSize(Context &context) const override; // Size of variable
};

#endif
