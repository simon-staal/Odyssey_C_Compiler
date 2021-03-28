#include "ast/functions/ast_functionDeclarator.hpp"

// Constructors
FunctionDeclarator::FunctionDeclarator(NodePtr id, NodeListPtr params)
{
  branches.push_back(id);
  branches.push_back(params);
}

FunctionDeclarator::FunctionDeclarator(NodePtr id, std::vector<NodePtr> params)
  : FunctionDeclarator(id, new NodeList(params))
{}

FunctionDeclarator::FunctionDeclarator(NodePtr id)
  : FunctionDeclarator(id, new NodeList())
{}

// Destructor
FunctionDeclarator::~FunctionDeclarator()
{
  delete branches[0];
  delete branches[1];
}

// Visualising
void FunctionDeclarator::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Function Declarator [" << std::endl;
  dst << indent << "Identifier: " << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "Parameters: " << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

// Codegen + helpers
void FunctionDeclarator::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::string id = branches[0]->getId();
  // Macro, required for linking or something
  dst << ".globl " << id << std::endl;
  // Function label
  dst << id << ":" << std::endl;
  // Storing ra and fp, updating frame pointer
  dst << "addiu $29,$29,-8" << std::endl;
  dst << "sw $30,0($29)" << std::endl;
  dst << "sw $31,4($29)" << std::endl;
  dst << "move $30,$29" << std::endl;

  // Process params
  stackFrame newFrame;
  int paramSize = 0;
  unsigned i = 0;
  unsigned f = 12;
  NodePtr param = branches[1]->getNode(i);
  while(param != NULL){
    std::string var = param->getId();
    int size = param->getSize();
    enum Specifier type = param->getType();
    if( param->getNode(1)->isPtr() ){
      newFrame.varBindings[var] = {size, paramSize+8, -1, Specifier::_ptr};
    }else{
      newFrame.varBindings[var] = {size, paramSize+8, -1, type};
    }

    switch(type){
      case _float:
        if(f <= 14){
          dst << "swc1 $f" << f << "," << paramSize+8 << "($30)" << std::endl; // floating point arguments stored in $f12 & $f14
          f += 2;
        }
        else if(i < 4){
          newFrame.varBindings[var].reg = i+4;
          dst << "sw $" << i+4 << "," << paramSize+8 << "($30)" << std::endl; // stores 2 extra fp arguments in $6-$7
        }
        break;
      case _double:
        if(f <= 14){
          dst << "sdc1 $f" << f << "," << paramSize+8 << "($30)" << std::endl;
          f += 2;
        }
        break;
      default:
        if(i < 4){
          newFrame.varBindings[var].reg = i+4; // First 4 arguments stored in registers $4-$7
          dst << "sw $" << i+4 << "," << paramSize+8 << "($30)" << std::endl; // The first 4 args aren't actually stored in the right place
        }
    }
    i++;
    paramSize += size;
    context.functions[id].argSize.push_back(size);
    param = branches[1]->getNode(i);
  }
  if(paramSize < 16 && paramSize > 0){
    paramSize = 16;
  }
  context.functions[id].size = paramSize;
  context.stack.push_back(newFrame);
}

// Helpers for codegen
NodePtr FunctionDeclarator::getNode(unsigned index) const
{
  return branches[index];
}

std::string FunctionDeclarator::getId() const
{
  return branches[0]->getId();
}

bool FunctionDeclarator::isFunction() const
{
  return true;
}
