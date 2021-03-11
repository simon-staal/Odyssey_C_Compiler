#ifndef ast_return_hpp
#define ast_return_hpp

#include "ast_node.hpp"
#include "literals/ast_integer.hpp" // Needed for void

class Return
  : public Node
{
public:
    // Constructors
    Return(NodePtr val)
    {
      branches.push_back(val);
    }

    Return() // For void funcitons (hopefully this works), returns 0 (i.e. success)
      : Return(new Integer())
    {}

    // Destructor
    ~Return()
    {
      delete branches[0];
    }

    // Visualising
    virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
    {
      dst << indent << "Return: [" << std::endl;
      branches[0]->PrettyPrint(dst, indent+"  ");
      dst << indent << "]" << std::endl;
    }
};

#endif
