#ifndef ast_program_hpp
#define ast_program_hpp

class Program;

typedef const Program *ProgramPtr;

class Program
{
public:
  virtual ~Program()
  {}

  virtual void
}

ProgramPtr Parse(
    std::istream &src
);

struct CompileContext
{
    std::vector<int32_t> params;
    std::map<std::string,int32_t> bindings;
};

void Compile(
    ProgramPtr program,
    CompileContext &context
);
