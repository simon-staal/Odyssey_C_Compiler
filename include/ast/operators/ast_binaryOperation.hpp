#ifndef ast_binaryOperation_hpp
#define ast_binaryOperation_hpp

#include "ast/ast_node.hpp"

class BinaryOperation
    : public Node

{
protected:

    NodePtr LeftOp() const;
    NodePtr RightOp() const;

public:

    BinaryOperation(NodePtr left, NodePtr right);

    virtual ~BinaryOperation();

    //implement in its derived functions
    virtual void PrettyPrint(std::ostream &dst, std::string indent) const = 0;

    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const;
};

#endif
