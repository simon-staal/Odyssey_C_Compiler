#ifndef context_hpp
#define context_hpp

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>

// Contains information related to memory
struct variable;
struct function;
// Duh
struct stackFrame;
// Regfile
struct registers
{
  int usedRegs[32] = {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1};
  void useReg(int i);
  void freeReg(int i);
  int allocate();
};

struct Context
{
  // Stack stuff
  std::vector<stackFrame> stack;

  // Globals
  std::map<std::string, variable> globals;

  // MIPS Register file
  registers regFile;

  // Return a unique label for assembly code
  std::string makeLabel(std::string label);

  bool isGlobal(std::string varName);

  // Read / write variables between memory (stack) and register
  // Manually increments / decrements sp
  void storeReg(std::ostream &dst, int reg);
  void restoreReg(std::ostream &dst, int reg);

  // Read / wrtie variables between memory (stack) and register
  // from a specified index (requires stack to be already allocated)
  /*
  void storeInStack(std::ostream &dst, int reg, int offset);
  void restoreFromStack(std::ostream &dst, int reg, int offset);
  */

  // sp, fp and ra management for a function return - requires more work for leaf functions
  void functionReturn(std::ostream &dst);
  // Manages stack stuff for entering new function call
  void functionAlloc(std::ostream &dst);

  void functionCall(std::ostream &dst);
  //std::string regName(int i);
};

struct variable
{
  unsigned int size;
  int offset;
};

struct function
{
  unsigned int param_size;
  unsigned int return_size;
  unsigned int offset;
};

struct stackFrame
{
  std::map<std::string, variable> varBindings;
  unsigned int offset = 8;
  int argSize = 16; // Space for arguments of subroutine call -- EXTEND LATER
  bool inFrame(std::string varName);
};



#endif
