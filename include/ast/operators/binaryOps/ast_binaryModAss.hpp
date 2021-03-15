#ifndef ast_binaryModAss_hpp
#define ast_binaryModAss_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinaryModAss
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif

