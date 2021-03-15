#ifndef ast_binaryLShift_hpp
#define ast_binaryLShift_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryLShift
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif