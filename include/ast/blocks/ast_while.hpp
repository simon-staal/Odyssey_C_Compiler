#ifndef ast_while_hpp
#define ast_while_hpp

#include "ast/ast_node.hpp"

class While
  : public Node
  {
  public:
    // Constructor
    While(NodePtr condition, NodePtr scope);

    // Destructor
    virtual ~While();

    // Where things should be
    NodePtr getCondition() const;
    NodePtr getScope() const;

    // Visualising
    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  };

#endif
