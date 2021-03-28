#ifndef ast_binarySub_hpp
#define ast_binarySub_hpp

#include "ast/operators/ast_binaryOperation.hpp"

class BinarySub
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
    void generateTypeMIPS(std::ostream &dst, Context &context, int destReg, std::string type) const override;



};

#endif
