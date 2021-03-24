#include "ast/operators/binaryOps/ast_binaryNormalAss.hpp"

void BinaryNormalAss::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary NormalAss [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+ "  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void BinaryNormalAss::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  NodePtr Index;
  variable Var = LeftVar(context);
  if((Index = LeftOp()->getNode(1)) != NULL ){ // THEN ITS AN ARRAY

    Index->generateMIPS(dst, context, destReg);
    int reg = context.allocate();

    dst << "addiu $" << reg << ", $0, " << Var.size << std::endl;
    dst << "mult $" << destReg << ", $" << reg << std::endl;
    dst << "mflo $" << destReg << std::endl;
    dst << "addiu $" << destReg << ", $" << destReg << ", " << Var.offset << std::endl;
    dst << "move $" << reg << ", $30" << std::endl;
    dst << "add $" << destReg << ", $" << destReg << ", $" << reg << std::endl;

    RightOp()->generateMIPS(dst, context, reg);
    dst << "sw $" << reg << ", 0($" << destReg << ")" << std::endl;
    dst << "move $" << destReg << ", $" << reg << std::endl;

    context.regFile.freeReg(reg);
     


  }else{

    RightOp()->generateMIPS(dst, context, destReg);
    ifFunction(dst, context, destReg);
    AssEnd(dst, context, destReg, Var);
  }
}
