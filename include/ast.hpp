#ifndef generic_ast_hpp
#define generic_ast_hpp

#include <string>
#include <iostream>
#include <memory>
#include <initializer_list>
#include <vector>
#include <map>

#include "ast/ast_node.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_primitive.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_return.hpp"
#include "ast/ast_identifier.hpp"
#include "ast/ast_scope.hpp"
#include "ast/ast_sequence.hpp"

extern const Program *parseAST();

#endif
