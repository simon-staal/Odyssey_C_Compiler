#include "ast/context.hpp"

bool stackFrame::inFrame(std::string varName)
{
  auto it = varBindings.find(varName);
  return (it != varBindings.end());
}

register::allocate()
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

void Context::storeReg(std::ostream &dst, int reg)
{
  dst << "addiu $29,$29,-4" << std::endl;
  dst << "sw $" << reg << ",0($29)" << std::endl;
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
