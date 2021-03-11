#include "ast/functions/ast_functionDeclarator.hpp"

// Constructors
// Using a NodeListPtr for params to have scalability, currently will be empty for main()
FunctionDeclarator::FunctionDeclarator(NodePtr id, NodeListPtr params)
{
  branches.push_back(id);
  branches.push_back(params);
}

FunctionDeclarator::FunctionDeclarator(NodePtr id, std::vector<NodePtr> params)
  : FunctionDeclarator(id, new NodeList(params))
{}

// Should work for `main()`
FunctionDeclarator::FunctionDeclarator(NodePtr id)
  : FunctionDeclarator(id, new NodeList())
{}

// Destructor, not 100% sure if correct
virtual FunctionDeclarator::~FunctionDeclarator()
{
  delete branches[0];
  delete branches[1];
}

//This is where things should be
NodePtr FunctionDeclarator::getIdentifier() const
{
  return branches[0];
}

NodePtr FunctionDeclarator::getParams() const
{
  return branches[1];
}

// Visualising
virtual void FunctionDeclarator::PrettyPrint(std::ostream &dst, std::string indent) const override
{
  dst << indent << "Function Declarator [" << std::endl;
  dst << "Identifier: ";
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << "Parameters: ";
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}
