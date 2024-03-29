#include "ast/keywords/ast_return.hpp"

// Constructors
Return::Return(NodePtr val)
{
  branches.push_back(val);
}

/* REFACTORED INTO PARSER
Return::Return() // For void funcitons (hopefully this works), returns 0 (i.e. success)
  : Return(new Integer())
{}
*/

// Destructor
Return::~Return()
{
  delete branches[0];
}

// Visualising
void Return::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Return: [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

// Codegen
void Return::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  switch(context.stack.back().returnType)
  {
    case _float:
      branches[0]->generateTypeMIPS(dst, context, 0, Specifier::_float); // Evaluates expression into $f0 (return register for floats)
      break;
    case _double:
      branches[0]->generateTypeMIPS(dst, context, 0, Specifier::_double);
      break;
    default: // Evaluates expression into $2
      branches[0]->generateMIPS(dst, context, 2);
  }


  // Exiting function
  dst << "move $29,$30" << std::endl;
  dst << "lw $30,0($29)" << std::endl;
  dst << "lw $31,4($29)" << std::endl;
  dst << "addiu $29,$29,8" << std::endl;
  dst << "jr $31" << std::endl;
  dst << "nop" << std::endl; // <- Not using delay slot (gross)
}
