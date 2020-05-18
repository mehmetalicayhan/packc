#include "ProjectCreator.hpp"
#include <fstream>

ProjectCreator::ProjectCreator() {
    init();
    createProject();
}

void ProjectCreator::init() {
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

    fileManager = new FileManager(p_name, p_version, p_makeSystem, p_author);
}

void ProjectCreator::createDirectory(std::string directoryName) {
    std::string path;
    path = p_path + "/" + directoryName;
#ifdef __unix__
    filesystem::create_directory(path.c_str());

#elif defined(_WIN32) || defined(WIN32)
#include<windows.h>
    if(CreateDirectory(path,NULL)){

        std::cout<<"Created";

    }

#endif
}


void ProjectCreator::createDirectories() {
    for (size_t i = 0; i < 3; i++) {
        createDirectory(directories[i].c_str());
    }
}

void ProjectCreator::createProject() {
    createDirectories();
    fileManager->createInitFiles();
}

void ProjectCreator::writeHelpPage() {
    std::cout << "DESCRIPTION\n\n"
              << "USAGE\n\n"
              << "Create Project:\tpackc create\n\n"
              << "Source File:\tpackc add -s <filename>\n\n"
              << "C++ Class:\tpackc add -c <filename>\n\n"
              << "Header File:\tpackc add -h <filename>\n\n"
              << "Build Project:\t packc build\n\n"
              << "Run Project:\t packc run\n\n"
              << "Clean Project:\t packc clean\n\n";

}

ProjectCreator::~ProjectCreator() {
    delete fileManager;
    delete this;
}