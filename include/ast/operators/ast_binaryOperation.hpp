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

    virtual void EZPrint(std::ostream &dst, std::string instr, int destReg, int regLeft, int regRight) const;

    virtual int DoLeft(std::ostream &dst, Context &context, int destReg) const;

    virtual int DoRight(std::ostream &dst, Context &context, int destReg, int regLeft) const;

    virtual variable LeftVar(Context &context) const;

    void ifFunction(std::ostream &dst, Context &context, int destReg) const;

    virtual void generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const;

    bool isPtrVar(Context &context, NodePtr op) const;

    int DoTypeLeft(std::ostream &dst, Context &context, int destReg, enum Specifier type) const;

    int DoTypeRight(std::ostream &dst, Context &context, int destReg, enum Specifier type) const;

};



#endif
