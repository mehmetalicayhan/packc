#ifndef ProjectCreator_HPP
#define ProjectCreator_HPP
#include <experimental/filesystem>
#include <iostream>

enum class FileType
{
  CMAKE,
  MAKEFILE,
  HEADER,
  SOURCE,
  MAIN,
  MAC
};

namespace filesystem = std::experimental::filesystem;
class ProjectCreator
{

private:
  // p = project
  std::string p_name;
  std::string p_version;
  std::string p_author;
  std::string p_makeSystem;
  std::string p_path;

  std::string directories[3] = {"", "include", "src"};

public:
  ProjectCreator();
  ~ProjectCreator();
  void createDirectories();
  void createProject();
  void createFile(FileType type);
  void createFile(FileType type, std::string name);
  void createDirectory(std::string createDir = "");
  void createFile(std::string name, std::string extension);
};

#endif