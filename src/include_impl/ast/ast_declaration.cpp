#include "ast/ast_declaration.hpp"

// Constructors
/* Legacy code, refer back if needed
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
*/
Declaration::Declaration(NodePtr type, NodePtr id)
{
  branches.push_back(type);
  branches.push_back(id);
}

Declaration::Declaration(NodePtr type)
  : Declaration(type, new Identifier("<NULL>"))
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

std::string Declaration::getId() const
{
  return branches[1]->getId();
}

// Visualising
void Declaration::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Declaration [" << std::endl;
  dst << indent+"  " << "Type: ";
  branches[0]->PrettyPrint(dst, indent+"  ");
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

void Declaration::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // Check the type of branches1 to see if it's a variable / function declaration
  int size = branches[0]->getSize();
  if(branches[1]->isFunction()){
    branches[1]->generateMIPS(dst, context, destReg);
  }
  else{
    std::string id = branches[1]->getId();
    context.stack.back().varBindings[id] = {size, -1};
  }
}
