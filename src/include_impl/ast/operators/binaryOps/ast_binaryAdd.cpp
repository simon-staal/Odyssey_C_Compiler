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
  // std::cerr << "Hello :D" << std::endl; (I couldn't remove him ;( )
  int regLeft = DoLeft(dst, context, destReg);
  int regRight = DoRight(dst, context, destReg, regLeft);

  EZPrint(dst, "add", destReg, regLeft, regRight);

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}

void BinaryAdd::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  switch(type)
  {
    case _ptr:
    {
      if( isPtrVar(context, LeftOp()) ){
        LeftOp()->generateMIPS(dst, context, destReg);
      }else{
        LeftOp()->generateMIPS(dst, context, destReg);
        dst << "sll $" << destReg << ", $" << destReg << ", 2" << std::endl;
      }

      int temp = context.allocate();
      if( isPtrVar(context, RightOp()) ){
        RightOp()->generateMIPS(dst, context, temp);
      }else{
        RightOp()->generateMIPS(dst, context, temp);
        dst << "sll $" << temp << ", $" << temp << ", 2" << std::endl;
      }
        EZPrint(dst, "add", destReg, destReg, temp);
        context.regFile.freeReg(temp);
      break;
    }
    case _float:
    {
      int regLeft = DoTypeLeft(dst, context, 2, type);
      int regRight = DoTypeRight(dst, context, 4, type);

      dst << "add.s $f0, $f2, $f4" << std::endl;

      break;
    }

  }
}
