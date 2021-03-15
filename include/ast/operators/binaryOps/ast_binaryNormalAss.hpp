#ifndef ast_binaryNormalAss_hpp
#define ast_binaryNormalAss_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryNormalAss
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif

