#ifndef ast_binaryAssign_hpp
#define ast_binaryAssign_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryAssign
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
    virtual void generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const override;

};

#endif
