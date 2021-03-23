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

  virtual std::string getId() const override;
  virtual bool isFunction() const override;
  virtual bool isInit() const override;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

};

#endif
