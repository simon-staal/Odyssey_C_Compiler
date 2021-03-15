#ifndef ast_unaryPreDec_hpp
#define ast_unaryPreDec_hpp

#include "ast/operators/ast_unaryOperation.hpp"

class UnaryPreDec
    : public UnaryOperation
{
public:

    using UnaryOperation::UnaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif
