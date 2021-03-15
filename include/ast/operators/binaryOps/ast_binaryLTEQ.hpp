#ifndef ast_binaryLTEQ_hpp
#define ast_binaryLTEQ_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryLTEQ
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif