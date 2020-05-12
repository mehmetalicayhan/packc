#ifndef  Application_HPP
#define  Application_HPP
#include "ProjectCreator.hpp"

class Application { 

  private:
  ProjectCreator * projectCreator;

  public:
  Application(int argc,char const* argv[]);
  ~Application();
};

#endif