#ifndef ast_function_hpp
#define ast_function_hpp

#include "ast_node.hpp"

class Function
  : public Node
{
private:
    std::string type;
    std::string identifier;
    NodePtr scope;

public:
  Function(std::string _type, std::string _identifier, NodePtr _scope)
    : type(_type),
      identifier(_identifier),
      scope(_scope);
  {}

};

#endif
