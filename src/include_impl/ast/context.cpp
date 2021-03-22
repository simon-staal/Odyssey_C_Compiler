#include "ast/context.hpp"

bool stackFrame::inFrame(std::string varName)
{
  auto it = varBindings.find(varName);
  return (it != varBindings.end());
}

std::ostream &operator<<(std::ostream &dst, stackFrame frame)
{
  dst << "Beginning of frame" << std::endl;
  dst << "offset = " << frame.offset << std::endl;
  dst << "argSize = " << frame.argSize << std::endl;
  dst << "varBindings:" << std::endl;
  for(auto it = frame.varBindings.begin(); it != frame.varBindings.end(); it++){
    dst << "  " << it->first << ": size = " << it->second.size << ", offset = " << it->second.offset << std::endl;
  }
  dst << "End of frame" << std::endl;
  return dst;
}

void registers::useReg(int i) { usedRegs[i] = 1; }
void registers::freeReg(int i) { usedRegs[i] = 0; }


int registers::allocate()
{
  for(int i = 2; i < 26; i++){
    if(!usedRegs[i]){
      useReg(i);
      return i;
    }
  }
  return -1;
}

std::string Context::makeLabel(std::string label)
{
  static int count = 0;
  return "_"+label+"_"+std::to_string(count++);
}

bool Context::isGlobal(std::string varName)
{
  auto it = globals.find(varName);
  return (it != globals.end());
}


void Context::enterScope()
{
  assert(stack.size() > 0); // You should only enterScope within a function => at least 1 stackFrame
  stack.push_back(stack.back()); // Creates a copy of current scope (variables declared in function are available in sub-scope)
}

void Context::exitScope(std::ostream &dst)
{
  // Ensures changes to variable from previous scope are retained
  int oldScope = -(stack.end()[-2]).offset; // Any variable with an offset >= to this offset need to be stored
  for(auto it = stack.back().varBindings.begin(); it != stack.back().varBindings.end(); it++){
    if(it->second.offset >= oldScope){
      int reg = it->second.reg;
      // If variable is stored in a register write it back to offset to ensure it's preserved
      if(reg != -1){
        dst << "sw $" << reg << "," << it->second.offset << "($30)" << std::endl;
      }
    }
  }

  // Re-increments stack pointer to deallocate any variables no longer in scope
  int diff = stack.back().offset - oldScope;
  if(diff > 0){
    dst << "addiu $29,$29," << diff << std::endl;
  }
  stack.pop_back(); // Leaves scope, re-enters previous scope

  // Restores registers from previous scope
  for(auto it = stack.back().varBindings.begin(); it != stack.back().varBindings.end(); it++){
    int reg = it->second.reg;
    if(reg != -1){
      dst << "lw $" << reg << "," << it->second.offset << "($30)" << std::endl;
    }
  }
}


int Context::allocateFull()
{
  for(auto it = stack.back().varBindings.begin(); it != stack.back().varBindings.end(); it++){
    int reg = it->second.reg;
    if(reg != -1){
      regFile.freeReg(reg);
      it->second.reg = -1;
      return reg;
    }
  }
  std::cerr << "Unable to free any registers" << std::endl;
  exit(1);
  return -1;
}
/* Legacy code

void Context::storeReg(std::ostream &dst, int reg)
{
  dst << "addiu $29,$29,-4" << std::endl;
  dst << "sw $" << reg << ",0($29)" << std::endl;
  stack.back().offset += 4;
  regFile.freeReg(reg);
}

void Context::restoreReg(std::ostream &dst, int reg)
{
  dst << "lw $" << reg << ",0($29)" << std::endl;
  dst << "addiu $29,$29,4" << std::endl;
}

void Context::storeInStack(std::ostream &dst, int reg, int offset)
{
  dst << "sw $" << reg << "," << stackSize - offset << "($29)" << std::endl;
}

void Context::restoreFromStack(std::ostream &dst, int reg, int offset)
{
  dst << "lw $" << reg << "," << stackSize - offset << "($29)" << std::endl;
}

void Context::functionReturn(std::ostream &dst)
{
  dst << "lw $31," << stack.back().offset-4 << "($29)" << std::endl;
  dst << "lw $30," << stack.back().offset-8 << "($29)" << std::endl;
  dst << "jr $31" << std::endl;
  dst << "addiu $29,$29," << stack.back().offset << std::endl; // Delay slot op
}

void Context::functionAlloc(std::ostream &dst)
{
  dst << "move $30,$29" << std::endl;
}

void Context::functionCall(std::ostream &dst)
{
  stackFrame newFrame;
  stack.push_back(newFrame);
  dst << "addiu $29,$29,-8" << std::endl;
  dst << "sw $31" << stack.back().offset-4 << "($29)" << std::endl;
  dst << "sw $30," << stack.back().offset-8 << "($29)" << std::endl;
  // loads arguments
  for(int i = 4; i < 8; i++){
    if(regFile.usedRegs[i]){
      dst << "sw $" << i << "," << stack.back().offset+4*(i-4) << "($30)" << std::endl;
    }
  }
}

*/
