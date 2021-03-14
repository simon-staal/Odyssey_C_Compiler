#include "ast/operators/ast_binaryOperation.hpp"

BinaryOperation::BinaryOperation(NodePtr left, NodePtr right)
{
    branches.push_back(left);
    branches.push_back(right);
}

BinaryOperation::~BinaryOperation()
{
    delete branches[0];
    delete branches[1];
}

NodePtr BinaryOperation::LeftOp() const
{
    return branches[0];
}

NodePtr BinaryOperation::RightOp() const
{
    return branches[1];
}
