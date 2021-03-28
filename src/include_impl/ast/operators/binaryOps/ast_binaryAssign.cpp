#include "ast/operators/binaryOps/ast_binaryAssign.hpp"
#include <cmath> // For array stuff

void BinaryAssign::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Assign [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+ "  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void BinaryAssign::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  NodePtr Index;
  std::string id = LeftOp()->getId();
  variable Var = LeftVar(context);

  if( LeftOp()->isPtr() ){  // if it has *p on the left hand side
    NodePtr assigned = RightOp()->getNode(1);
    if( assigned != NULL ){

      RightOp()->generateTypeMIPS(dst, context, destReg, Specifier::_ptr);

    }else{
      RightOp()->generateMIPS(dst, context, destReg);
    }

    int address = context.allocate();
    LeftOp()->getOp()->generateMIPS(dst, context, address);

    dst << "sw $" << destReg << ", 0($" << address << ")" << std::endl;

    context.regFile.freeReg(address);

  }else if( Var.type == Specifier::_ptr ){ // if it has p with type pointer on the left hand side

    NodePtr assigned = RightOp()->getNode(1); // checks if its just gonna be equal to &x e.g or any ptr arithmetic stuff
    if( assigned != NULL ){
      //std::cerr << "This is where the fun begins" << std::endl;
      RightOp()->generateTypeMIPS(dst, context, destReg, Specifier::_ptr);
      //std::cerr << "This is where the fun ends" << std::endl;
    }else{
      RightOp()->generateMIPS(dst, context, destReg);
    }

    dst << "sw $" << destReg << ", " << Var.offset << "($30)" << std::endl;

    if(Var.reg == -1){
      //not stored in registers
    }else{
      dst << "move $" << Var.reg << ", $" << destReg << std::endl;
    }

  }

  else{
    int reg = context.allocate(); // Allocates temporary GPR for processing
    if((Index = LeftOp()->getNode(1)) != NULL ){ // THEN ITS AN ARRAY
      int offset = reg;
      Index->generateMIPS(dst, context, offset);

      if(context.isGlobal(id)){
        // Scales offset
        dst << "sll $" << offset << ",$" << offset << ",2" << std::endl; // Will need to extend if we do doubles/longs

        // Load global address
        dst << "lui $" << destReg << ",%hi(" << id << ")" << std::endl;
        dst << "addiu $" << destReg << ",$" << destReg << ",%lo(" << id << ")" << std::endl;

        // Loads array element
        dst << "addu $" << destReg << ",$" << offset << ",$" << destReg << std::endl;
      }

      else{
        variable Var = LeftVar(context);
        // Scales offset
        dst << "addiu $" << destReg << ", $0, " << (int)log2(Var.size) << std::endl;
        dst << "sll $" << offset << ", $" << offset << ",$" << destReg << std::endl;

        // Load start of array
        dst << "addiu $" << destReg << ",$30," << Var.offset << std::endl;
        dst << "addu $" << destReg << ", $" << destReg << ", $" << offset << std::endl;
      }

      RightOp()->generateMIPS(dst, context, reg);
      dst << "sw $" << reg << ", 0($" << destReg << ")" << std::endl;
      dst << "move $" << destReg << ", $" << reg << std::endl; // Could switch registers to be more efficient but CBA

    }else{
      switch(Var.type)
      {
        case _float:
          RightOp()->generateTypeMIPS(dst, context, 0, Var.type); // generated into $f0 (same if function call)
          dst << "mfc1 $" << destReg << ", $f0" << std::endl;
          dst << "s.s $f0, " << Var.offset << "($30)" << std::endl; // Stores result in variable
          if(Var.reg != -1){
            dst << "move $" << Var.reg << ", $" << destReg << std::endl;
          }
          break;
        case _double: // Double vars not stored in registers
          RightOp()->generateTypeMIPS(dst, context, 0, Var.type); // generated into $f0
          dst << "s.d $f0, " << Var.offset << "($30)" << std::endl;
          break;
        default:
          RightOp()->generateMIPS(dst, context, destReg);
          ifFunction(dst, context, destReg);

          if(context.isGlobal(id)){
            int address = reg; // Temporary register
            dst << "lui $" << address << ",%hi(" << id << ")" << std::endl;
            dst << "addiu $" << address << ",$" << address << ",%lo(" << id << ")" << std::endl;
            dst << "sw $" << destReg << ",0($" << address << ")" << std::endl;
          }
          else{
            variable Var = LeftVar(context);
            dst << "sw $" << destReg << ", "<< Var.offset << "($30)" << std::endl; // Stores result in variable
            if(Var.reg != -1){ // Update register var is stored in
              dst << "move $" << Var.reg << ", $" << destReg << std::endl;
            }
          }
      }
    }
    context.regFile.freeReg(reg);
  }
}

void BinaryAssign::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{

}
