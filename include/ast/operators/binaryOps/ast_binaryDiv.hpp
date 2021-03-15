#ifndef ast_binaryDiv_hpp
#define ast_binaryDiv_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryDiv
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif
