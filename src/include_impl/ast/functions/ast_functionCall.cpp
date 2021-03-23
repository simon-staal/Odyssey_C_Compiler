#include "ast/functions/ast_functionCall.hpp"

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

  // Staging arguments
  if(argSize > 0){
    context.stack.back().offset += argSize;
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

  // Going to function
  dst << "jal " << id << std::endl;
  dst << "nop" << std::endl;
}

std::string FunctionCall::getId() const
{
  return branches[0]->getId();
}
