#ifndef ast_enumerator_hpp
#define ast_enumerator_hpp

#include "ast/ast_node.hpp"

class Enumerator
  : public Node
{
public:
  // Constructor
  Enumerator(std::string _id, NodePtr expression);

  // Destructor
  ~Enumerator();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  //void generateMIPS(std::ostream &dst, Context &context, int destReg) const override; // idk if we need this rn
  NodePtr getNode(unsigned index) const override;
  bool isEnum() const override;
  std::string getId() const override;
  int getValue() const override;

protected:
  std::string id;
};


#endif
