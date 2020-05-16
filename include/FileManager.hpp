#ifndef FileManager_HPP
#define FileManager_HPP

#include <string>

class FileManager
{

private:
  std::string projectDir;
  std::string projectName;
  std::string projectVersion;
  std::string projectMakeSystem;
  std::string projectAuthor;

public:
  enum class FileType
  {
    CMAKE,
    MAKEFILE,
    HEADER,
    SOURCE,
    MAIN,
    MAC
  };
  void createCMakeFile();
  void createMACFile();
  void createMainFile();
  static void createSourceFile(std::string name);
  static void createHeaderFile(std::string name);
  void createInitFiles();
  static bool isFileExist(std::string path);
  static void createFile(FileType type, std::string name);
  static void addToCMakeFile(std::string name, std::string extension);
  FileManager(std::string projectName = "./");
  FileManager(std::string projectName, std::string projectVersion, std::string projectMakeSystem, std::string projectAuthor);
  ~FileManager();
};

#endif