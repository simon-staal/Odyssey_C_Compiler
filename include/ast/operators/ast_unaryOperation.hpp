#ifndef ast_unaryOperation_hpp
#define ast_unaryOperation_hpp

#include "ast/ast_node.hpp"

class UnaryOperation
    : public Node

{
protected:

    NodePtr GetOp() const;

public:

    UnaryOperation(NodePtr op);

    virtual ~UnaryOperation();

    //implement in its derived functions
    virtual void PrettyPrint(std::ostream &dst, std::string indent) const = 0;

};

#endif