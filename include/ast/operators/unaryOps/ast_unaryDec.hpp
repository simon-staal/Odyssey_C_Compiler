#ifndef ast_unaryDec_hpp
#define ast_unaryDec_hpp

#include "ast/operators/ast_unaryOperation.hpp"

class UnaryDec
    : public UnaryOperation
{
public:

    using UnaryOperation::UnaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;


};

#endif
