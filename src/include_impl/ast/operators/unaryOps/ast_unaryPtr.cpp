#include "ast/operators/unaryOps/ast_unaryPtr.hpp"

void UnaryPtr::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Ptr [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  getOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void UnaryPtr::generateMIPS(std::ostream &dst, Context &context, int destReg) const // only for dereferencing.
{
  //find variable you are *ing
  std::string id = getOp()->getId();
  variable var;

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    std::cerr << "Uninitialised Variable?" << std::endl;
  }else{
    var = it->second;
  }

  getOp()->generateMIPS(dst, context, destReg); // puts ptr value (its pointed address) into destReg like any other variable
  dst << "lw $" << destReg << ", 0($" << destReg << ")" << std::endl; // loads whatever its pointing at.

}

bool UnaryPtr::isPtr() const 
{
  return true;
}


void UnaryPtr::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const // only for dereferencing.
{

    switch(type)
  {

      case _float:
      {
        //find variable you are *ing
        std::string id = getOp()->getId();
        variable var;

        auto it = context.stack.back().varBindings.find(id);
        if( it == context.stack.back().varBindings.end() ){
          std::cerr << "Uninitialised Variable?" << std::endl;
        }else{
         var = it->second;
        }

        int reg = context.allocate();
        getOp()->generateMIPS(dst, context, reg); // puts ptr value (its pointed address) into destReg like any other variable
        dst << "lwc1 $f" << destReg << ", 0($" << reg << ")" << std::endl; // loads whatever its pointing at.
        context.regFile.freeReg(reg);

        break;
      }

      case _double:
      {
        //find variable you are *ing
        std::string id = getOp()->getId();
        variable var;

        auto it = context.stack.back().varBindings.find(id);
        if( it == context.stack.back().varBindings.end() ){
          std::cerr << "Uninitialised Variable?" << std::endl;
        }else{
         var = it->second;
        }

        int reg = context.allocate();
        getOp()->generateMIPS(dst, context, reg); // puts ptr value (its pointed address) into destReg like any other variable
        dst << "ldc1 $f" << destReg << ", 0($" << reg << ")" << std::endl; // loads whatever its pointing at.
        context.regFile.freeReg(reg);

        break;
      }


  }

}