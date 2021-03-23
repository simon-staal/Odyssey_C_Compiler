#include "ast/operators/binaryOps/ast_binaryORAss.hpp"

void BinaryORAss::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary ORAss [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+ "  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void BinaryORAss::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  variable Var = LeftVar(context);

  RightOp()->generateMIPS(dst, context, destReg);

  ifFunction(dst, context, destReg);


  if( Var.reg == -1){
    int reg = context.allocate();
    dst << "lw $" << reg << ", " << Var.offset << "($30)" << std::endl;
    EZPrint(dst, "or", reg, reg, destReg);
    Var.reg = reg;

  }else{

    EZPrint(dst, "or", Var.reg, Var.reg, destReg);
  }

}
 
