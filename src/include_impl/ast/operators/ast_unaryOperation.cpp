#include "ast/operators/ast_unaryOperation.hpp"

UnaryOperation::UnaryOperation(NodePtr op)
{
    branches.push_back(op);
}

UnaryOperation::~UnaryOperation()
{
    delete branches[0];
}

NodePtr UnaryOperation::GetOp() const
{
    return branches[0];
}

