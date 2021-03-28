#ifndef ast_enumSpecifier_hpp
#define ast_enumSpecifier_hpp

#include "ast/ast_node.hpp"

class EnumSpecifier
  : public Node
{
public:
  // Constructor
  EnumSpecifier(std::string _id, std::vector<NodePtr> enums);
  EnumSpecifier(std::string _id); // Not sure what this actually does functionally

  // Destructor
  ~EnumSpecifier();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  std::string getId() const override;
  int getSize() const override;
  bool isEnum() const override;
  enum Specifier getType() const override;

protected:
  std::string id;
};

#endif
