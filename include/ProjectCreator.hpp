#ifndef ProjectCreator_HPP
#define ProjectCreator_HPP

#include <experimental/filesystem>
#include <iostream>
#include "FileManager.hpp"

namespace filesystem = std::experimental::filesystem;

class ProjectCreator {

private:
    // p = project
    std::string p_name;
    std::string p_version;
    std::string p_author;
    std::string p_path;
    FileManager *fileManager;
    std::string directories[3] = {"", "include", "src"};

public:
    ProjectCreator();

    ~ProjectCreator();

    void createDirectories();

    void createProject();

    void init();

    void createDirectory(const std::string& createDir = "");

    static void writeHelpPage();
};

#endif