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

  if(destReg == -1){
    for(auto it = context.stack.back().varBindings.begin(); it != context.stack.back().varBindings.end(); it++){
      if (it->second.reg != -1){
        context.regFile.freeReg(it->second.reg); // This variable can still be accessed directly from memory
        destReg = it->second.reg;
        it->second.reg = -1; // Inidicate this variable is no longer available in register
      }
     }
    }


  std::string id = RightOp()->getId();
  variable left;

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    dst << "Uninitialised Variable?" << std::endl;
  }else{
    left = it->second;
  }

  if(left.reg == -1){
    dst << "lw $" << destReg << ", " << left.offset << "($30)" << std::endl;
  }else{
    dst << "move $" << destReg << ", $" << left.reg << std::endl;
  }

  int regRight;
  if( ((regRight = context.regFile.allocate()) == -1) ){
    dst << "OOPSIES NO REGS ARE FREE. OVERWRITING" << std::endl;
  }

  RightOp()->generateMIPS(dst, context, regRight);

  dst << "move $" << destReg << ", $" << regRight << std::endl;


  context.regFile.freeReg(regRight);
}
 
