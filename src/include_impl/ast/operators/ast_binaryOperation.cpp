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

int BinaryOperation::DoLeft(std::ostream &dst, Context &context, int destReg) const
{

  // Process left operand
  LeftOp()->generateMIPS(dst, context, destReg);
  int regLeft = context.allocate();
  if(LeftOp()->isFunction()){
    dst << "move $" << regLeft << ",$2" << std::endl;
  }else{
    dst << "move $" << regLeft << ", $" << destReg << std::endl;
  }

    return regLeft;

}

int BinaryOperation::DoRight(std::ostream &dst, Context &context, int destReg, int regLeft) const
{

  // Process right operand
  if(RightOp()->isFunction()){ // Preserve leftop across function call
    // Preserves $s0
    dst << "addiu $29,$29,-4" << std::endl;
    context.stack.back().offset += 4;
    context.stack.back().varBindings["$s0"] = {4, -context.stack.back().offset, -1};
    dst << "sw $s0,0($29)" << std::endl;
    // Move leftOp into $s0 to be preserved
    dst << "move $s0,$" << regLeft << std::endl;
  }

  RightOp()->generateMIPS(dst, context, destReg);
  int regRight = context.allocate();
  if(RightOp()->isFunction()){
    // Restore regleft
    dst << "move $" << regLeft << ", $s0" << std::endl;
    // Restore $s0
    dst << "lw $s0," << context.stack.back().varBindings["$s0"].offset << "($30)" << std::endl;
    dst << "move $" << regRight << ",$2" << std::endl;
  }else{
    dst << "move $" << regRight << ", $" << destReg << std::endl;
  }

    return regRight;

}

variable BinaryOperation::LeftVar(Context &context) const
{
  
  std::string id = LeftOp()->getId();
  variable left;

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    std::cerr << "Uninitialised Variable?" << std::endl;
  }else{
    left = it->second;
  }

  return left;

}

void BinaryOperation::AssEnd(std::ostream &dst, Context &context, int destReg, variable VarLeft) const
{
  dst << "sw $" << destReg << ", "<< VarLeft.offset << "($30)" << std::endl; // Stores result in variable
  if(VarLeft.reg == -1){
    //not stored in registers
  }else{
    dst << "move $" << VarLeft.reg << ", $" << destReg << std::endl;
  }
}

void BinaryOperation::ifFunction(std::ostream &dst, Context &context, int destReg) const
{
    if(RightOp()->isFunction()){
        dst << "move $" << destReg << ", $2" << std::endl;

    }
}