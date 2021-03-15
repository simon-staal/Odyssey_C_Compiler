#include "ast/operators/ast_unaryOperation.hpp"

BinaryOperation::BinaryOperation(NodePtr op)
{
    branches.push_back(op);
}

BinaryOperation::~BinaryOperation()
{
    delete branches[0];
}

NodePtr BinaryOperation::getOp() const
{
    return branches[0];
}

