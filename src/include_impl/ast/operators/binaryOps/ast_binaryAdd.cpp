#include "ast/operators/binaryOps/ast_binaryAdd.hpp"

void BinaryAdd::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Addition [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinaryAdd::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  int regLeft, regRight;
  if( ((regLeft = context.regFile.allocate()) == -1) |  ((regRight = context.regFile.allocate()) == -1) ){
    std::cerr << "OOPSIES NO REGS ARE FREE. OVERWRITING" << std::endl;
  }

  // Process left operand
  LeftOp()->generateMIPS(dst, context, regLeft);
  if(LeftOp()->isFunction()){
    dst << "move $" << regLeft << ",$2" << std::endl;
  }

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
  RightOp()->generateMIPS(dst, context, regRight);
  if(RightOp()->isFunction()){
    // Restore regleft
    dst << "move $" << regLeft << ",$s0" << std::endl;
    // Restore $s0
    dst << "lw $s0," << context.stack.back().varBindings["$s0"].offset << "($30)" << std::endl;
    dst << "move $" << regRight << ",$2" << std::endl;
  }

  EZPrint(dst, "add", destReg, regLeft, regRight);

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}
