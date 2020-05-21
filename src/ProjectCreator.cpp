#include "ProjectCreator.hpp"
#include <fstream>

ProjectCreator::ProjectCreator() {
    init();
    fileManager = new FileManager(p_name, p_version, p_author);
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
    p_author = author;
    p_path = "./" + p_name;
}

void ProjectCreator::createDirectory(const std::string &directoryName) {
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
              << "packc is a project manager for C++ written by @mehmetalicayhan.\nYou can create project or add classes,source files, or header files to your existing packc project. \nIn same time this files add to your cmake file automatically.\nYou can build and run your projects and define your own commands.\n\n"
              << "USAGE\n\n"
              << "Create Project:\tpackc create\n\n"
              << "Create Source File:\tpackc add -s <filename>\n\n"
              << "Create C++ Class:\tpackc add -c <filename>\n\n"
              << "Create Header File:\tpackc add -h <filename>\n\n"
              << "Build Project:\t packc build\n\n"
              << "Run Project:\t packc run\n\n"
              << "Clean Project:\t packc clean\n\n";

}

ProjectCreator::~ProjectCreator() {
    delete fileManager;
    delete this;
}