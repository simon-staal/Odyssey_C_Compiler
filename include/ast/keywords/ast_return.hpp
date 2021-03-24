#ifndef ast_return_hpp
#define ast_return_hpp

#include "ast/ast_node.hpp"

class Return
  : public Node
{
public:
    // Constructors
    Return(NodePtr val);
    //Return(); // For void funcitons returns 0 (i.e. success) REFACTORED

    // Destructor
    ~Return();

    // Visualising
    void PrettyPrint(std::ostream &dst, std::string indent) const override;

    // Codegen
    void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;

};

#endif
