#include "ast/ast_root.hpp"

Root::Root(NodePtr globalScope)
{
  branches.push_back(globalScope);
}

Root::~Root()
{
  delete branches[0];
}

void Root::PrettyPrint(std::ostream &dst, std::string indent) const
{
  branches[0]->PrettyPrint(dst, indent);
}

void Root::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  branches[0]->generateMIPS(dst, context, destReg);
}
