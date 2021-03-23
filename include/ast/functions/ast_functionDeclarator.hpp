#ifndef ast_functionDeclarator_hpp
#define ast_functionDeclarator_hpp

#include "ast/ast_node.hpp"
#include "ast/ast_nodeList.hpp"

class FunctionDeclarator
  : public Node
{
public:
  // Constructors
  FunctionDeclarator(NodePtr id, NodeListPtr params);
  FunctionDeclarator(NodePtr id, std::vector<NodePtr> params);
  FunctionDeclarator(NodePtr id);

  // Destructor
  virtual ~FunctionDeclarator();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  virtual NodePtr getNode(unsigned index) const override;
  virtual std::string getId() const override;
  virtual bool isFunction() const override;
};

#endif
