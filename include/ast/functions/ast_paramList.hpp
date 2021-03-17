#ifndef ast_paramList_hpp
#define ast_paramList_hpp

#include "ast/ast_nodeList.hpp"

class ParamList;
typedef ParamList *ParamListPtr;

class ParamList
  : public NodeList
{
public:
  using NodeList::NodeList;

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
};

#endif
