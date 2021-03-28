#include "ast/operators/unaryOps/ast_unaryPostInc.hpp"

void UnaryPostInc::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Post Inc [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  getOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void UnaryPostInc::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::string id = getOp()->getId();
  variable op;

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    std::cerr << "Inc a non var?" << std::endl;
  }else{
    op = it->second;
  }

  if( op.type == "_ptr" ){

    if(op.reg == -1){

      dst << "lw $" << destReg << ", " << op.offset << "($30)" << std::endl;
      dst << "addiu $" << destReg << ", $" << destReg << ", 4" << std::endl;
      dst << "sw $" << destReg << ", " << op.offset << "($30)" << std::endl;
      dst << "addiu $" << destReg << ", $" << destReg << ", -4" << std::endl;

    }else{

      dst << "addiu $" << op.reg << ", $" << op.reg << ", 4" << std::endl;
      dst << "sw $" << op.reg << ", " << op.offset << "($30)" << std::endl;
      dst << "addiu $" << destReg << ", $" << op.reg << ", -4" << std::endl;
    }

  }else{

    if(op.reg == -1){

      dst << "lw $" << destReg << ", " << op.offset << "($30)" << std::endl;
      dst << "addiu $" << destReg << ", $" << destReg << ", 1" << std::endl;
      dst << "sw $" << destReg << ", " << op.offset << "($30)" << std::endl;
      dst << "addiu $" << destReg << ", $" << destReg << ", -1" << std::endl;

    }else{

      dst << "addiu $" << op.reg << ", $" << op.reg << ", 1" << std::endl;
      dst << "sw $" << op.reg << ", " << op.offset << "($30)" << std::endl;
      dst << "addiu $" << destReg << ", $" << op.reg << ", -1" << std::endl;

    }
  }
}