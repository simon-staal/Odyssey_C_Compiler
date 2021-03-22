#ifndef ast_root_hpp
#define ast_root_hpp

#include "ast_node.hpp"

class Root
  : public Node
{
public:
  // Constructor
  Root(NodePtr globalScope);

  // Destructor
  virtual ~Root();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
