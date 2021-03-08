#ifndef ast_return_hpp
#define ast_return_hpp

#include "ast_node.hpp"

class Return;

typedef const Return* ReturnPtr;

class Return
  : public Node
{

protected:

    ExprPtr expr;

public:
    
    Return(ExprPtr _expr)
    : expr(_expr)
    {}

    Return()
    {}

};

#endif