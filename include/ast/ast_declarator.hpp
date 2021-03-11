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
  Declarator(NodePtr id);

  Declarator(std::string id);

  // Destructor
  virtual ~Declarator();

  // Where stuff is
  NodePtr getId() const;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
};

#endif
