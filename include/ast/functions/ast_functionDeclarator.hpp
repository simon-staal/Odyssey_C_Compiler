#ifndef ast_functionDeclarator_hpp
#define ast_functionDeclarator_hpp

#include "ast/ast_node.hpp"
#include "ast/ast_nodeList.hpp"

class FunctionDeclarator
  : public Node
{
public:
  // Constructors
  // Using a NodeListPtr for params to have scalability, currently will be empty for main()
  FunctionDeclarator(NodePtr id, NodeListPtr params);
  FunctionDeclarator(NodePtr id, std::vector<NodePtr> params);
  // Should work for `main()`
  FunctionDeclarator(NodePtr id);

  // Destructor, not 100% sure if correct
  virtual ~FunctionDeclarator();

  //This is where things should be
  NodePtr getIdentifier() const;

  NodePtr getParams() const;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

};

#endif
