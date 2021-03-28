#include "ast/context.hpp"

// Register methods implementation
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

// Stack methods implementation
bool stackFrame::inFrame(std::string varName)
{
  auto it = varBindings.find(varName);
  return (it != varBindings.end());
}

// Overload for Debugging
std::ostream &operator<<(std::ostream &dst, stackFrame frame)
{
  dst << "Beginning of frame" << std::endl;
  dst << "offset = " << frame.offset << std::endl;
  // dst << "argSize = " << frame.argSize << std::endl;
  dst << "varBindings:" << std::endl;
  for(auto it = frame.varBindings.begin(); it != frame.varBindings.end(); it++){
    dst << "  " << it->first << ": size = " << it->second.size << ", offset = " << it->second.offset << std::endl;
  }
  dst << "startlabel: " << frame.startLabel << std::endl;
  dst << "endLabel: " << frame.endLabel << std::endl;
  dst << "End of frame" << std::endl;
  return dst;
}

// Context methods
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

bool Context::isEnum(std::string varName)
{
  auto it = enums.find(varName);
  return (it != enums.end());
}

void Context::enterScope()
{
  //std::cerr << "Entering scope" << std::endl; // Debugging
  assert(stack.size() > 0); // You should only enterScope within a function => at least 1 stackFrame
  stack.push_back(stack.back()); // Creates a copy of current scope (variables declared in function are available in sub-scope)
}

void Context::exitScope(std::ostream &dst)
{
  //std::cerr << "Exiting scope" << std::endl; // Debugging
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
  int diff = stack.back().offset + oldScope; // oldScope is -ve
  //std::cerr << "Previous stack: " << std::endl << stack.end()[-2]; // Debugging
  //std::cerr << "Current stack: " << std::endl << stack.back(); // Debugging
  if(diff > 0){
    dst << "addiu $29,$29," << diff << std::endl;
  }
  stack.pop_back(); // Leaves scope, re-enters previous scope
  //std::cerr << "Current stack == previous stack:" << std::endl << stack.back(); // Debugging
  // Restores registers from previous scope
  for(auto it = stack.back().varBindings.begin(); it != stack.back().varBindings.end(); it++){
    int reg = it->second.reg;
    if(reg != -1){
      dst << "lw $" << reg << "," << it->second.offset << "($30)" << std::endl;
    }
  }
}

int Context::allocate()
{
  // Allocates register
  int reg = regFile.allocate();
  if(reg != -1){
    return reg;
  }
  // If no registers are free, overwrites variable
  else{
    for(auto it = stack.back().varBindings.begin(); it != stack.back().varBindings.end(); it++){
      reg = it->second.reg;
      if(reg != -1){
        regFile.freeReg(reg);
        it->second.reg = -1;
        return reg;
      }
    }
  }
  // Hopefully this never happens lmao
  std::cerr << "Unable to free any registers" << std::endl;
  exit(1);
}

int Context::allocateFloat()
{
  int reg = floatRegs.allocate();
  if(reg != -1){
    return reg;
  }
  // Hopefully this never happens lmao
  std::cerr << "Unable to allocate any registers" << std::endl;
  exit(1);
}
