#include "ast/operators/binaryOps/ast_binarySub.hpp"

void BinarySub::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Subtraction [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinarySub::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  
  int regLeft = DoLeft(dst, context, destReg);
  int regRight = DoRight(dst, context, destReg, regLeft);

  EZPrint(dst, "sub", destReg, regLeft, regRight);
  std::cerr << "we got here" << std::endl;
  
  if( isPtrVar(context, RightOp()) ){
    dst << "sra $" << destReg << ", $" << destReg << ", 2" << std::endl;
  }

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}
 

void BinarySub::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, std::string type) const
{
  if(type == "_ptr"){
    int ptrcount = 0;
    if( isPtrVar(context, LeftOp()) ){
      ptrcount++;
      LeftOp()->generateMIPS(dst, context, destReg);
    }else{
      LeftOp()->generateMIPS(dst, context, destReg);
      dst << "sll $" << destReg << ", $" << destReg << ", 2" << std::endl;
    }

    int temp = context.allocate();
    if( isPtrVar(context, RightOp()) ){
      ptrcount++;
      RightOp()->generateMIPS(dst, context, temp);
    }else{
      RightOp()->generateMIPS(dst, context, temp);
      dst << "sll $" << temp << ", $" << temp << ", 2" << std::endl;
    }

    EZPrint(dst, "sub", destReg, destReg, temp);
    if( ptrcount > 1 ){
      dst << "sra $" << destReg << ", $" << destReg << ", 2" << std::endl;
    }
      context.regFile.freeReg(temp);

  }else{

    //whateber
  }

}

