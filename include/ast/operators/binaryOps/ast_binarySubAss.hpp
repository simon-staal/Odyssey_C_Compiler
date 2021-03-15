#ifndef ast_binarySubAss_hpp
#define ast_binarySubAss_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinarySubAss
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif

