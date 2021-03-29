#ifndef context_hpp
#define context_hpp

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <utility>

// Contains information related to where a variable exists in memory
struct variable;
// contains information related to size of arguments of a function
struct function;
// Represents current scope
struct stackFrame;
// Represents enumerations
struct enumeration;

// Regfile
struct registers
{
  int usedRegs[32] =
  { 1, // $0 = 0 [0]
    1, // $at = no touch [1]
    1, 1, // $v0-$v1, return value => changed by function calls so not suitable to evaluate temporaries [2-3]
    1, 1, 1, 1, // $a0-$a3, function arguments, just use them for that [4-7]
    0, 0, 0, 0, 0, 0, 0, 0, // $t0-$t7, temporary registers, do what you want [8-15]
    1, 1, 1, 1, 1, 1, 1, 1, // $s0-$s7, values preserved across function calls [16-23]
    0, 0, // $t8-$t9, more temporaries [24-25]
    1, 1, // $k0-$k1, kernel registers, no touchy [26-27]
    1, // $gp, used for static global variables (probs never use) [28]
    1, // $sp, stack pointer [29]
    1, // $fp, frame pointer [30]
    1}; // $ra, return address [31]

  void useReg(int i); // Register is now being used
  void freeReg(int i); // Register is no longer being used
  int allocate(); // Returns empty register, -1 if no registers are available (Helper function for context)
};

// Supported types
enum Specifier {
  _int,
  _void,
  _unsigned, // Not implemented yet
  _char, // Not implemented yet
  _float,
  _double,
  _ptr
};

struct Context
{
  // Stack stuff
  std::vector<stackFrame> stack;

  // Globals (pretty sure i should be using std::unordered_map for faster lookups but getting weird issues with the header)
  std::map<std::string, enum Specifier> globals; // Just needs to track the names + types of globals
  std::map<std::string, function> functions; // tracks the size of the arguments
  std::map<std::string, enumeration> enums; // Tracks enums globally
  // (this is technically wrong but i'm lazy - hopefully they don't test locally scoped enums)
  // Alternative would be to add it to the stack from and copy it whenever entering a funciton call
  // If i had more time this is probably what i'd do

  // MIPS Register file
  registers regFile;
  registers floatRegs = {{ // Special floating point reg file
    1, 1, // $f0-1 used for return of floats/doubles
    0, 1, // $f2-3 available
    0, 1, 0, 1, 0, 1, 0, 1, // $f4-$f11 temporaries, available
    0, 1, 0, 1, // $f12-$f15 used for arguments, stored in memory => available
    0, 1, 0, 1, // $f16-$f19 more temporaries, available
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 // $f20-$f30 saved registers, preserved across fn calls
  }};

  // Return a unique label for assembly code
  std::string makeLabel(std::string label);

  bool isGlobal(std::string varName); // Use to check which map to use for variables
  bool isEnum(std::string varName); // use to check which map to use for variables

  // Used to manage scope within a function (i.e. block structures - ifElse, while, for)
  void enterScope();
  void exitScope(std::ostream &dst);

  // Use this method for allocation
  // If all registers are being used, this will clear a register and return it
  int allocate();
  int allocateFloat();

};

struct variable
{
  unsigned int size; // How many bytes does the variable take up
  int offset; // Offset from frame pointer (+ for arguments, - for variables)
  int reg; // Keeps track of which register the variable is in (-1 := not stored in reg)
  enum Specifier type = Specifier::_int; // keeps track of type, int by default (refactor this to enum if possible at some point)
};

struct function
{
  unsigned int size; // Total size of arguments
  std::vector<unsigned int> argSize; // Individual size of each argument
};

struct enumeration
{
  std::string id; // Name of enum
  int value; // Value associated with enum
};

struct stackFrame
{
  std::map<std::string, variable> varBindings; // Tracks variables in scope
  unsigned int offset = 0; // Keeps track of size of frame to restore the stack pointer for blocks (i.e. while loops, if statements) -- MAKE SURE TO INCREMENT WHEN ALLOCATING VARIABLES
  bool inFrame(std::string varName); // Error checking, probably not necessary
  std::string startLabel; // Used for continue statement (and case stuff for switch)
  std::string endLabel; // Used for break statement
  enum Specifier returnType; // Used to track type being returned from function
};

std::ostream &operator<<(std::ostream &dst, stackFrame frame);

#endif
