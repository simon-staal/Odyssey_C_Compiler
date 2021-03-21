#include "ast/ast_identifier.hpp"

// Constructor
Identifier::Identifier(std::string _id)
  : id(_id)
{}

// Getting identifier
std::string Identifier::getId() const
{
  if(branches.empty()) { return id; }
  else{ return branches[0]->getId(); }
}

// Visualising
void Identifier::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Identifier: " << id << std::endl;
}

void Identifier::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // only if declarator for variable
  // context.stack.back().varBindings[id] = {0, 0};
  std::string id = getId();
  variable tmp;

  if(destReg == -1){
    for(auto it = context.stack.back().varBindings.begin(); it != context.stack.back().varBindings.end(); it++){
      if (it->second.reg != -1){
        context.regFile.freeReg(it->second.reg); // This variable can still be accessed directly from memory
        destReg = it->second.reg;
        it->second.reg = -1; // Inidicate this variable is no longer available in register
      }
     }
    }

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    //variable doesnt exist in current frame !!
  }else{
    tmp = it->second;
  }

  if(tmp.reg == -1){
    dst << "lw $" << destReg << ", " << tmp.offset << "($30)" << std::endl;
  }else{
    dst << "move $" << destReg << ", $" << tmp.reg << std::endl;
  }

}
