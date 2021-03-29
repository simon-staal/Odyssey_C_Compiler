#include "ast/arrays/ast_arrayIndex.hpp"
#include <cmath> // Required for shift stuff

// Constructors
ArrayIndex::ArrayIndex(NodePtr id, NodePtr index)
{
  branches.push_back(id);
  branches.push_back(index);
}

// Destructor
ArrayIndex::~ArrayIndex()
{
  delete branches[0];
  delete branches[1];
}

// Visualising
void ArrayIndex::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Array Index [" << std::endl;
  dst << indent << "Identifier: " << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "Index: " << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

// Codegen + helpers
void ArrayIndex::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
    std::string id = branches[0]->getId();
    int offset = context.allocate(); // Offset from start of array
    branches[1]->generateMIPS(dst, context, offset);

    variable array;
    auto it = context.stack.back().varBindings.find(id);
    if( it == context.stack.back().varBindings.end() ){
      std::cerr << "Uninitialised Variable?" << std::endl;
    }else{
      array = it->second;
    }

    if( array.type == _ptr ){

    dst << "sll $" << offset << ",$" << offset << ", 2" << std::endl; // Will need to extend if we do doubles/longs
    dst << "lw $" << destReg << ", " << array.offset << "($30)" << std::endl;
    dst << "add $" << destReg << ", $" << destReg << ", $" << offset << std::endl;
    dst << "lw $" << destReg << ", 0($" << destReg << ")" << std::endl;

    context.regFile.freeReg(offset);


    }else{

    if(context.isGlobal(id)){
      // Scales offset
      dst << "sll $" << offset << ",$" << offset << ",2" << std::endl; // Will need to extend if we do doubles/longs

      // Load global address
      dst << "lui $" << destReg << ",%hi(" << id << ")" << std::endl;
      dst << "addiu $" << destReg << ",$" << destReg << ",%lo(" << id << ")" << std::endl;

      // Loads array element
      dst << "addu $" << destReg << ",$" << offset << ",$" << destReg << std::endl;

      // Load value into destReg
      dst << "lw $" << destReg << ",0($" << destReg << ")" << std::endl;
      dst << "nop" << std::endl; // Idk if this is needed but godbolt has it
    }
    else{

      // Scales offset
      dst << "addiu $" << destReg << ", $0, " << (int)log2(array.size) << std::endl;
      dst << "sll $" << offset << ", $" << offset << ",$" << destReg << std::endl;

      // Load start of array
      dst << "addiu $" << destReg << ",$30," << array.offset << std::endl;
      dst << "addu $" << destReg << ", $" << destReg << ", $" << offset << std::endl;
      dst << "lw $" << destReg << ", 0($" << destReg << ")" << std::endl;
    }
    // Frees temporary register
    context.regFile.freeReg(offset);

    }
}


std::string ArrayIndex::getId() const
{
  return branches[0]->getId();
}

bool ArrayIndex::isFunction() const
{
  return false;
}


// Codegen + helpers
void ArrayIndex::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{

    std::string id = branches[0]->getId();
    int offset = context.allocate(); // Offset from start of array
    branches[1]->generateMIPS(dst, context, offset);

    variable array;
    auto it = context.stack.back().varBindings.find(id);
    if( it == context.stack.back().varBindings.end() ){
      std::cerr << "Uninitialised Variable?" << std::endl;
    }else{
      array = it->second;
    }

  switch(type)
  {

    case _ptr:
    {

      dst << "sll $" << offset << ",$" << offset << ", 2" << std::endl; // Will need to extend if we do doubles/longs
      dst << "lw $" << destReg << ", " << array.offset << "($30)" << std::endl;
      dst << "add $" << destReg << ", $" << destReg << ", $" << offset << std::endl;
      dst << "lwc1 $f" << destReg << ", 0($" << destReg << ")" << std::endl;

      
    }

    case _float:

    {
      if(context.isGlobal(id)){
        // Scales offset
        dst << "sll $" << offset << ",$" << offset << ",2" << std::endl; // Will need to extend if we do doubles/longs

        // Load global address
        dst << "lui $" << destReg << ",%hi(" << id << ")" << std::endl;
        dst << "addiu $" << destReg << ",$" << destReg << ",%lo(" << id << ")" << std::endl;

        // Loads array element
        dst << "addu $" << destReg << ",$" << offset << ",$" << destReg << std::endl;

        // Load value into destReg
        dst << "lwc1 $f" << destReg << ",0($" << destReg << ")" << std::endl;
        dst << "nop" << std::endl; // Idk if this is needed but godbolt has it
      }
      else{

        // Scales offset
        dst << "addiu $" << destReg << ", $0, " << (int)log2(array.size) << std::endl;
        dst << "sll $" << offset << ", $" << offset << ",$" << destReg << std::endl;

        // Load start of array
        dst << "addiu $" << destReg << ",$30," << array.offset << std::endl;
        dst << "addu $" << destReg << ", $" << destReg << ", $" << offset << std::endl;
        dst << "lwc1 $f" << destReg << ", 0($" << destReg << ")" << std::endl;
      }
    }

    case _double:
    {

      if(context.isGlobal(id)){
        // Scales offset
        dst << "sll $" << offset << ",$" << offset << ",2" << std::endl; // Will need to extend if we do doubles/longs

        // Load global address
        dst << "lui $" << destReg << ",%hi(" << id << ")" << std::endl;
        dst << "addiu $" << destReg << ",$" << destReg << ",%lo(" << id << ")" << std::endl;

        // Loads array element
        dst << "addu $" << destReg << ",$" << offset << ",$" << destReg << std::endl;

        // Load value into destReg
        dst << "ldc1 $f" << destReg << ",0($" << destReg << ")" << std::endl;
        dst << "nop" << std::endl; // Idk if this is needed but godbolt has it
      }
      else{

        // Scales offset
        dst << "addiu $" << destReg << ", $0, " << (int)log2(array.size) << std::endl;
        dst << "sll $" << offset << ", $" << offset << ",$" << destReg << std::endl;

        // Load start of array
        dst << "addiu $" << destReg << ",$30," << array.offset << std::endl;
        dst << "addu $" << destReg << ", $" << destReg << ", $" << offset << std::endl;
        dst << "ldc1 $f" << destReg << ", 0($" << destReg << ")" << std::endl;
      }

    }

  }

  context.regFile.freeReg(offset);
}