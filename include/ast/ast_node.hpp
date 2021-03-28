#ifndef ast_node_hpp
#define ast_node_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "context.hpp"

// Base building block for everything, the Argos

class Node;
typedef Node *NodePtr;

class Node
{
protected:
  std::vector<NodePtr> branches;

public:
  // Constructors
  // Used in derived classes
  Node(std::vector<NodePtr> _branches);
  Node();
  Node(std::vector<NodePtr> branches1, std::vector<NodePtr> branches2); // Specifically used for sequence

  // Destructor
  virtual ~Node();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const = 0;
  // We friends with ostream now :D
  friend std::ostream& operator<<(std::ostream &dst, const Node &Node);
  friend std::ostream& operator<<(std::ostream &dst, const NodePtr Node);

  // Codegen + helpers
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const;
  virtual void generateTypeMIPS(std::ostream &dst, Context &context, int destReg, std::string type) const;

  // Used in codegen for more complex, context-dependant constructs (i.e. to process declarator's in a higher node)
  virtual NodePtr getNode(unsigned index) const;
  // Used for codegen in returning the size of a variable
  virtual int getSize() const;
  virtual int getSize(Context &context) const;
  // Used in codegen in returning the identifier of a variable / function
  virtual std::string getId() const;
  // Used in codegen to check if a declaration is for a function
  virtual bool isFunction() const;
  // Used in codegen to check if enumeration
  virtual bool isEnum() const;
  // Used in codegen to check if declarator is initialised
  virtual bool isInit() const;
  // Used to get ArraySize
  virtual int getArraySize() const;
  // used to get literal values before codegen
  virtual int getValue() const;
  virtual int getValue(int i) const; // For arrays
  virtual double getFloat() const; // getValue but for floating point stuff
  virtual bool isPtr() const;
  virtual NodePtr getOp() const; // for unaryops
  virtual std::string getType() const; // Used for different typed instructions
};

#endif
