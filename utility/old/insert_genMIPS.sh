#!/bin/bash

# Creates the .hpp and .cpp files for AST construct following naming conventions and adds them to git
# NOTE: Run this in base directory

set -euo pipefail

INCLUDE_DIR="include/ast/"
SRC_DIR="src/include_impl/ast/"


for i in src/include_impl/ast/operators/binaryOps/*.cpp; do
    echo "void BinaryAdd::generateMIPS(std::ostream &dst, Context context, int destReg) const
{
  int regLeft, regRight;
  if( ((regLeft = context.regFile.allocate()) == -1) | (regRight = context.regFile.allocate();) == -1 ){
    std::cerr << \"OOPSIES NO REGS ARE FREE. OVERWRITING\" << std::endl;
  }

  getLeft->generateMIPS(&dst, context, regLeft);
  getRight->generateMIPS(&dst, context, regRight);

  EZPrint(&dst, \"add\", destReg, regLeft, regRight);

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}" >> ${i}
done



>&2 echo "Inserted it"
