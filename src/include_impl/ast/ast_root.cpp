#include "ast/ast_root.hpp"

// Constructor
Root::Root(NodePtr globalScope)
{
  branches.push_back(globalScope);
}

// Destructor
Root::~Root()
{
  delete branches[0];
}

// Visualising
void Root::PrettyPrint(std::ostream &dst, std::string indent) const
{
  branches[0]->PrettyPrint(dst, indent);
}

// Codegen
void Root::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  branches[0]->generateMIPS(dst, context, destReg);
}
