#ifndef ast_unaryNOT_hpp
#define ast_unaryNOT_hpp

#include "ast/operators/ast_unaryOperation.hpp"

class UnaryNOT
    : public UnaryOperation
{
public:

    using UnaryOperation::UnaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;


};

#endif


