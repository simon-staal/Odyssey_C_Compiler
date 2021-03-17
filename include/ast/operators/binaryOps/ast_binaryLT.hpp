#ifndef ast_binaryLT_hpp
#define ast_binaryLT_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryLT
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
    virtual void generateMIPS(std::ostream &dst, Context context, int destReg) const override;


};

#endif
