#include "ast/operators/binaryOps/ast_binarySubAss.hpp"

void BinarySubAss::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary SubAss [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+ "  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void BinarySubAss::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  variable Var = LeftVar(context);

  RightOp()->generateMIPS(dst, context, destReg);

  ifFunction(dst, context, destReg);

  if( Var.reg == -1){
    int reg = context.allocate();
    dst << "lw $" << reg << ", " << Var.offset << "($30)" << std::endl;
    EZPrint(dst, "sub", reg, reg, destReg);
    Var.reg = reg;

  }else{

    EZPrint(dst, "sub", Var.reg, Var.reg, destReg);
  }
}
 
