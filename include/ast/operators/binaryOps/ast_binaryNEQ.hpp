#ifndef ast_binaryNEQ_hpp
#define ast_binaryNEQ_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryNEQ
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif