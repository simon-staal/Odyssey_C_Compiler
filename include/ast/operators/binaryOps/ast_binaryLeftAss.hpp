#ifndef ast_binaryLeftAss_hpp
#define ast_binaryLeftAss_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryLeftAss
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif

