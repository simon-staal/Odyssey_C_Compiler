#ifndef ast_binaryEQ_hpp
#define ast_binaryEQ_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryEQ
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif