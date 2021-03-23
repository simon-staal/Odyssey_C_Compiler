#include "ast/operators/binaryOps/ast_binaryDivAss.hpp"

void BinaryDivAss::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary DivAss [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+ "  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void BinaryDivAss::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  variable Var = LeftVar(context);

  RightOp()->generateMIPS(dst, context, destReg);

  if( Var.reg == -1){
    int reg = context.allocate();
    dst << "lw $" << reg << ", " << Var.offset << "($30)" << std::endl;
    dst << "div $" << reg << ", $" << destReg << std::endl;
    dst << "mflo $" << reg << std::endl;
    Var.reg = reg;

  }else{
    
    dst << "div $" << Var.reg << ", $" << destReg << std::endl;
    dst << "mflo $" << Var.reg << std::endl;
  }
}
 
