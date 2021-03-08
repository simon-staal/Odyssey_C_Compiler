#ifndef ast_expression_hpp
#define ast_expression_hpp

// This shit is probs useless now that node contains branches
// Leaving here for now just in case

#include "ast_node.hpp"

class Expression;
typedef const Expression *ExprPtr;

class Expression
  : public Node
{
public:
  virtual ~Expression()
  {
    for(unsigned i = 0; i < branches.size(); i++){
      delete branches[i];
    }
  }

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "Expression [" << std::endl;
    for(unsigned i = 0; i < branches.size(); i++){
      branches[i]->PrettyPrint(dst, indent+"  ");
    }
    dst << indent << "]" << std::endl;
  }
};

#endif
