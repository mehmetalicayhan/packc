#include "Application.hpp"
#include <iostream>
#include <FileManager.hpp>
#include "ProjectBuilder.hpp"
Application::Application(int argc, char const *argv[])
{
  std::string programArg = argv[1];
  ProjectBuilder *pb = new ProjectBuilder();

  if (argc < 2)
  {
    std::cout << "Usage";
    return;
  }

  if (programArg == "create")
  {
    projectCreator = new ProjectCreator();
  }
  else if (programArg == "add")
  {

    std::string argument = argv[2];
    std::string fileName = argv[3];

    if (argument == "-c")
    {
      std::cout << "create class";

      FileManager::createFile(FileManager::FileType::SOURCE, fileName);
      FileManager::createFile(FileManager::FileType::HEADER, fileName);
    }
    else if (argument == "-s")
    {
      std::cout << "create source :";

      FileManager::createFile(FileManager::FileType::SOURCE, fileName);
    }
    else if (argument == "-h")
    {
      std::cout << "create header :";

      // TODO .h file include in class
      FileManager::createFile(FileManager::FileType::HEADER, fileName);
    }
  }
  pb->runCommands(programArg);
}

Application::~Application()
{
  delete projectCreator;
  delete this;
}
