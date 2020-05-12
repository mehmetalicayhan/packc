#include "ProjectCreator.hpp"
#include <fstream>
ProjectCreator::ProjectCreator()
{
  // Get inputs from user
  std::string projectName;
  std::string version;
  std::string makeSystem;
  std::string author;

  std::cout << "Project Name : ";
  std::cin >> projectName;

  std::cout << "Version : ";
  getline(std::cin, version);

  std::cout << "Make System (CMake/Makefile) : ";
  getline(std::cin, makeSystem);

  std::cout << "Author : ";
  getline(std::cin, author);

  p_name = projectName;
  p_version = version;
  p_makeSystem = makeSystem;
  p_author = author;
  p_path = "./" + p_name;

  createProject();
}

void ProjectCreator::createDirectory(std::string directoryName)
{
  std::string path = p_path + "/" + directoryName;
  filesystem::create_directory(path.c_str());
}

void ProjectCreator::createDirectories()
{
  for (size_t i = 0; i < 3; i++)
  {
    createDirectory(directories[i].c_str());
  }
}

void ProjectCreator::createFile(FileType type)
{
  std::ofstream file;

  if (type == FileType::CMAKE)
  {

    file.open(p_path + "/CMakeLists.txt");

    file << "cmake_minimum_required(VERSION 2.8)"
         << "\n"
         << "project(" + p_name + ")\n"
         << "set(PROJECT_DIR ${CMAKE_SOURCE_DIR})\n"
         << "set(PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)\n"
         << "set(PROJECT_SOURCE_DIR ${PROJECT_DIR}/src)\n"
         << "set(PROJECT_SOURCES\n${PROJECT_SOURCE_DIR}/main.cpp)\n"
         << "include_directories(${PROJECT_INCLUDE_DIR})\n"
         << "add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})\n";
  }
  else if (type == FileType::MAIN)
  {
    std::string mainPath = p_path + "/src/main.cpp";
    file.open(mainPath);
    file << "#include<iostream>\n\nint main(int argc,char** argv){\n\n\tstd::cout<<\"Hello World\"<<std::endl;\n\n\treturn 0;\n\n}";
  }
  else if (type == FileType::MAC)
  {
    file.open(p_path + "/" + p_name + ".cppmac");
    file << "Project Name : " << p_name << "\n"
         << "Version : " << p_version << "\n"
         << "Make System : " << p_makeSystem << "\n"
         << "Author : " << p_author << "\n";
  }

  file.close();
}

void ProjectCreator::createFile(FileType type, std::string name)
{
  std::ofstream file;
  std::string path = p_path;
  if (type == FileType::SOURCE)
  {
    path = p_path + "/src/" + name + ".cpp";
    file.open(path);
    file << "class " + name + "\n"
         << "{\n"
         << "private: \n\n"
         << "public: \n\n"
         << "   " + name + "(/* args */); \n"
         << "   ~" + name + "(); \n"
         << "};\n"
         << "\n"
         << name + "::" + name + "(/*args*/)\n"
         << "{\n"
         << "}\n"
         << "~" + name + "::" + name + "(/*args*/)\n"
         << "{\n"
         << "}\n";
  }
  else if (type == FileType::HEADER)
  {
    path = p_path + "/include/" + name + ".hpp";
    file.open(path);
    file << "#ifndef " + name + "_HPP\n"
         << "#define " + name + "_HPP\n"
         << "class " + name + "\n"
         << "{\n"
         << "private: \n\n"
         << "public: \n\n"
         << "   " + name + "(/* args */); \n"
         << "   ~" + name + "(); \n"
         << "};\n"
         << "\n\n"
         << "#endif";
  }

  file.close();
}

void ProjectCreator::createProject()
{
  createDirectories();
  createFile(FileType::CMAKE);
  createFile(FileType::MAIN);
  createFile(FileType::MAC);
  createFile(FileType::SOURCE, "test");
  createFile(FileType::HEADER, "test");
}

ProjectCreator::~ProjectCreator()
{
  delete this;
}