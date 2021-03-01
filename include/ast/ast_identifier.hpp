#ifndef ast_identifier_hpp
#define ast_identifier_hpp

#include "ast_node.hpp"

class Identifier
  : public Node
{
private:
  std::string id;
public:
  Identifier(std::string _id)
    : id(_id)
  {}

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "Identifier = " << id << std::endl;
  }
};

#endif
