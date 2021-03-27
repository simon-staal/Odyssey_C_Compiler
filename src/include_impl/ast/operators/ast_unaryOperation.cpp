#include "ast/operators/ast_unaryOperation.hpp"

UnaryOperation::UnaryOperation(NodePtr op)
{
    branches.push_back(op);
}

UnaryOperation::~UnaryOperation()
{
    delete branches[0];
}

NodePtr UnaryOperation::getOp() const
{
    return branches[0];
}

void UnaryOperation::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
    
}

void UnaryOperation::ifFunction(std::ostream &dst, Context &context, int destReg) const
{
    if(getOp()->isFunction()){
        dst << "move $" << destReg << ", $2" << std::endl;

    }
}

std::string UnaryOperation::getId() const
{
    return branches[0]->getId();
}

bool UnaryOperation::isPtr() const
{
    return branches[0]->isPtr();
}