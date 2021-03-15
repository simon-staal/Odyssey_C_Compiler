#ifndef ast_binaryGTEQ_hpp
#define ast_binaryGTEQ_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryGTEQ
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif