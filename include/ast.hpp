#ifndef generic_ast_hpp
#define generic_ast_hpp

#include <string>
#include <iostream>
#include <memory>
#include <initializer_list>
#include <vector>
#include <map>

#include "ast/ast_program.hpp"
#include "ast/ast_statement.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_primitives.hpp"

extern const Program *parseAST();

#endif