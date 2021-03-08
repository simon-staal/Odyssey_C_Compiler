#ifndef generic_ast_hpp
#define generic_ast_hpp

#include <string>
#include <iostream>
#include <memory>
#include <initializer_list>
#include <vector>
#include <map>

#include "ast/ast_node.hpp"
#include "ast/ast_nodeList.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_identifier.hpp"
#include "ast/ast_scope.hpp"
#include "ast/ast_sequence.hpp"

#include "ast/types/ast_primitive.hpp"

#include "ast/function/ast_functionDeclarator.hpp"
#include "ast_functionDefinition.hpp"

extern const NodePtr parseAST();

#endif
