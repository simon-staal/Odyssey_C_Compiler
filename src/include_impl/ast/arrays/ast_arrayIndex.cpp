#include "ast/arrays/ast_arrayIndex.hpp"

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
    variable array;
    auto it = context.stack.back().varBindings.find(id);
    if( it == context.stack.back().varBindings.end() ){
    std::cerr << "Uninitialised Variable?" << std::endl;
    }else{
        array = it->second;
    }

    branches[1]->generateMIPS(dst, context, destReg);

    int reg = context.allocate();

    dst << "addiu $" << reg << ", $0, " << array.size << std::endl;
    dst << "mult $" << destReg << ", $" << reg << std::endl;
    dst << "mflo $" << destReg << std::endl;
    dst << "addiu $" << destReg << ", $" << destReg << ", " << array.offset << std::endl;
    dst << "move $" << reg << ", $30" << std::endl;
    dst << "add $" << destReg << ", $" << destReg << ", $" << reg << std::endl;
    dst << "lw $" << destReg << ", 0($" << destReg << ")" << std::endl;


    context.regFile.freeReg(reg);
}


std::string ArrayIndex::getId() const
{
  return branches[0]->getId();
}

bool ArrayIndex::isFunction() const
{
  return false;
}
