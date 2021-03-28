#!/bin/bash

# Creates the .hpp and .cpp files for AST construct following naming conventions and adds them to git
# NOTE: Run this in base directory

set -euo pipefail

INCLUDE_DIR="include/ast/"
SRC_DIR="src/include_impl/ast/"

if [[ $# -eq 0 ]] ; then
  >&2 echo "Usage: ./add_ast.sh <Construct_Name> <Path>"
  >&2 echo "<Construct_Name> is the name of the new class to be added to the AST (without prefix), i.e. ifThenElse for ast_ifThenElse"
  >&2 echo "<Path> (optional) is any extra filepath from the ast directory (i.e. \"operators/\" would create file in .../ast/operators/ )"
  exit 1
fi

NAME="$1"
DIR="${2:-null}"
SHORTNAME="$3"

if [[ "${DIR}" = "null" ]] ; then
  touch "${INCLUDE_DIR}ast_${NAME}.hpp"
  touch "${SRC_DIR}ast_${NAME}.cpp"
  git add "${INCLUDE_DIR}ast_${NAME}.hpp" "${SRC_DIR}ast_${NAME}.cpp"
else
  touch "${INCLUDE_DIR}${DIR}ast_${NAME}.hpp"
  touch "${SRC_DIR}${DIR}ast_${NAME}.cpp"
  git add "${INCLUDE_DIR}${DIR}ast_${NAME}.hpp" "${SRC_DIR}${DIR}ast_${NAME}.cpp"
fi

echo "#include \"ast/operators/binaryOps/ast_binary${SHORTNAME}.hpp\"

void Binary$SHORTNAME::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << \"Binary ${SHORTNAME} [ \" << std::endl;
  dst << indent << \"Left Op:\" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+ \"  \");
  std::cout << indent << \"Right Op: \" << std::endl;
  RightOp()->PrettyPrint(dst, indent+\"  \");
  std::cout << indent << \"]\" <<std::endl;
}
" > ${SRC_DIR}${DIR}ast_${NAME}.cpp

echo "#ifndef ast_binary${SHORTNAME}_hpp
#define ast_binary${SHORTNAME}_hpp

#include \"ast/operators/ast_binaryOperation.hpp\"

class Binary${SHORTNAME}
    : public BinaryOperation
{
public:

    using BinaryOperation::BinaryOperation;

    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;


};

#endif
" > ${INCLUDE_DIR}${DIR}ast_${NAME}.hpp

echo "#include \"ast/operators/binaryOps/ast_binary${SHORTNAME}.hpp\"" >> include/ast.hpp


>&2 echo "Created files"
