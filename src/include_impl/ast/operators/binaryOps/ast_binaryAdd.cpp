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

  int regLeft = DoLeft(dst, context, destReg);
  int regRight = DoRight(dst, context, destReg, regLeft);

  EZPrint(dst, "add", destReg, regLeft, regRight);

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}

void BinaryAdd::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, std::string type) const
{
  if(type == "_ptr"){  
    if( isPointer(context, LeftOp()) ){
      generateMIPS(dst, context, destReg);
    }else{
      generateMIPS(dst, context, destReg);
      dst << "sll $" << destReg << ", $" << destReg << ", 2" << std::endl;
    }

    int temp = context.allocate();
    if( isPointer(context, RightOp()) ){
      generateMIPS(dst, context, temp);
    }else{
      generateMIPS(dst, context, temp);
      dst << "sll $" << temp << ", $" << temp << ", 2" << std::endl;
    }
      EZPrint(dst, "add", destReg, destReg, temp);
      context.regFile.freeReg(temp);

  }else{

    //whateber
  }

}
