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
#include "ast/ast_root.hpp"
#include "ast/ast_empty.hpp"
#include "ast/ast_declarator.hpp"
#include "ast/ast_initDeclarator.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_identifier.hpp"

#include "ast/ast_return.hpp"

#include "ast/blocks/ast_sequence.hpp"
#include "ast/blocks/ast_scope.hpp"
#include "ast/blocks/ast_scopeGlobal.hpp"
#include "ast/blocks/ast_ifElse.hpp"
#include "ast/blocks/ast_while.hpp"
#include "ast/blocks/ast_for.hpp"

#include "ast/literals/ast_integer.hpp"

#include "ast/types/ast_primitive.hpp"

#include "ast/functions/ast_functionDeclarator.hpp"
#include "ast/functions/ast_functionDefinition.hpp"
#include "ast/functions/ast_functionCall.hpp"

#include "ast/operators/ast_binaryOperation.hpp"
#include "ast/operators/binaryOps/ast_binaryAdd.hpp"
#include "ast/operators/binaryOps/ast_binarySub.hpp"
#include "ast/operators/binaryOps/ast_binaryMul.hpp"
#include "ast/operators/binaryOps/ast_binaryDiv.hpp"
#include "ast/operators/binaryOps/ast_binaryMod.hpp"
#include "ast/operators/binaryOps/ast_binaryGT.hpp"
#include "ast/operators/binaryOps/ast_binaryLT.hpp"
#include "ast/operators/binaryOps/ast_binaryGTEQ.hpp"
#include "ast/operators/binaryOps/ast_binaryLTEQ.hpp"
#include "ast/operators/binaryOps/ast_binaryNEQ.hpp"
#include "ast/operators/binaryOps/ast_binaryEQ.hpp"
#include "ast/operators/binaryOps/ast_binaryAND.hpp"
#include "ast/operators/binaryOps/ast_binaryLogAND.hpp"
#include "ast/operators/binaryOps/ast_binaryLogOR.hpp"
#include "ast/operators/binaryOps/ast_binaryOR.hpp"
#include "ast/operators/binaryOps/ast_binaryXOR.hpp"
#include "ast/operators/binaryOps/ast_binaryRShift.hpp"
#include "ast/operators/binaryOps/ast_binaryLShift.hpp"

#include "ast/operators/binaryOps/ast_binaryDivAss.hpp"
#include "ast/operators/binaryOps/ast_binaryMulAss.hpp"
#include "ast/operators/binaryOps/ast_binaryModAss.hpp"
#include "ast/operators/binaryOps/ast_binaryAddAss.hpp"
#include "ast/operators/binaryOps/ast_binarySubAss.hpp"
#include "ast/operators/binaryOps/ast_binaryLeftAss.hpp"
#include "ast/operators/binaryOps/ast_binaryRightAss.hpp"
#include "ast/operators/binaryOps/ast_binaryANDAss.hpp"
#include "ast/operators/binaryOps/ast_binaryXORAss.hpp"
#include "ast/operators/binaryOps/ast_binaryORAss.hpp"
#include "ast/operators/binaryOps/ast_binaryNormalAss.hpp"

#include "ast/operators/unaryOps/ast_unaryAdd.hpp"
#include "ast/operators/unaryOps/ast_unaryNOT.hpp"
#include "ast/operators/unaryOps/ast_unaryBWNOT.hpp"
#include "ast/operators/unaryOps/ast_unaryPtr.hpp"
#include "ast/operators/unaryOps/ast_unaryAdr.hpp"
#include "ast/operators/unaryOps/ast_unarySub.hpp"
#include "ast/operators/unaryOps/ast_unaryPreDec.hpp"
#include "ast/operators/unaryOps/ast_unaryPreInc.hpp"

#include "ast/context.hpp"

extern Node *parseAST(std::string filename);

#endif
