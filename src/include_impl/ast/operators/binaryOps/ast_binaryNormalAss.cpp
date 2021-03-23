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

  if(destReg == -1){
    destReg = context.allocate();
  }


  std::string id = LeftOp()->getId();
  variable left;

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    std::cerr << "Uninitialised Variable?" << std::endl;
  }else{
    left = it->second;
  }


  int regRight;
  if( ((regRight = context.regFile.allocate()) == -1) ){
    std::cerr << "OOPSIES NO REGS ARE FREE. OVERWRITING" << std::endl;
  }

  RightOp()->generateMIPS(dst, context, regRight);

  dst << "sw $" << regRight << ", "<< left.offset << "($30)" << std::endl; // Stores result in variable

  if(left.reg == -1){
    //not stored in registers
  }else{
    dst << "move $" << left.reg << ", $" << regRight << std::endl;
  }

  context.regFile.freeReg(regRight);

}
