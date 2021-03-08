#ifndef ast_declaration_hpp
#define ast_declaration_hpp

#include "ast_node.hpp"
#include "ast_nodeList.hpp"

// Represents declarations as type (i.e. int) + what the declaration actually is, which could be a bunch of stuff

class Declaration
  : public Node
{
public:
  // Constructors
  // For scaling, not necessary atm (probably lmao)
  // Basically, we're gonna always have a declaration as a type at branches[0] and then a list of declarations at branches[1]
  Declaration(NodePtr type, NodeListPtr declarations)
  {
    branches.push_back(type);
    branches.push_back(declarations);
  }

  Declaration(NodePtr type, std::vector<NodePtr> declarations)
    : Declaration(type, new NodeList(declarations))
  {}

  // Case where it's just 1 declaration (probs the one we'll usually use)
  Declaration(NodePtr type, NodePtr declaration)
    : Declaration(type, std::vector<NodePtr>{declaration})
  {}

  // idk if we ever have a declaration with just a type, this is here just in case ig
  Declaration(NodePtr type)
    : Declaration(type, std::vector<NodePtr>{})
  {}

  // Destructor
  virtual ~Declaration()
  {
    delete branches[0];
    delete branches[1];
  }

  // Where things in should be
  NodePtr getType() const
  {
    return branches[0];
  }

  NodeListPtr getDeclarations() const
  {
    return branches[1];
  }

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "Declaration [" << std::endl;
    dst << "Type: ";
    branches[0]->PrettyPrint(dst, indent+"  ");
    dst << "Declarations: ";
    branches[1]->PrettyPrint(dst, indent+"  ");
    dst << indent << "]" << std::endl;
  }
};

#endif
