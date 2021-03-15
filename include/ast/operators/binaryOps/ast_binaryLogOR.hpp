#ifndef ast_binaryLogOR_hpp
#define ast_binaryLogOR_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryLogOR
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif