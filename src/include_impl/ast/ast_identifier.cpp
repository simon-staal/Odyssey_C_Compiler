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
