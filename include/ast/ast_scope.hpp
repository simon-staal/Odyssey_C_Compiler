#ifndef ast_scope_hpp
#define ast_scope_hpp

#include "ast_node.hpp"

class Scope
  : public Node
{
private:
public:
  std::vector<NodePtr> expressions = {};
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
      dst
  }
}

#endif
