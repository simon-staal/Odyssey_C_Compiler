#ifndef ast_functionCall_hpp
#define ast_functionCall_hpp

#include "ast/ast_node.hpp"
#include "ast/lists/ast_nodeList.hpp"

// Represents a function call as an identifier + parameters

class FunctionCall
  : public Node
{
public:
  // Constructors
  FunctionCall(NodePtr id, NodeListPtr params);
  FunctionCall(NodePtr id, std::vector<NodePtr> params);
  FunctionCall(NodePtr id); // No params

  // Destructor
  virtual ~FunctionCall();

  virtual std::string getId() const override;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
