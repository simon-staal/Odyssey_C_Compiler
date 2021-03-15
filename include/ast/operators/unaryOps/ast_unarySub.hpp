#ifndef ast_unarySub_hpp
#define ast_unarySub_hpp

#include "ast/operators/ast_unaryOperation.hpp"

class UnarySub
    : public UnaryOperation
{
public:

    using UnaryOperation::UnaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif


