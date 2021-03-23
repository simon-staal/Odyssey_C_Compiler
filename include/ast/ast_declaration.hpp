#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include "ast_node.hpp"
#include "ast_identifier.hpp"

// Represents declarations as type (i.e. int) + what the declaration actually is, which could be a bunch of stuff

class Declaration
  : public Node
{
public:
  // Constructors
  Declaration(NodePtr type, NodePtr id);
  Declaration(NodePtr type);

  // Destructor
  virtual ~Declaration();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  virtual NodePtr getNode(unsigned index) const override;
  virtual int getSize() const override;
  virtual std::string getId() const override;
};

#endif
