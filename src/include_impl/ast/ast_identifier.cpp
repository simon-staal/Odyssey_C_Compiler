#include "ast/ast_identifier.hpp"

// Constructor
Identifier::Identifier(std::string _id)
  : id(_id)
{}

// Visualising
void Identifier::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Identifier: " << id << std::endl;
}

// Codegen
void Identifier::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // Only used if identifier for variable, used in evaluation
  std::string id = getId();
  variable tmp;

  // Finds variable
  if(context.isGlobal(id)){
    // Load global address
    dst << "lui $" << destReg << ",%hi(" << id << ")" << std::endl;
    dst << "addiu $" << destReg << ",$" << destReg << ",%lo(" << id << ")" << std::endl;
    // Load value into destReg
    dst << "lw $" << destReg << ",0($" << destReg << ")" << std::endl;
    dst << "nop" << std::endl; // Idk if this is needed but godbolt has it and i'm not taking chances

  }
  else if(context.isEnum(id)){
    dst << "li $" << destReg << "," << context.enums[id].value << std::endl;
  }
  else{
    auto it = context.stack.back().varBindings.find(id);
    if( it == context.stack.back().varBindings.end() ){
      //variable doesnt exist in current frame !! -> handle globals later
      std::cerr << "Code is invalid lmao)" << std::endl;
      exit(1);
    }else{
      tmp = it->second;
    }

    // Puts variable in destReg
    if(tmp.reg == -1){
      dst << "lw $" << destReg << ", " << tmp.offset << "($30)" << std::endl;
    }else{
      dst << "move $" << destReg << ", $" << tmp.reg << std::endl;
    }
  }
}

void Identifier::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  std::string id = getId();
  variable tmp;

  // All this stuff is needed because we might (and probably will) call generateTypeMIPS recursively on a regular identifier
  // Finds variable
  if(context.isGlobal(id)){
    int reg = context.allocate(); // destReg is a floating point register
    switch(context.globals[id])
    {
      case _float:
        dst << "lui $" << reg << ",%hi(" << id << ")" << std::endl;
        dst << "addiu $" << reg << ",$" << reg << ",%lo(" << id << ")" << std::endl;
        dst << "l.s $f" << destReg << ",0($" << reg << ")" << std::endl;
        break;
      case _double:
        dst << "lui $" << reg << ",%hi(" << id << ")" << std::endl;
        dst << "addiu $" << reg << ",$" << reg << ",%lo(" << id << ")" << std::endl;
        dst << "l.d $f" << destReg << ",0($" << reg << ")" << std::endl;
        break;
      default:
        // Load global address
        dst << "lui $" << destReg << ",%hi(" << id << ")" << std::endl;
        dst << "addiu $" << destReg << ",$" << destReg << ",%lo(" << id << ")" << std::endl;
        // Load value into destReg
        dst << "lw $" << destReg << ",0($" << destReg << ")" << std::endl;
    }

  }
  else if(context.isEnum(id)){
    dst << "li $" << destReg << "," << context.enums[id].value << std::endl;
  }
  else{
    auto it = context.stack.back().varBindings.find(id);
    if( it == context.stack.back().varBindings.end() ){
      //variable doesnt exist in current frame !! -> handle globals later
      std::cerr << "Code is invalid lmao)" << std::endl;
      exit(1);
    }else{
      tmp = it->second;
    }
    switch(type)
    {
      case _float:
        dst << "l.s $f" << destReg << ", " << tmp.offset << "($30)" << std::endl;
        break;
      case _double:
        dst << "l.d $f" << destReg << ", " << tmp.offset << "($30)" << std::endl;
        break;
      default:
        if(tmp.reg == -1){
          dst << "lw $" << destReg << ", " << tmp.offset << "($30)" << std::endl;
        }else{
          dst << "move $" << destReg << ", $" << tmp.reg << std::endl;
        }
    }
  }
}

// Getting identifier (codegen helper)
std::string Identifier::getId() const
{
  if(branches.empty()) { return id; }
  else{ return branches[0]->getId(); }
}

int Identifier::getSize(Context &context) const
{
  if(context.isGlobal(id)){
    // TODO: Add some shit to globals
    std::cerr << "SizeOf globals not implemented" << std::endl;
    return 0;
  }
  else{
    auto it = context.stack.back().varBindings.find(id);
    if(it == context.stack.back().varBindings.end()){
      std:: cerr << "Variable not found" << std::endl;
      exit(1);
    }
    return it->second.size;
  }
}
