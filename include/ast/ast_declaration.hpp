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
  NodePtr getNode(unsigned index) const override;
  int getSize() const override;
  std::string getId() const override;
  bool isFunction() const override;
  bool isInit() const override;
  int getArraySize() const override;
  int getValue() const override;
  int getValue(int i) const override;
};

#endif
