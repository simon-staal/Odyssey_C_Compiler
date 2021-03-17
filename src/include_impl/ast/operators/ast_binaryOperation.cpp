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

void BinaryOperation::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::cerr << "Binary shit doesn't yet Kai you lazy fuck" << std::endl;
}

void BinaryOperation::EZPrint(std::ostream &dst, std::string instr, int destReg, int regLeft, int regRight) const
{
    dst << instr << " $" << destReg << ", $" << regLeft << ", $" << regRight << std::endl;
}

