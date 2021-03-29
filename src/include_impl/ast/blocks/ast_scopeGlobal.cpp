#include "ast/blocks/ast_scopeGlobal.hpp"

// Visualising
void GlobalScope::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Global Scope [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}

// Codegen
void GlobalScope::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  for(unsigned i = 0; i < branches.size(); i++){
    if(branches[i]->isFunction()){
      branches[i]->generateMIPS(dst, context, destReg);
    }
    else if(branches[i]->isEnum()){
      branches[i]->generateMIPS(dst, context, destReg);
    }
    else{
      // Global variables
      std::string id = branches[i]->getId();
      enum Specifier type = branches[i]->getType();
      context.globals.insert(std::pair<std::string, enum Specifier>(id, type)); // Add to global set
      dst << ".globl " << id << std::endl;
      dst << ".data" << std::endl;
      dst << ".align 2" << std::endl;
      int array = branches[i]->getArraySize();
      if(array == 0){ // Not an array
        int size = branches[i]->getSize();
        dst << ".size " << id << ", " << size << std::endl;
        dst << id << ":" << std::endl;
        if(branches[i]->isInit()){
          switch(type)
          {
            case _float:
              dst << ".float " << (float)branches[i]->getFloat() << std::endl; // Hopefully these work
              break;
            case _double:
              dst << ".double " << branches[i]->getFloat() << std::endl;
              break;
            default:
              dst << ".word " << branches[i]->getValue() << std::endl;
          }

        }
        else{
          dst << ".space " << size << std::endl;
        }
      }
      else{
        int size = array*branches[i]->getSize();
        dst << ".size " << id << ", " << size << std::endl;
        dst << id << ":" << std::endl;
        if(branches[i]->isInit()){
          switch(type)
          {
            case _float:
              for(unsigned index = 0; index < array; index++){
                dst << ".float " << (float)branches[i]->getFloat(index) << std::endl;
              }
              break;
            case _double:
              for(unsigned index = 0; index < array; index++){
                dst << ".double " << branches[i]->getFloat(index) << std::endl;
              }
              break;
            default:
            // Initializes every index in order
            for(unsigned index = 0; index < array; index++){
              dst << ".word " << branches[i]->getValue(index) << std::endl;
            }
          }
        }
        else{
          dst << ".space " << size << std::endl;
        }
      }


    }
  }
}
