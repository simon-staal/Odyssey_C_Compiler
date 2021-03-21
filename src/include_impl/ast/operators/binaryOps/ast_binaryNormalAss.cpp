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
    for(auto it = context.stack.back().varBindings.begin(); it != context.stack.back().varBindings.end(); it++){
      if (it->second.reg != -1){
        context.regFile.freeReg(it->second.reg); // This variable can still be accessed directly from memory
        destReg = it->second.reg;
        it->second.reg = -1; // Inidicate this variable is no longer available in register
      }
     }
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
