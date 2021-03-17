#ifndef ast_node_hpp
#define ast_node_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include ""

// Base building block for everything, the Argos

class Node;
typedef Node *NodePtr;

class Node
{
protected:
  std::vector<NodePtr> branches;

public:
  // Used in derived classes
  Node(std::vector<NodePtr> _branches);
  Node();
  // Specifically used for sequence
  Node(std::vector<NodePtr> branches1, std::vector<NodePtr> branches2);

  virtual ~Node();

  // Used for codegen in returning the size of a variable
  virtual int getSize() const = 0;
  // Used in codegen in returning the identifier of a variable / function
  virtual std::string getId() const = 0;
  // Used in codegen to check if identifier is for function
  virtual bool isFuntion() const = 0;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const = 0;

  virtual void generateMIPS(std::ostream &dst, Context context, int destReg) const = 0;

  // We friends with ostream now :D
  friend std::ostream& operator<<(std::ostream &dst, const Node &Node);
  friend std::ostream& operator<<(std::ostream &dst, const NodePtr Node);
};

// idk wtf this is lmao
/*
struct CompileContext
{
    std::map<std::string,int32_t> bindings;
};
*/

#endif
