#ifndef ast_binaryRShift_hpp
#define ast_binaryRShift_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryRShift
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif