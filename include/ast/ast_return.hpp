#ifndef ast_return_hpp
#define ast_return_hpp

// Haven't looked at this, idk if it's still relevant

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


};

#endif
