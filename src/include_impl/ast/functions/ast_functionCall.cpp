#include "ast/functions/ast_functionCall.hpp"
#include <unordered_set>

// Constructors
FunctionCall::FunctionCall(NodePtr id, NodeListPtr params)
{
  branches.push_back(id);
  branches.push_back(params);
}

FunctionCall::FunctionCall(NodePtr id, std::vector<NodePtr> params)
  : FunctionCall(id, new NodeList(params))
{}

FunctionCall::FunctionCall(NodePtr id)
  : FunctionCall(id, new NodeList())
{}

// Destructor
FunctionCall::~FunctionCall()
{
  delete branches[0];
  delete branches[1];
}

// Visualising
void FunctionCall::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Function Call [" << std::endl;
  dst << indent << "Identifier: " << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "Parameters: " << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

// Codegen + helpers
void FunctionCall::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::string id = getId();
  int argSize = context.functions[id].size;
  //dst << "DEBUGGING: argSize of " << id << " = " << argSize << std::endl;

  // Staging arguments
  if(argSize > 0){
    dst << "addiu $29,$29," << -argSize << std::endl; // Decrement stack pointer by appropriate amount
    NodePtr param = branches[1]->getNode(0);
    int i = 0;
    int offset = 0;
    while(param != NULL && i < 4){ // First 4 arguments stored in registers $4-$7
      param->generateMIPS(dst, context, i+4);
      offset += context.functions[id].argSize[i];
      i++;
      param = branches[1]->getNode(i);
    }
    if(argSize > 16){ // Rest stored in memory
      int paramReg = context.allocate();
      while(param != NULL){
        param->generateMIPS(dst, context, paramReg);
        dst << "sw $" << paramReg << "," << offset << "($29)" << std::endl;
        offset += context.functions[id].argSize[i];
        i++;
        param = branches[1]->getNode(i);
      }
    }
  }

  // Indicate variable stored in reg no longer available
  for(auto it = context.stack.back().varBindings.begin(); it != context.stack.back().varBindings.end(); it++){
    std::unordered_set<int> regs = {2, 3, 4, 5, 6, 7, 8 ,9, 10, 11, 12, 13, 14, 15, 24, 25}; // Regs changed by function calls (that we use)
    if(regs.find(it->second.reg) != regs.end()){
      it->second.reg = -1;
    }
  }

  // Going to function
  dst << "jal " << id << std::endl;
  dst << "nop" << std::endl;

  // Returning from function
  dst << "addiu $29, $29," << argSize << std::endl; // Deallocate memory allocated for function call vars
}

std::string FunctionCall::getId() const
{
  return branches[0]->getId();
}

bool FunctionCall::isFunction() const
{
  return true;
}
