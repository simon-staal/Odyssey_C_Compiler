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
#include "ast/ast_sequence.hpp"
#include "ast/ast_return.hpp"

#include "ast/literals/ast_integer.hpp"

#include "ast/types/ast_primitive.hpp"

#include "ast/functions/ast_functionDeclarator.hpp"
#include "ast/functions/ast_functionDefinition.hpp"

#include "ast/operators/ast_binaryAdd.hpp"
#include "ast/operators/ast_binaryOperation.hpp"

#include "ast/blocks/ast_scope.hpp"
#include "ast/blocks/ast_ifElse.hpp"

extern Node *parseAST(std::string filename);

#endif
