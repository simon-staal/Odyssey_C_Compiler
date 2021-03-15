#ifndef ast_binaryANDAss_hpp
#define ast_binaryANDAss_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryANDAss
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif

