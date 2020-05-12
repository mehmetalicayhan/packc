#include "Application.hpp"
#include <iostream>

Application::Application(int argc, char const *argv[])
{
  std::string programArg = argv[1];

  if (argc < 2)
  {
    std::cout << "Usage";
    return;
  }

  if (programArg == "create")
  {
    projectCreator = new ProjectCreator();
  }
}

Application::~Application()
{
  delete projectCreator;
  delete this;
}
