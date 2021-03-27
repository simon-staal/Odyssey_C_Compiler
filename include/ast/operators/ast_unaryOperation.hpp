#ifndef ast_unaryOperation_hpp
#define ast_unaryOperation_hpp

#include "ast/ast_node.hpp"

class UnaryOperation
    : public Node

{
protected:

    NodePtr getOp() const;

public:

    UnaryOperation(NodePtr op);

    virtual ~UnaryOperation();

    //implement in its derived functions
    virtual void PrettyPrint(std::ostream &dst, std::string indent) const = 0;

    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const;

    void ifFunction(std::ostream &dst, Context &context, int destReg) const;
    
    bool isPtr() const override;

    std::string getId() const;


};

#endif