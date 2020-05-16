#ifndef ProjectBuilder_HPP
#define ProjectBuilder_HPP
#include <vector>
#include <map>
class ProjectBuilder
{

private:
  std::multimap<std::string, std::string> jsonData;

public:
  ProjectBuilder();
  ~ProjectBuilder();
  void runCommands(std::string argument);
};

#endif