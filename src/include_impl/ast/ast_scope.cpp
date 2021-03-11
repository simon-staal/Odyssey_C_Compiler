#include "ast/ast_scope.hpp"

// Just in case we need it
std::vector<NodePtr> Scope::getScope()
{
  return branches;
}
