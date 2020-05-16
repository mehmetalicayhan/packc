#include "ProjectBuilder.hpp"
#include <fstream>
#include "json.hpp"
#include <string>
#include <iostream>

using json = nlohmann::json;

ProjectBuilder::ProjectBuilder(/* args */)
{
  std::ifstream cppmacFile("./cppmac.json");
  json j;
  cppmacFile >> j;
  for (auto i : j["commands"].items())
  {
    jsonData.insert(std::pair<std::string, std::string>(i.key(), i.value()));
    // std::cout << i.key() << " " << std::endl;
  }
}

ProjectBuilder::~ProjectBuilder()
{
}

// void ProjectBuilder::buildProject()
// {
//   std::ifstream i("./cppmac.json");
//   json j;
//   i >> j;
//   // std::cout << j["commands"]["build"].dump(4);
//   std::string buildCommand = j["commands"]["build"].dump(4);
//   buildCommand.replace(0, 1, "");
//   buildCommand.replace(buildCommand.size() - 1, 1, "");

//   system(buildCommand.c_str());
//   i.close();
// }

// void ProjectBuilder::runProject()
// {
//   std::ifstream cppmacFile("./cppmac.json");
//   json j;
//   cppmacFile >> j;
//   std::string runCommand = j["commands"]["run"].dump(4);
//   runCommand.replace(0, 1, "");
//   runCommand.replace(runCommand.size() - 1, 1, "");
//   for (auto i : j["commands"].items())
//   {
//     jsonData.insert(std::pair<std::string, std::string>(i.key(), i.value()));
//     // std::cout << i.key() << " " << std::endl;
//   }
//   //system(runCommand.c_str());
//   cppmacFile.close();

//   // std::ifstream file("./cppmac.json");
//   // json commands;

//   // std::vector<std::string> names = commands["commands"];

//   // for (auto i : names)
//   // {
//   //   std::cout << i << " ";
//   // }
// }

void ProjectBuilder::runCommands(std::string argument)
{
  std::multimap<std::string, std::string>::iterator itr;

  for (itr = jsonData.begin(); itr != jsonData.end(); ++itr)
  {
    std::string command = itr->second;
    if (itr->first == argument)
    {
      std::cout << itr->first << "\t" << command;
      system(command.c_str());
    }
  }
}