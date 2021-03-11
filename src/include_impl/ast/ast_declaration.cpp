#include "ast/ast_declaration.hpp"

// Constructors
// For scaling, not necessary atm (probably lmao)
// Basically, we're gonna always have a declaration as a type at branches[0] and then a list of declarations at branches[1]
Declaration::Declaration(NodePtr type, NodeListPtr declarations)
{
  branches.push_back(type);
  branches.push_back(declarations);
}

Declaration::Declaration(NodePtr type, std::vector<NodePtr> declarations)
  : Declaration(type, new NodeList(declarations))
{}

// Case where it's just 1 declaration (probs the one we'll usually use)
Declaration::Declaration(NodePtr type, NodePtr declaration)
  : Declaration(type, std::vector<NodePtr>{declaration})
{}

// idk if we ever have a declaration with just a type, this is here just in case ig
Declaration::Declaration(NodePtr type)
  : Declaration(type, std::vector<NodePtr>{})
{}

// Destructor
Declaration::~Declaration()
{
  delete branches[0];
  delete branches[1];
}

// Where things in should be
NodePtr Declaration::getType() const
{
  return branches[0];
}

NodePtr Declaration::getDeclarations() const // Actually returns a NodeListPtr (but it's stored as a NodePtr)
{
  return branches[1];
}

// Visualising
void Declaration::PrettyPrint(std::ostream &dst, std::string indent) const 
{
  dst << indent << "Declaration [" << std::endl;
  dst << "Type: ";
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << "Declarations: ";
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}
