#include "ast/operators/unaryOps/ast_unarySub.hpp"

void UnarySub::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Sub [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  getOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void UnarySub::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  getOp()->generateMIPS(dst, context, destReg);

  ifFunction(dst, context, destReg);

  dst << "sub $" << destReg << ", $0, $" << destReg << std::endl; 

}

void UnarySub::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  switch(type)
  {
    case _ptr:
    {
      std::cerr << "multiplying pointers are we?" << std::endl;
    }
    case _float:
    {

      getOp()->generateTypeMIPS(dst, context, destReg, type);
      if( getOp()-isFunction() ){
        dst << "mov.s $f" << destReg << ", $f0" << std::endl; 
      }

      dst << "neg.s $f" << destReg << ", $f" << destReg << std::endl;

      break;
    }
    
    case _double:
    {

      getOp()->generateTypeMIPS(dst, context, destReg, type);
      if( getOp()-isFunction() ){
        dst << "mov.d $f" << destReg << ", $f0" << std::endl; 
      }

      dst << "neg.d $f" << destReg << ", $f" << destReg << std::endl;


      break;

    }

  }
}
