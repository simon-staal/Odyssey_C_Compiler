#include "ast/types/ast_enumSpecifier.hpp"

// Constructor
EnumSpecifier::EnumSpecifier(std::string _id, std::vector<NodePtr> enums)
{
  id = _id;
  branches = enums;
}

EnumSpecifier::EnumSpecifier(std::string _id)
  : EnumSpecifier(_id, std::vector<NodePtr>{})
{}

EnumSpecifier::~EnumSpecifier()
{
  for(unsigned i = 0; i < branches.size(); i++){
    delete branches[i];
  }
}

// Visualising
void EnumSpecifier::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "EnumerationSpecifier [" << std::endl;
  dst << indent << "id: " << id << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "] endEnumeration" << std::endl;
}

void EnumSpecifier::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::string enumId = getId();
  int val = -1;
  for(unsigned i = 0; i < branches.size(); i++){
    std::string id = branches[i]->getId();
    if(branches[i]->getNode(0) != NULL){
      val = branches[i]->getValue();
    }
    else{
      val++;
    }
    context.enums[id] = {enumId, val};
  }
}

std::string EnumSpecifier::getId() const
{
  return id;
}

bool EnumSpecifier::isEnum() const
{
  return true;
}
