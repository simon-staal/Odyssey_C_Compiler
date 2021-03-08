#ifndef ast_functionDeclarator_hpp
#define ast_functionDeclarator_hpp

#include "ast_node.hpp"
#include "ast_nodeList.hpp"

class FunctionDeclarator
  : public Node
{
public:
  // Constructors
  // Using a NodeListPtr for params to have scalability, currently will be empty for main()
  FunctionDeclarator(NodePtr id, NodeListPtr params)
  {
    branches.push_back(id);
    branches.push_back(params);
  }

  FunctionDeclarator(NodePtr id, std::vector<NodePtr> params)
    : FunctionDeclarator(id, new NodeList(params))
  {}

  // Should work for `main()`
  FunctionDeclarator(NodePtr id)
    : FunctionDeclarator(id, new NodeList())
  {}

  // Destructor, not 100% sure if correct
  virtual ~FunctionDeclarator()
  {
    delete branches[0];
    delete branches[1];
  }

  //This is where things should be
  NodePtr getIdentifier() const
  {
    return branches[0];
  }

  NodePtr getParams() const
  {
    return branches[1];
  }

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "Function Declarator [" << std::endl;
    dst << "Identifier: ";
    branches[0]->PrettyPrint(dst, indent+"  ");
    dst << "Parameters: "
    branches[1]->PrettyPrint(dst, indent+"  ");
    dst << indent << "]" << std::endl;
  }

};

#endif
