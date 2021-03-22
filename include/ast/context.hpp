#ifndef context_hpp
#define context_hpp

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>

// Contains information related to where a variable exists in memory
struct variable;
// Represents current scope
struct stackFrame;
// Regfile
struct registers
{
  int usedRegs[32] = {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1};
  void useReg(int i); // Register is now being used
  void freeReg(int i); // Register is no longer being used
  int allocate(); // Returns empty register, -1 if no registers are available
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

  bool isGlobal(std::string varName); // Use to check which map to use

  // Used to manage scope within a function (i.e. block structures - ifElse, while, for)
  void enterScope();
  void exitScope(std::ostream &dst);

  // If all registers are being used, this will clear a register and return it
  int allocateFull();

  /* Legacy code -- Remove once i'm sure it's useless
  // Read / write variables between memory (stack) and register
  // Manually increments / decrements sp
  void storeReg(std::ostream &dst, int reg);
  void restoreReg(std::ostream &dst, int reg);

  // Read / wrtie variables between memory (stack) and register
  // from a specified index (requires stack to be already allocated)

  void storeInStack(std::ostream &dst, int reg, int offset);
  void restoreFromStack(std::ostream &dst, int reg, int offset);

  // sp, fp and ra management for a function return - requires more work for leaf functions
  void functionReturn(std::ostream &dst);
  // Manages stack stuff for entering new function call
  void functionAlloc(std::ostream &dst);

  void functionCall(std::ostream &dst);
  */
};

struct variable
{
  unsigned int size; // How many bytes does the variable take up
  int offset; // Offset from frame pointer (+ for arguments, - for variables)
  int reg; // Keeps track of which register the variable is in (-1 := not stored in reg)
};

struct stackFrame
{
  std::map<std::string, variable> varBindings; // Tracks variables in scope
  unsigned int offset = 0; // Keeps track of size of frame to restore the stack pointer for blocks (i.e. while loops, if statements) -- MAKE SURE TO INCREMENT WHEN ALLOCATING VARIABLES
  int argSize = 16; // Space for arguments of subroutine call -- Extend for function with no arguments (optional optimisation)
  bool inFrame(std::string varName); // Error checking, probably not necessary
};

std::ostream &operator<<(std::ostream &dst, stackFrame frame);

#endif
