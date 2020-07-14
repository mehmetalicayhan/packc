#ifndef ProjectCreator_HPP
#define ProjectCreator_HPP
#ifdef _WIN32
#include"direct.h"
#define CMAKE_FLAGS "-G \"MinGW Makefiles\""
#elif __unix__ || __APPLE__
#include <sys/stat.h>
#endif

#include <iostream>
#include "FileManager.hpp"


class ProjectCreator {

private:
    // p = project
    std::string p_name;
    std::string p_version;
    std::string p_author;
    std::string p_path;
    std::string p_repository;

    FileManager *fileManager;
    std::string directories[4] = {"", "include", "src", "build"};

public:
    ProjectCreator();

    ~ProjectCreator();

    void createDirectories();

    void createProject();

    void init();

    void createDirectory(const std::string &createDir = "");

    static void printHelp();
};

#endif