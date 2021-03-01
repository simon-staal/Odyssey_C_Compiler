#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include "ast_expression.hpp"

class Declaration
  : public Expression
{
public:
  virtual ~Declaration();

  Declaration(NodePtr type)
  {
    branches.push_back(type);
    branches.push_back(0);
  }

  Declaration(NodePtr type, NodePtr id)
  {
    branches.push_back(type);
    branches.push_back(id);
  }

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "Declaration [" << std::endl;
    dst << "type = ";
    branches[0]->PrettyPrint(dst, indent+"  ");
    dst << "id = ";
    branches[1]->PrettyPrint(dst, indent+"  ");
    dst << indent << "]" << std::endl;
  }
};

#endif
