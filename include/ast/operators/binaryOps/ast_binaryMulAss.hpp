#ifndef ast_binaryMulAss_hpp
#define ast_binaryMulAss_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryMulAss
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;


};

#endif

