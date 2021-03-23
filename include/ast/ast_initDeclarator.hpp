#ifndef ast_initDeclarator_hpp
#define ast_initDeclarator_hpp

#include "ast_declarator.hpp"

// This is used for declarations which are initialised (int x = 3;)
// Basically a combination of declarator and binaryNormalAssign, but i'm too lazy to think
// of an elegant way to combine them so I'm just making a new class

class InitDeclarator
  : public Node
{
public:
  // Consturctor
  InitDeclarator(NodePtr declarator, NodePtr initializer);

  // Destructor
  virtual ~InitDeclarator();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  virtual std::string getId() const override;
  virtual bool isFunction() const override;
  virtual bool isInit() const override;

};

#endif
