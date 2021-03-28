#include "ast/types/ast_enumerator.hpp"

Enumerator::Enumerator(std::string _id, NodePtr expression)
{
  id = _id;
  branches.push_back(expression);
}

Enumerator::~Enumerator()
{
  if(branches[0] != NULL){
    delete branches[0];
  }
}

void Enumerator::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << id << ": " << std::endl;
  if(branches[0] != NULL){
    branches[0]->PrettyPrint(dst, indent+"  ");
  }
  else{
    dst << indent+"  "+"Default" << std::endl;
  }
}

NodePtr Enumerator::getNode(unsigned index) const
{
  if(index == 0){
    return branches[0];
  }
  std::cerr << "Tried to getNode out of enum range" << std::endl;
  return NULL;
}

std::string Enumerator::getId() const
{
  return id;
}

bool Enumerator::isEnum() const
{
  return true;
}

int Enumerator::getValue() const
{
  if(branches[0] == NULL){
    std::cerr << "Tried to getValue of uninit enum" << std::endl;
    exit(1);
  }
  return branches[0]->getValue();
}
