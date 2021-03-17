#ifndef ast_binaryRightAss_hpp
#define ast_binaryRightAss_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryRightAss
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;


};

#endif

