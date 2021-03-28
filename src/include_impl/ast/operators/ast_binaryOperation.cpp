#include "ast/operators/ast_binaryOperation.hpp"

BinaryOperation::BinaryOperation(NodePtr left, NodePtr right)
{
    branches.push_back(left);
    branches.push_back(right);
}

BinaryOperation::~BinaryOperation()
{
    delete branches[0];
    delete branches[1];
}

NodePtr BinaryOperation::LeftOp() const
{
    return branches[0];
}

NodePtr BinaryOperation::RightOp() const
{
    return branches[1];
}

void BinaryOperation::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::cerr << "Binary shit doesn't yet Kai you lazy fuck" << std::endl;
}

void BinaryOperation::EZPrint(std::ostream &dst, std::string instr, int destReg, int regLeft, int regRight) const
{
    dst << instr << " $" << destReg << ", $" << regLeft << ", $" << regRight << std::endl;
}

int BinaryOperation::DoLeft(std::ostream &dst, Context &context, int destReg) const
{

  // Process left operand
  LeftOp()->generateMIPS(dst, context, destReg);
  int regLeft = context.allocate();
  if(LeftOp()->isFunction()){
    dst << "move $" << regLeft << ",$2" << std::endl;
  }else{
    dst << "move $" << regLeft << ", $" << destReg << std::endl;
  }

    return regLeft;

}

int BinaryOperation::DoRight(std::ostream &dst, Context &context, int destReg, int regLeft) const
{

  // Process right operand
  if(RightOp()->isFunction()){ // Preserve leftop across function call
    // Preserves $s0
    dst << "addiu $29,$29,-4" << std::endl;
    context.stack.back().offset += 4;
    context.stack.back().varBindings["$s0"] = {4, -context.stack.back().offset, -1};
    dst << "sw $s0,0($29)" << std::endl;
    // Move leftOp into $s0 to be preserved
    dst << "move $s0,$" << regLeft << std::endl;
  }

  RightOp()->generateMIPS(dst, context, destReg);
  int regRight = context.allocate();
  if(RightOp()->isFunction()){
    // Restore regleft
    dst << "move $" << regLeft << ", $s0" << std::endl;
    // Restore $s0
    dst << "lw $s0," << context.stack.back().varBindings["$s0"].offset << "($30)" << std::endl;
    dst << "move $" << regRight << ",$2" << std::endl;
  }else{
    dst << "move $" << regRight << ", $" << destReg << std::endl;
  }

    return regRight;

}

variable BinaryOperation::LeftVar(Context &context) const
{

  std::string id = LeftOp()->getId();
  variable left;

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    std::cerr << "Uninitialised Variable?" << std::endl;
  }else{
    left = it->second;
  }

  return left;

}

void BinaryOperation::ifFunction(std::ostream &dst, Context &context, int destReg) const
{
    if(RightOp()->isFunction()){
        dst << "move $" << destReg << ", $2" << std::endl;

    }
}

void BinaryOperation::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  std::cerr << "shouldnt be used??" << std::endl;
}

bool BinaryOperation::isPtrVar(Context &context, NodePtr op) const
{
      std::string id = op->getId();
      variable var;
      if( !(op->isFunction()) ){

        if( id != "<NULL>" ){
          auto it = context.stack.back().varBindings.find(id);
          if( it == context.stack.back().varBindings.end() ){
            std::cerr << "Uninitialised Variable?" << std::endl;
          }else{
            var = it->second;
          }

          if(var.type == Specifier::_ptr){
            return true;
          }
        }
      }
      return false;
}

int BinaryOperation::DoTypeLeft(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  switch(type)
  {
    case _float:
    {
      if(LeftOp()->isFunction()){

        LeftOp()->generateMIPS(dst, context, destReg);
        dst << "mov.s $f0, $f6" << std::endl;

      }else{

        LeftOp()->generateTypeMIPS(dst, context, destReg, type);
        dst << "mov.s $f6, $f" << destReg << std::endl;
      }

      return 2;
    }

    case _double:
    {

      if(LeftOp()->isFunction()){

        LeftOp()->generateMIPS(dst, context, destReg);
        dst << "mov.d $f0, $f6" << std::endl;

      }else{

        LeftOp()->generateTypeMIPS(dst, context, destReg, type);
        dst << "mov.d $f6, $f" << destReg << std::endl;
      }

      return 2;
    }

  }
}

int BinaryOperation::DoTypeRight(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  switch(type)
  {

    case _float:
    {
      if(RightOp()->isFunction()){

        dst << "addiu $29,$29,-4" << std::endl;
        context.stack.back().offset += 4;
        context.stack.back().varBindings["$f20"] = {4, -context.stack.back().offset, -1};
        dst << "swc1 $f20,0($29)" << std::endl;

        dst << "mov.s $f20, $f6" << std::endl; // save left result into preserved register

        RightOp()->generateMIPS(dst, context, destReg);
        dst << "mov.s $f6, $f20" << std::endl; // restore register
        dst << "lwc1 $f20," << context.stack.back().varBindings["$f20"].offset << "($30)" << std::endl; //restore saved register

      }else{

        RightOp()->generateTypeMIPS(dst, context, destReg, type);
        dst << "mov.s $f8, $f" << destReg << std::endl;
      }

      return 4;
    }

    case _double:
    {
      if(RightOp()->isFunction()){

        dst << "addiu $29,$29,-8" << std::endl;
        context.stack.back().offset += 8;
        context.stack.back().varBindings["$f20"] = {8, -context.stack.back().offset, -1};
        dst << "sdc1 $f20,0($29)" << std::endl;

        dst << "mov.d $f20, $f6" << std::endl; // save left result into preserved register

        RightOp()->generateMIPS(dst, context, destReg);
        dst << "mov.d $f6, $f20" << std::endl; // restore register
        dst << "ldc1 $f20," << context.stack.back().varBindings["$f20"].offset << "($30)" << std::endl; //restore saved register

      }else{

        RightOp()->generateTypeMIPS(dst, context, destReg, type);
        dst << "mov.d $f8, $f" << destReg << std::endl;
      }

      return 4;
    }

  }

}