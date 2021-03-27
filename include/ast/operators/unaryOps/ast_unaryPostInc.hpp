#ifndef ast_unaryPostInc_hpp
#define ast_unaryPostInc_hpp

#include "ast/operators/ast_unaryOperation.hpp"

class UnaryPostInc
    : public UnaryOperation
{
public:

    using UnaryOperation::UnaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;


};

#endif
