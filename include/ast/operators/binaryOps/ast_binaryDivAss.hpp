#ifndef ast_binaryDivAss_hpp
#define ast_binaryDivAss_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryDivAss
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif

