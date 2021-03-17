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

  // Getting identifier
  std::string getId() const override;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  virtual void generateMIPS(std::ostream &dst, Context context, int destReg) const override;
};

#endif
