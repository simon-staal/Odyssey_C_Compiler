#ifndef ast_return_hpp
#define ast_return_hpp

#include "ast_node.hpp"
#include "literals/ast_integer.hpp" // Needed for void

class Return
  : public Node
{
public:
    // Constructors
    Return(NodePtr val);
    Return(); // For void funcitons (hopefully this works), returns 0 (i.e. success)

    // Destructor
    ~Return();

    // Visualising
    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
    virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;

};

#endif
