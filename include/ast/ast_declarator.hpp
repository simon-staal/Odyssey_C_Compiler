#ifndef ast_declarator_hpp
#define ast_declarator_hpp

#include "ast_node.hpp"
#include "ast_identifier.hpp"

// Used for base declarators from parser, functionDeclarator uses this as its id

class Declarator
  : public Node
{
public:
  // Constructors
  Declarator(NodePtr id)
  {
    branches.push_back(id);
  }

  Declarator(std::string id)
    : Declarator(new Identifier(id))
  {}

  // Destructor
  virtual ~Declarator()
  {
    delete branches[0];
  }

  // Where stuff is
  NodePtr getId() const
  {
    return branches[0];
  }

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "Declarator: [" << std::endl;
    branches[0]->PrettyPrint(dst, indent+"  ");
    dst << indent << "]" << std::endl;
  }
};

#endif
